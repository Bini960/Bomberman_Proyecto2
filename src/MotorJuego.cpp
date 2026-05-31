#include "MotorJuego.h" // Enlaza el archivo de header
#include "Jugador.h" // Permite instanciar objetos del tipo personaje.
#include "Enemigo.h" // Permite instanciar objetos del tipo adversario.
#include "ManejadorEntrada.h" // Permite instanciar el hilo lector del teclado.
#include <unistd.h> 

MotorJuego::MotorJuego() { 
    juegoActivo = true; // Establece el ciclo de vida inicial en verdadero.
    pausado = false; // Define que la partida arranca sin interrupciones.
    pthread_mutex_init(&mutexEstado, NULL); // Inicializa el candado global del motor.
    pthread_cond_init(&condPausa, NULL); // Inicializa el mecanismo de suspensión.
    manejador = nullptr; // Inicializa el puntero del teclado en nulo por seguridad.
}

MotorJuego::~MotorJuego() { 
    detener(); // Asegura apagar el ciclo lógico antes de destruir objetos.
    pthread_mutex_destroy(&mutexEstado); // Libera los recursos del sistema operativo asignados al candado.
    pthread_cond_destroy(&condPausa); // Libera los recursos de la señal condicional.
    
    if (manejador != nullptr) { // Verifica si el objeto de entrada fue instanciado.
        delete manejador; // Libera la memoria reservada para el teclado.
    }
    for (Jugador* j : jugadores) { // Recorre el arreglo dinámico de personajes.
        delete j; // Libera el espacio de memoria de cada usuario.
    }
    for (Enemigo* e : enemigos) { // Recorre el arreglo dinámico de adversarios.
        delete e; // Libera el espacio de memoria de cada entidad autónoma.
    }
    jugadores.clear(); // Vacía los punteros residuales del vector de personajes.
    enemigos.clear(); // Vacía los punteros residuales del vector de adversarios.
}

void MotorJuego::inicializar() { 
    mapa.inicializarMapa(); // Construye los muros y pasillos en la matriz bidimensional.
    
    manejador = new ManejadorEntrada(this); // Reserva memoria para el módulo de entrada.
    manejador->iniciar(); // Dispara el hilo secundario para evitar el bloqueo del sistema.

    jugadores.push_back(new Jugador(1, 1, 1, this)); // Posiciona al jugador principal en la esquina superior.
    jugadores[0]->iniciar(); // Activa la lógica paralela del personaje.

    for (int i = 0; i < 4; i++) { // Itera cuatro veces para instanciar a los rivales iniciales.
        enemigos.push_back(new Enemigo(11, 13, 0, this)); // Reserva memoria y ubica al adversario en el tablero.
        enemigos[i]->iniciar(); // Despierta el hilo de inteligencia artificial del rival.
    }
}

void MotorJuego::ejecutar() { // Administra el refresco visual de la consola.
    while (estaActivo()) { // Mantiene el bucle operativo durante el ciclo de vida.
        pthread_mutex_lock(&mutexEstado); // Captura el candado para revisar variables delicadas.
        while (pausado && juegoActivo) { // Evalúa si existe una solicitud de suspensión temporal.
            pthread_cond_wait(&condPausa, &mutexEstado); // Duerme el hilo principal pasivamente sin saturar CPU.
        }
        pthread_mutex_unlock(&mutexEstado); // Suelta el candado tras verificar el estado.
        
        mapa.dibujar(); // Proyecta el estado actual de la matriz en la salida estándar.
        usleep(100000); // Retarda la iteración 100 milisegundos para mantener 10 fotogramas por segundo.
    }
}

void MotorJuego::alternarPausa() { // Modifica el flujo continuo de la simulación.
    pthread_mutex_lock(&mutexEstado); // Exige acceso exclusivo a las banderas de control.
    pausado = !pausado; // Alterna el valor lógico de falso a verdadero o viceversa.
    if (!pausado) { // Verifica si la orden corresponde a reanudar la marcha.
        pthread_cond_broadcast(&condPausa); // Despierta simultáneamente a todos los hilos inactivos.
    }
    pthread_mutex_unlock(&mutexEstado); // Retira el bloqueo de las banderas de control.
}

bool MotorJuego::estaActivo() { // Función consultora de la bandera principal.
    pthread_mutex_lock(&mutexEstado); // Cierra el acceso concurrente.
    bool estado = juegoActivo; // Extrae el valor actual en memoria.
    pthread_mutex_unlock(&mutexEstado); // Habilita el acceso a otros procesos.
    return estado; // Devuelve la resolución del ciclo de vida.
}

bool MotorJuego::estaPausado() { // Función consultora del mecanismo de suspensión.
    pthread_mutex_lock(&mutexEstado); // Protege la lectura contra modificaciones espontáneas.
    bool estado = pausado; // Extrae la bandera de interrupción temporal.
    pthread_mutex_unlock(&mutexEstado); // Cede el control del segmento de código crítico.
    return estado; // Devuelve la resolución actual de pausa.
}

void MotorJuego::detener() { // Procedimiento de apagado del programa.
    pthread_mutex_lock(&mutexEstado); // Asegura la sección para sobrescribir la orden de cierre.
    juegoActivo = false; // Fuerza el cierre de todos los bucles dependientes.
    pthread_cond_broadcast(&condPausa); // Previene que hilos suspendidos queden atrapados al salir.
    pthread_mutex_unlock(&mutexEstado); // Libera el sistema para procesar el apagado.
}

Mapa* MotorJuego::obtenerMapa() { // Expone el acceso controlado al entorno gráfico.
    return &mapa; // Entrega la dirección exacta del objeto administrador del tablero.
}

pthread_mutex_t* MotorJuego::obtenerMutexEstado() { // Facilita el mecanismo de sincronización.
    return &mutexEstado; // Entrega la dirección del candado para que las entidades evalúen la pausa.
}

pthread_cond_t* MotorJuego::obtenerCondPausa() { // Facilita la herramienta de descanso pasivo.
    return &condPausa; // Entrega la señal empleada en las rutinas de los hilos externos.
}