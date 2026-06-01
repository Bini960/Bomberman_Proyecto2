#include "MotorJuego.h" // Enlaza el archivo de definiciones del archivo principal
#include "Jugador.h" // Permite instanciar objetos del tipo personaje en memoria.
#include "Enemigo.h" // Permite instanciar objetos del tipo adversario.
#include "ManejadorEntrada.h" // Permite instanciar el hilo lector del hardware de teclado.
#include <unistd.h> 
#include <iostream>

MotorJuego::MotorJuego() { // Constructor
    juegoActivo = false; // El programa arranca sin una partida activa por defecto.
    pausado = false; // La pausa se encuentra desactivada inicialmente.
    puntos = 0; // El puntaje inicia sin valores acumulados.
    nivel = 1; // La dificultad inicia en la etapa base.
    bombasActivas = 0; // El conteo de artefactos inicia vacío.
    maxBombas = 3; // Límite de artefactos simultáneos predeterminado para control de memoria.
    modoJuego = 1; // Configura el formato contra la inteligencia artificial por defecto.
    mensajeGlobal = "¡Buena suerte!";

    pthread_mutexattr_t attr; // Crea los atributos para el candado de sincronización POSIX.
    pthread_mutexattr_init(&attr); // Inicia los atributos del candado en memoria.
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE); // Configura un candado recursivo para prevenir interbloqueos entre funciones anidadas.
    pthread_mutex_init(&mutexEstado, &attr); // Construye el candado principal del juego aplicando los atributos.
    pthread_mutexattr_destroy(&attr); // Libera la memoria de los atributos tras aplicarlos al candado.
    pthread_cond_init(&condPausa, NULL); // Inicia el suspensor pasivo de hilos.
    manejador = nullptr; // Asegura que el lector de teclado no contenga direcciones de memoria residuales.
}

MotorJuego::~MotorJuego() { // Destructor 
    detener(); // Envía la señal de apagado a todos los subprocesos en ejecución.
    limpiarNivel(); // Se asegura de recolectar todos los recursos dinámicos.
    pthread_mutex_destroy(&mutexEstado); // Devuelve los recursos del candado al sistema operativo.
    pthread_cond_destroy(&condPausa); // Devuelve los recursos de la variable de condición.
}

void MotorJuego::iniciarMenu() { 
    bool enMenu = true; // Establece la condición de permanencia en el programa.
    while (enMenu) { // Ejecuta el ciclo mientras no se elija salir.
        limpiarNivel(); // Se asegura de que la terminal esté restaurada y limpia antes de pedir datos.
        int opcion = mapa.mostrarMenu(); // Llama a la interfaz gráfica del menú y captura la selección.
        if (opcion == 1 || opcion == 2) { // Valida si se eligió iniciar una partida funcional.
            modoJuego = opcion; // Guarda la modalidad seleccionada.
            puntos = 0; // Restablece los contadores de la sesión.
            nivel = 1; // Devuelve la dificultad al inicio.
            juegoActivo = true; // Levanta la bandera de ejecución para los hilos.
            pausado = false; // Asegura que la partida inicie con flujo normal.
            inicializarNivel(); // Construye el laberinto y levanta los hilos de las entidades.
            ejecutar(); // Traspasa el control al ciclo de actualización gráfica.
            mapa.guardarPuntaje(puntos); // Salva el récord en archivo de texto al perder o terminar.
        } else if (opcion == 3) { // Valida si se solicitó el panel de ayuda.
            mapa.mostrarInstrucciones(); // Despliega la información de reglas.
        } else if (opcion == 4) { // Valida si se solicitaron los récords.
            mapa.mostrarPuntajes(); // Lee e imprime el archivo plano.
        } else if (opcion == 5) { // Valida la opción de salida.
            enMenu = false; // Rompe el ciclo maestro apagando el programa.
        }
    }
}

void MotorJuego::limpiarNivel() { 
    if (manejador != nullptr) { // Verifica si el puntero del teclado contiene datos.
        delete manejador; // Libera el espacio asignado en el heap e invoca su destructor.
        manejador = nullptr; // Elimina la referencia para evitar accesos indebidos.
    }
    for (Jugador* j : jugadores) { // Recorre el arreglo de personajes.
        delete j; // Destruye cada hilo de usuario.
    }
    for (Enemigo* e : enemigos) { // Recorre el arreglo de inteligencias artificiales.
        delete e; // Destruye cada hilo enemigo de forma controlada.
    }
    jugadores.clear(); // Vacía el contenedor de punteros de personajes.
    enemigos.clear(); // Vacía el contenedor de punteros de adversarios.
}

void MotorJuego::inicializarNivel() { // Reconstruye el entorno para jugar.
    mapa.inicializarMapa(); // Llama a la generación del plano bidimensional.
    manejador = new ManejadorEntrada(this); // Reserva espacio para el capturador de eventos de hardware.
    manejador->iniciar(); // Inicia el desdoblamiento del proceso de lectura.

    jugadores.push_back(new Jugador(1, 1, 1, this)); // Instancia al jugador primario en la coordenada superior izquierda.
    jugadores[0]->iniciar(); // Arranca el motor cinemático del primer jugador.

    if (modoJuego == 2) { // Comprueba si se debe instanciar un rival competitivo.
        jugadores.push_back(new Jugador(2, 11, 13, this)); // Instancia al jugador secundario en la esquina inferior derecha.
        jugadores[1]->iniciar(); // Arranca el motor cinemático del oponente.
    }

    int cantidadEnemigos = 2 + nivel; // Calcula un incremento progresivo de adversarios basado en el nivel actual.
    for (int i = 0; i < cantidadEnemigos; i++) { // Ejecuta la creación repetitiva de oponentes.
        int tipoIA = i % 3; // Asigna patrones de comportamiento matemáticamente balanceados.
        enemigos.push_back(new Enemigo(11 - i, 13 - i, tipoIA, this)); // Instancia la IA en posiciones distanciadas del jugador primario.
        enemigos[i]->iniciar(); // Enciende los algoritmos de patrullaje.
    }
}

void MotorJuego::ejecutar() { 
    while (estaActivo()) { // Mantiene vivo el renderizado mientras la bandera global persista.
        pthread_mutex_lock(&mutexEstado); // Solicita exclusión mutua para consultar variables de control.
        while (pausado && juegoActivo) { // Evalúa si existe una solicitud de interrupción activa.
            pthread_cond_wait(&condPausa, &mutexEstado); // Duerme el refresco visual pasivamente ahorrando recursos energéticos.
        }
        pthread_mutex_unlock(&mutexEstado); // Libera el candado tras revisar el estado de control.
        
        int vidasP1 = (jugadores.size() > 0) ? jugadores[0]->obtenerVidas() : 0; // Extrae y protege la salud del usuario principal.
        int vidasP2 = (jugadores.size() > 1) ? jugadores[1]->obtenerVidas() : 0; // Extrae y protege la salud del usuario secundario.
        
        mapa.dibujar(vidasP1, vidasP2, puntos, nivel, modoJuego, obtenerMensaje()); // Ejecuta el vaciado de la matriz visual en la terminal del sistema operativo.
        verificarEstadoNivel(); // Analiza lógicamente si se cumplieron las condiciones de victoria de la etapa.
        usleep(50000); // Impone una pausa de 50 milisegundos para lograr estabilidad visual en los fotogramas.
    }
}

void MotorJuego::verificarEstadoNivel() {
    pthread_mutex_lock(&mutexEstado); // Bloquea la memoria para evitar lecturas de hilos incompletos.
    bool enemigosVivos = false; // Supone que el tablero fue despejado de amenazas.
    for (Enemigo* e : enemigos) { // Itera la lista completa de inteligencias artificiales.
        if (e->estaVivo()) enemigosVivos = true; // Si detecta un proceso activo, rechaza el avance de nivel.
    }
    pthread_mutex_unlock(&mutexEstado); // Entrega el candado finalizada la inspección general.

    if (!enemigosVivos && modoJuego == 1) { // Determina si la condición de victoria se cumple en solitario.
        nivel++; // Aumenta el multiplicador de dificultad.
        detener(); // Pausa los hilos actuales para evitar fallos de segmentación.
        usleep(500000); // Pausa la transición brevemente para que la terminal visualice la victoria parcial.
        juegoActivo = true; // Reactiva el motor de estados global.
        limpiarNivel(); // Asegura de que no queden hilos zombies o posiciones en caché del nivel anterior.
        inicializarNivel(); // Carga y ensambla el entorno para el siguiente desafío.
    }
}

void MotorJuego::sumarPunto(int cantidad) { // Agrega recompensas numéricas a la partida.
    pthread_mutex_lock(&mutexEstado); // Solicita paso exclusivo para evitar desincronización de puntajes.
    puntos += cantidad; // Agrega la bonificación enviada.
    pthread_mutex_unlock(&mutexEstado); // Permite acceso concurrente nuevamente.
}

void MotorJuego::registrarBomba(int variacion) { // Controla el límite dinámico de explosivos.
    pthread_mutex_lock(&mutexEstado); // Bloquea el entorno de estados.
    bombasActivas += variacion; // Modifica la contabilidad de la munición.
    pthread_mutex_unlock(&mutexEstado); // Libera la herramienta de control.
}

void MotorJuego::alternarPausa() { // Altera el flujo de tiempo del programa.
    pthread_mutex_lock(&mutexEstado); // Pide el candado para mutar la lógica atómica.
    pausado = !pausado; // Invierte el estado lógico booleano de forma eficiente.
    if (!pausado) { // Si el resultado indica reanudación de actividades.
        pthread_cond_broadcast(&condPausa); // Despierta simultáneamente a todos los hilos colgados en la señal condicional.
    }
    pthread_mutex_unlock(&mutexEstado); // Retira la exclusión.
}

bool MotorJuego::estaActivo() { // Getter concurrente de ejecución.
    pthread_mutex_lock(&mutexEstado); // Protege lectura.
    bool estado = juegoActivo; // Copia contenido de memoria.
    pthread_mutex_unlock(&mutexEstado); // Suelta candado.
    return estado; // Responde con el estado copiado.
}

bool MotorJuego::estaPausado() { // Getter concurrente de congelamiento.
    pthread_mutex_lock(&mutexEstado); // Protege lectura.
    bool estado = pausado; // Copia contenido de memoria.
    pthread_mutex_unlock(&mutexEstado); // Suelta candado.
    return estado; // Responde con la bandera.
}

void MotorJuego::detener() { // Interrumpe de forma severa el bucle de juego.
    pthread_mutex_lock(&mutexEstado); // Asegura la sección para sobrescribir la orden.
    juegoActivo = false; // Fuerza el fin del bucle base.
    pthread_cond_broadcast(&condPausa); // Evita interbloqueos despertando hilos colgados temporalmente.
    pthread_mutex_unlock(&mutexEstado); // Habilita finalización de todos los procesos.
}

void MotorJuego::establecerMensaje(std::string mensaje) { // Sobrescribe el texto informativo de forma segura.
    pthread_mutex_lock(&mutexEstado); // Solicita el bloqueo de la memoria compartida.
    mensajeGlobal = mensaje; // Guarda el nuevo texto que notifican los poderes.
    pthread_mutex_unlock(&mutexEstado); // Habilita el acceso para el resto de hilos.
}

std::string MotorJuego::obtenerMensaje() { // Consulta el texto para imprimirlo en pantalla.
    pthread_mutex_lock(&mutexEstado); // Bloquea la variable para prevenir lecturas corruptas.
    std::string m = mensajeGlobal;
    pthread_mutex_unlock(&mutexEstado); // Devuelve el acceso a la memoria.
    return m; // Entrega el texto consultado.
}

Mapa* MotorJuego::obtenerMapa() { return &mapa; } /
pthread_mutex_t* MotorJuego::obtenerMutexEstado() { return &mutexEstado; } /
pthread_cond_t* MotorJuego::obtenerCondPausa() { return &condPausa; } 
int MotorJuego::obtenerModo() { return modoJuego; } // Informa bajo qué reglas de modalidad opera.
int MotorJuego::obtenerMaxBombas() { return maxBombas; } // máximo de bombas.