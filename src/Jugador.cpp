#include "Jugador.h" // Importa las propiedades internas y estructura atómica general de su propia entidad física interactiva virtualizada.
#include "Bomba.h" // Requiere la definición funcional completa para instanciar explosivos dinámicamente y llamar su creador y destructor con seguridad.
#include <unistd.h> // Habilita las pausas de proceso para asimilar pausas cortas milisegundos evitando bloqueos o saltos de cuadros inmanejables por el humano controlando la cinemática rítmicamente estable.
#include <cstdlib> // Llama a la librería de manipulación matemática para cálculos y suposiciones al azar o generadores numéricos seudoaleatorios impredecibles en el manejo de caídas de elementos valiosos.
#include <time.h> // Habilita las funciones para consultar la hora base unificada del sistema operativo proporcionando exactitud y estricta calibración en el manejo del control del paso del tiempo y decaimientos limitados de potenciadores orgánicos y ventajas algorítmicas temporales.

extern char teclaP1; // Extrae y adopta conocimiento de la variable global de pulsación compartida y actualizada del primer participante humano, asimilada en la etapa de manejo de consola base compartida, pre-compilada, resolviendo la transmisión global de hardware a la red abstracta algorítmica de interrupción sin acople fijo y constante y enrutamiento simple directo de lectura.
extern char teclaP2; // Extrae y acopla la información direccional secundaria para el teclado aislado resolviendo entradas superpuestas conflictivas durante competencias locales en la terminal única.
extern pthread_mutex_t mutexTecla; // Pide el acceso restringido central y compartido en la lectura general asincrónica solicitando control directo, protegiendo lecturas y bloqueando variables sensibles transitorias entre hilos concurrentes que procesan al ritmo de la terminal veloz para evadir lecturas colapsadas simultáneas de memoria entre pares competidores y oponentes y flujos primarios interconectados.

Jugador::Jugador(int idJugador, int x, int y, MotorJuego* m) { // Carga configuración posicional.
    id = idJugador; // Fija rol único y específico identificador de entrada lógica interna en base a prioridades.
    posX = x; // Establece altura inicial y eje matricial lateral original en pasillos lógicos y celdas del bloque virtual base vacío e inexplorado.
    posY = y; // Fija el avance original del eje opuesto e inicia profundidad de coordenada espacial inyectando posición pura a variable en el entorno de la cuadrícula abstracta y gráfica compartida principal y maestra del motor base maestro predeterminado de simulación general persistente global del mapa en turno para la entidad recién surgida viva del plano inicial instanciado abstracto numérico interno inactivo inicial inalterable pre-lógico del inicio posicional virtual base.
    vidas = 3; // Otorga el contador por defecto normado globalizando la resistencia y tope salud ininterrumpida base inalterable total del sujeto primario humano sin alteración antes de los perjuicios.
    radioBomba = 2; // Otorga magnitud estándar nativa y extensión natural predefinida radial expansiva sin modificaciones dinámicas base originales ofensivas operativas del elemento en detonación por cada unidad de artefacto sin alteración acumulativa y en magnitud pre-definida nativa en rango original pre-establecido inicial base estándar sin alteración modificativa a las características iniciales operativas instanciadas en memoria por la entidad por defecto desde inicio absoluto sin mejoras numéricas base base predefinidas estandarizadas e intactas nativas base pre establecidas inamovibles.
    atraviesaMuros = false; // Bloquea permiso físico nativo asumiendo choque forzoso lógico por solidez.
    celdaAnterior = '.'; // Guarda texturas neutrales asumiendo generación ininterrumpida en piso vacío al nacer.
    tiempoAtraviesaMuros = 0; // Configura cronómetro caducado en registro cero Unix previene excepciones.
    motor = m; // Cierra conexión acoplando puntero persistente global al acceso cruzado con el juego.
}

Jugador::~Jugador() { // Procesa fin atómico reciclando memoria OS y cortando recursos lógicos terminales con recolección dinámica.
    pthread_join(hiloJugador, NULL); // Recompone hilos sueltos aguardando cierre en ejecución de bucles dependientes inter-niveles garantizando limpieza base estricta antes de transitar por recolección destructiva automática final.
}

void Jugador::iniciar() { // Realiza llamada inicial al OS para solicitar fragmentación temporal.
    pthread_create(&hiloJugador, NULL, rutinaJugador, (void*)this); // Ensambla hilo entregando referencia explícita del objeto local genérico hacia el método maestro emulando paralelismo base con encapsulamiento propio.
}

void* Jugador::rutinaJugador(void* arg) { // Conduce comportamiento de vida de la entidad local y ciclos operacionales interactivos manuales controlados por hardware base general.
    Jugador* j = (Jugador*)arg; // Realiza cast del genérico inyectando puntero formal para leer características nativas exclusivas dentro de la ramificación concurrente asíncrona temporal base.
    MotorJuego* m = j->motor; // Establece proxy directo resolviendo consultas y actualizaciones hacia la clase administradora que contiene todos los recursos del laberinto virtual matriz global de interacción cruzada base.
    int retardo = 80000; // Define la constante osciladora que frena la excesiva iteración POSIX calibrando percepción visual y respuesta humana táctica en microsegundos fijos no variables en bucle regular activo predefinido constante de actualización.

    while (m->estaActivo()) { // Observa perpetuamente al motor y finaliza asíncronamente si el modo se detiene forzosamente externa.
        pthread_mutex_lock(m->obtenerMutexEstado()); // Solicita permiso al gestor atómico y paraliza lectura y ejecución de evaluación preventiva para evitar errores cruzados de consulta asíncrona base compartida previene variables inconsistentes durante la decisión central base inmanejable aleatoria de múltiples llamadas simultáneas operativas atómicas inalterables protegidas restrictivas en ciclo pasivo pasmado de escucha suspendida general ininterrumpida lógica restrictiva.
        while (m->estaPausado() && m->estaActivo()) { // Previene gasto energético si el sistema entra en espera voluntaria humana suspendiendo lógicas cinemáticas en conjunto y sin avance temporal ficticio y paralizando bucles iterativos base.
            pthread_cond_wait(m->obtenerCondPausa(), m->obtenerMutexEstado()); // Bloquea flujo pasivamente escuchando señales desde el menú sin sobrecargar núcleo y aguarda activación remota despertando coordinado de nuevo reanudando operación y flujo reestableciendo exclusión natural protectora temporal.
        }
        pthread_mutex_unlock(m->obtenerMutexEstado()); // Libera puerta lógicamente y continúa lectura.

        if (j->atraviesaMuros && difftime(time(NULL), j->tiempoAtraviesaMuros) >= 2.0) { 
            j->atraviesaMuros = false; // Revoca el permiso algorítmico para evadir colisiones en memoria.
            
            if (j->celdaAnterior == '#' || j->celdaAnterior == 'X') { // Evalúa si la entidad quedó atrapada dentro de una estructura inamovible en la matriz.
                m->obtenerMapa()->actualizarCelda(j->posX, j->posY, j->celdaAnterior); // Sanea la coordenada actual restituyendo la geometría original.
                bool reubicado = false; // Bandera atómica local para frenar la búsqueda.
                
                // Ejecuta un barrido radial para encontrar la celda de memoria libre más cercana.
                for (int radioBusqueda = 1; radioBusqueda < 15 && !reubicado; radioBusqueda++) { 
                    for (int i = 1; i < 12 && !reubicado; i++) { // Navega el límite vertical de la memoria del tablero.
                        for (int k = 1; k < 14 && !reubicado; k++) { // Navega el límite horizontal de hardware.
                            if (abs(j->posX - i) + abs(j->posY - k) <= radioBusqueda) { // Calcula proximidad para minimizar desplazamientos drásticos.
                                if (m->obtenerMapa()->obtenerCelda(i, k) == '.') { // Verifica disponibilidad de celda segura sin colisión.
                                    j->posX = i; // Sobrescribe posición X con el área segura encontrada.
                                    j->posY = k; // Sobrescribe posición Y atómicamente.
                                    j->celdaAnterior = '.'; // Restablece el suelo inmaculado por defecto.
                                    reubicado = true; // Cierra el algoritmo de búsqueda para liberar ciclos del CPU.
                                } 
                            } 
                        } 
                    } 
                } 
                m->establecerMensaje("Efecto caducado. Expulsado del muro a zona segura."); // Emite notificación de reubicación espacial a la interfaz.
            } else {
                m->establecerMensaje("El efecto de atravesar muros ha caducado."); // Actualiza GUI sin desplazar matriz.
            }
        }

        char celdaActual = m->obtenerMapa()->obtenerCelda(j->posX, j->posY); // Chequea suelo actual detectando trampas o amenazas simultáneas escritas por entes paralelos sin percance visual asíncrono.
        if (celdaActual == '~' || celdaActual == 'E') { // Cruza parámetros letales térmica o física certificando colisión mortal con onda cruzada o IA.
            j->vidas--; // Recorta salud numéricamente restando reserva natural de forma irreversible.
            if (j->vidas <= 0) { // Asimila condición fatal cero y tramita cierre permanente del participante humano en proceso base.
                m->obtenerMapa()->actualizarCelda(j->posX, j->posY, j->celdaAnterior); // Retira rastro pintando fondo preexistente inmaculado eliminando parpadeo fantasma al desaparecer de pantalla finalizada la vida base y dejando el plano despejado de su representación visual.
                if (m->obtenerModo() == 1) m->detener(); // Detiene campaña y emite interrupción si opera sin rival forzando retorno hacia panel base administrativo menú global cerrando entorno interactivo.
                return NULL; // Devuelve estado nulo a OS muriendo en silencio dinámico atómicamente base.
            }
            m->obtenerMapa()->actualizarCelda(j->posX, j->posY, j->celdaAnterior); // Corrige textura borrando silueta muerta al ser eliminado con reserva disponible para no superponer imágenes durante reaparición.
            j->posX = (j->id == 1) ? 1 : 11; // Impone coordenada de seguridad X basada en identificador devolviendo al origen neutral sin interferencias posicionales inminentes fatales inamovibles.
            j->posY = (j->id == 1) ? 1 : 13; // Restablece eje Y paralelo neutral.
            
            j->radioBomba = 2; // Reinicia atributos de explosivo penalizando la caída al perder la carga adquirida aleatoriamente y volviendo a su parámetro estándar normal inicial mínimo funcional.
            j->atraviesaMuros = false; // Remueve poder táctico evasivo restaurando condición de colisión sólida normal tras fallecer reseteando modificadores temporales.
            j->celdaAnterior = '.'; // Restablece conocimiento espacial al suelo vacío originario.
        }

        char accion = 0; // Prepara recipiente vacío y local ignorando variables viejas transitorias asíncronas no evaluadas.
        pthread_mutex_lock(&mutexTecla); // Traba memoria asimilando input hardware evitando sobrescritura cruzada del teclado mixto paralelo local con el otro usuario humano y resguardando extracción inalterable.
        if (j->id == 1 && teclaP1 != 0) { // Lee caché de usuario primario descartando vacío.
            accion = teclaP1; // Extrae instrucción y mueve a recipiente asíncrono de función operativa.
            teclaP1 = 0; // Traga orden previniendo repetición autómata.
        } else if (j->id == 2 && teclaP2 != 0) { // Lee variante secundaria del opositor en hardware anidado compartido.
            accion = teclaP2; // Copia instrucción separada de modo competitivo.
            teclaP2 = 0; // Consume la variable al instante y estabiliza lectura base asíncrona terminal.
        }
        pthread_mutex_unlock(&mutexTecla); // Destraba escucha y reabre canal hardware global de forma segura a nuevos datos OS continuos de tipeo humano sin retraso en memoria temporal.

        int nx = j->posX; // Proyecta sombra teórica de matriz X para deducciones previas a escritura.
        int ny = j->posY; // Proyecta matriz Y anticipando vectores direccionales lógicos matemáticos crudos y evalúa solidez de casillas colindantes posicionales puras inmutables.
        
        if ((j->id == 1 && accion == 'w') || (j->id == 2 && accion == 'U')) nx--; // Resta coordenada simulando paso ascendente hacia norte direccional general del plano.
        if ((j->id == 1 && accion == 's') || (j->id == 2 && accion == 'D')) nx++; // Suma empujando descenso hacia sur cartesiano relativo de matriz invertida general terminal OS.
        if ((j->id == 1 && accion == 'a') || (j->id == 2 && accion == 'L')) ny--; // Decrementa eje Y girando al oeste izquierdo matriz interna base del vector espacial 2D.
        if ((j->id == 1 && accion == 'd') || (j->id == 2 && accion == 'R')) ny++; // Incrementa apuntando al este derecho matriz completando brújula base posicional direccional controlable manual interactiva generalizada adaptada del modelo físico abstracto del arreglo matricial gráfico base funcional lógicamente y coherente visual e iterativa en bucle central POSIX base.

        if ((j->id == 1 && accion == 'f') || (j->id == 2 && accion == 'E')) { // Dispara condicional de agresión física colocando explosivos independientemente del mapeo direccional al detectar código de detonación.
            Bomba* b = new Bomba(j->posX, j->posY, j->radioBomba, m); // Reserva heap delegando detonador con radio dinámico actualizado por power ups de matriz paralela al motor en función de memoria asíncrona con independencia algorítmica.
            b->activar(); // Invoca método que desliga el hilo paralelo destructivo atado al tiempo OS liberando responsabilidad del jugador que puede alejarse.
        } else if (nx != j->posX || ny != j->posY) { // Asegura de que exista diferencial y no consumo vacío de CPU.
            char celda = m->obtenerMapa()->obtenerCelda(nx, ny); // Muestrea solidez y objeto frontal futuro consultando atómicamente.
            
            if (celda == '.' || celda == '+' || (j->atraviesaMuros && (celda == '#' || celda == 'X'))) { // Concede acceso validando vacío, recompensa o estado fantasma activo sobre sólidos ignorando límite original de juego base estricto y permitiendo reescribir coordenadas posicionales internas abstractas en función del parámetro modificado temporal dinámico local aleatorio sin alteración destructiva inicial base inminente.
                if (celda == '+') { // Procesa adquisición y otorga bonificaciones resolviendo aleatoriedad.
                    int tipoPoder = rand() % 2; // Pide número impredecible al hardware acotado entre cero y uno.
                    if (tipoPoder == 0) { // Otorga mejora predeterminada cero.
                        j->radioBomba += 2; // Ensancha magnitud ofensiva permanente sumando dos baldosas a su registro táctico propio ofensivo.
                        m->establecerMensaje("Mejora obtenida: +2 Casillas de expansion."); // Acopla información textual para GUI.
                    } else { // Otorga variante alterna aleatoria uno.
                        j->atraviesaMuros = true; // Activa permiso estructural lógico fantasma inestable de paso irrestricto asíncrono temporal base sin eliminación física interactiva atómica de texturas.
                        j->tiempoAtraviesaMuros = time(NULL); // Graba un registro fotográfico del segundo de colisión usando librería temporal OS cruda.
                        m->establecerMensaje("Mejora obtenida: Modo fantasma activado (2s)."); // Informa en panel dinámico de estado global el beneficio.
                    }
                    celda = '.'; // Asimila consumo y borra premio convirtiéndolo en pasillo vacío natural borrando del laberinto atómicamente e instanciando uso destructivo y adquisitivo completo irrecuperable en matriz gráfica del escenario base actual.
                }
                
                m->obtenerMapa()->actualizarCelda(j->posX, j->posY, j->celdaAnterior); // Corrige celda antigua insertando el respaldo de textura y sanando el paso asíncrono.
                j->celdaAnterior = celda; // Respaldos textura futura a invadir para conservar pasillos y texturas estables no destructibles bajo paso fantasma en entorno de variables controladas inalterables temporalmente y estables visualmente en la renderización del plano bidimensional.
                j->posX = nx; // Consuma cinemática real.
                j->posY = ny; // Fija salto asíncrono posicional matriz de forma atómica en variable de hilo propio aislado protegiendo memoria y delegando paso general completo y coherente algorítmico natural.
            } else if (celda == 'E') { // Tropiezo fatal inducido deliberado por choque frontal.
                j->vidas--; // Remueve reserva natural sin piedad ni condicional de escudo restando la cuenta local entera inmutable.
                if (j->vidas <= 0) { // Cierra y expulsa al perecer sin resguardo vital acumulativo remanente cerrando opciones competitivas del hilo asíncrono general y abortando ejecución en ciclo iterativo de estado POSIX base.
                    m->obtenerMapa()->actualizarCelda(j->posX, j->posY, j->celdaAnterior); // Limpia área e imprime textura sanando escena al desaparecer usuario completamente para estabilizar visión y entorno gráfico atómico de competidores vivos en modos simultáneos OS multijugador local interactivo sin colisiones fantasmas residuales ni texturas no actualizadas de personajes nulos o caducos visualmente atascados.
                    if (m->obtenerModo() == 1) m->detener(); // Manda señal de baja parando todo evento si no hay otro usuario secundario operativo de forma atómica en el sistema del nivel forzando revisión general pasiva.
                    return NULL; // Anula la carga base en rama de la CPU desvinculándose de las colisiones en el contexto general.
                }
                m->obtenerMapa()->actualizarCelda(j->posX, j->posY, j->celdaAnterior); // Fuga tras perder vida devolviendo texturas de respaldo y asumiendo castigo espacial borrando parpadeo.
                j->posX = (j->id == 1) ? 1 : 11; // Castiga al usuario con regreso remoto forzado hacia los bordes asignados por el origen reseteando todo progreso posicional en área ofensiva forzadamente sin colisiones.
                j->posY = (j->id == 1) ? 1 : 13; // Culmina reposicionamiento cardinal y limpia trayectoria previa completamente inestable.
                
                j->radioBomba = 2; // Resetea progresión eliminando daño amplificado.
                j->atraviesaMuros = false; // Quita habilidad espectral por muerte devolviendo al origen de limitaciones posicionales y reglas sólidas de colisiones naturales de matriz.
                j->celdaAnterior = '.'; // Olvida memoria táctica y se para en piso nuevo.
            }
        }
        
        m->obtenerMapa()->actualizarCelda(j->posX, j->posY, (j->id == 1) ? 'P' : 'Q'); // Aplasta memoria sobreponiendo el sprite humano con la actualización visual correcta y validada sobre la terminal a alta velocidad controlada en matriz atómica sincronizada por el candado base del arreglo y el mapa.
        usleep(retardo); // Duerme la acción de forma exacta consumiendo el resto de fotogramas sin acelerar o agotar el procesador base estabilizando carga de hardware natural ininterrumpida.
    }
    return NULL; // Se vacía el hilo resolviendo cierre.
}

int Jugador::obtenerVidas() { return vidas; } // Transmite variables locales al lector panel de estadísticas lateral proyectando resultados íntegros.