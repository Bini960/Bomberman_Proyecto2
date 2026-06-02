#include "ManejadorEntrada.h" // Procesa declaraciones previas.
#include <iostream> // Agrega utilidades base de captura manual.
#include <termios.h> // Expone registros del kernel UNIX de consola local para cambiar su comportamiento interactivo físico.
#include <fcntl.h> // Modifica atributos del descriptor de archivos integrados a nivel binario.
#include <unistd.h> // Despliega la capacidad del proceso POSIX base.

// Se separan las entradas de hardware globalmente mediante memoria estática para que la matriz motora P1 y P2 operen en simultáneo sin causar pérdida de fotogramas asíncronos.
char teclaP1 = 0; // Reserva variable temporal de jugador uno.
char teclaP2 = 0; // Reserva almacenamiento temporal aislado de jugador rival.
pthread_mutex_t mutexTecla = PTHREAD_MUTEX_INITIALIZER; // Declara macro estática de bloqueo directo aplicable al input de pulsaciones.

ManejadorEntrada::ManejadorEntrada(MotorJuego* m) { motor = m; } // Puntero conectivo asignado y vinculado.
ManejadorEntrada::~ManejadorEntrada() { pthread_join(hiloEntrada, NULL); } // Somete a la limpieza dinámica forzando acople antes del cierre de proceso destructor.
void ManejadorEntrada::iniciar() { pthread_create(&hiloEntrada, NULL, rutinaEntrada, (void*)motor); } // Reserva segmento de pila RAM despachando hilo funcional.

void* ManejadorEntrada::rutinaEntrada(void* arg) { // Función principal asíncrona interactiva.
    MotorJuego* motorJuego = (MotorJuego*)arg; // Moldea tipo primitivo a bloque de configuración general.
    struct termios viejo, nuevo; // Asigna dos bloques abstractos al manejo periférico.
    tcgetattr(STDIN_FILENO, &viejo); // Copia el registro maestro nativo guardando propiedades de consola clásica.
    nuevo = viejo; // Transmite estructura clonada para modificaciones inmediatas transitorias.
    nuevo.c_lflag &= ~(ICANON | ECHO); // Modula puertas lógicas bit a bit suprimiendo enter restrictivo y eco por pantalla del carácter tipeado.
    tcsetattr(STDIN_FILENO, TCSANOW, &nuevo); // Fija configuraciones aplicando parámetros a la brevedad.
    
    int flagsOriginales = fcntl(STDIN_FILENO, F_GETFL, 0); // Extrae y resguarda indicadores y estatus fundamentales operativos en el momento exacto anterior a los cambios.
    fcntl(STDIN_FILENO, F_SETFL, flagsOriginales | O_NONBLOCK); // Conmuta descriptor sumando propiedad asíncrona no-bloqueante evadiendo pausa total del programa al consultar teclado de hardware.

    while (motorJuego->estaActivo()) { // Observador cíclico no destructivo.
        char tecla; // Asigna bit temporal primitivo en el bucle local para no saturar memoria RAM externa.
        if (read(STDIN_FILENO, &tecla, 1) > 0) { // Evalúa condición de recepción de bytes sin detener sistema central usando descriptor interno OS de lectura asíncrona.
            if (tecla == 'q' || tecla == 'Q') { // Procesa atajo destructivo predefinido forzosamente.
                motorJuego->detener(); // Enruta ejecución bajando bandera maestra general.
            } else if (tecla == 'p' || tecla == 'P') { // Procesa atajo de interrupción lógica suspendida.
                motorJuego->alternarPausa(); // Convoca estado de sueño general simultáneo en las funciones esclavas.
            } else if (tecla == 27) { // Detecta primer valor decodificado ASCII correspondiente al código de escape primitivo de teclas complejas de dirección.
                char seq[2]; // Prepara matriz de apoyo consecutiva al escape para discernir tipo de comando expandido ANSI.
                if (read(STDIN_FILENO, &seq[0], 1) > 0 && read(STDIN_FILENO, &seq[1], 1) > 0) { // Absorbe dos bytes continuos comprobando finalización de bloque ANSI detectado.
                    if (seq[0] == '[') { // Discrimina segundo byte secuencial comprobando corchete característico de secuencias direccionales estándar.
                        pthread_mutex_lock(&mutexTecla); // Bloquea espacio estático protegiendo información volátil contra consumo simultáneo ajeno y corrupciones en memoria inter-hilo.
                        if (seq[1] == 'A') teclaP2 = 'U'; // Traduce señal superior traduciéndolo a carácter de desplazamiento.
                        if (seq[1] == 'B') teclaP2 = 'D'; // Determina caída del vector.
                        if (seq[1] == 'C') teclaP2 = 'R'; // Señala traslado este.
                        if (seq[1] == 'D') teclaP2 = 'L'; // Emite comando lateral oeste mapeando control numérico.
                        pthread_mutex_unlock(&mutexTecla); // Libera contención abriendo canales de transporte.
                    }
                }
            } else if (tecla == '\n' || tecla == '\r') { // Inspecciona llegada de comando detonador paralelo por defecto del retorno de carro.
                pthread_mutex_lock(&mutexTecla); // Contención mutua atómica para eventos de artillería.
                teclaP2 = 'E'; // Estandariza la pulsación en formato simple asimilable al código condicional primario.
                pthread_mutex_unlock(&mutexTecla); // Entrega recursos del subsistema asíncrono liberado.
            } else { // Si recibe alfabeto clásico.
                pthread_mutex_lock(&mutexTecla); // Retiene memoria asumiendo control primario exclusivo.
                teclaP1 = tecla; // Actualiza búfer central sin retrasar terminal.
                pthread_mutex_unlock(&mutexTecla); // Retorna a ejecución vacía en modo escucha.
            }
        }
        usleep(15000); // Emite instrucción a CPU relajando hardware minimizando llamadas redundantes del núcleo durante polling agresivo continuo.
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &viejo); // Limpia las afectaciones forzando terminal a retornar a modo nativo original sin corrupciones permanentes al ambiente externo terminal.
    fcntl(STDIN_FILENO, F_SETFL, flagsOriginales); // Restaura comportamiento estricto bloqueante previniendo interbloqueo del menú infinito y regresando control absoluto a flujos de entrada en librerías estándar C++.
    
    return NULL; // Se cierra el proceso del hilo con entrega limpia para recolección de POSIX.
}