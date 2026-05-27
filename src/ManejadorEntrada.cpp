#include "ManejadorEntrada.h" // Incluye el headerdel manejador correspondientes.
#include <iostream>
#include <termios.h> // Contiene las estructuras para modificar los modos de la consola.
#include <fcntl.h> // Proporciona las constantes para deshabilitar el bloqueo de lectura.
#include <unistd.h> // Habilita las llamadas al sistema como read.

ManejadorEntrada::ManejadorEntrada(MotorJuego* m) { // Implementación del constructor.
    motor = m; // Vincula el puntero del motor global.
}

ManejadorEntrada::~ManejadorEntrada() { // Implementación del destructor.
    pthread_join(hiloEntrada, NULL); // Espera la finalización correcta del hilo lector antes de destruir.
}

void ManejadorEntrada::iniciar() { // Llama a la construcción del proceso asíncrono.
    pthread_create(&hiloEntrada, NULL, rutinaEntrada, (void*)motor); // Crea el hilo asíncrono para el teclado.
}

void* ManejadorEntrada::rutinaEntrada(void* arg) { // Función paralela que procesa la entrada del teclado.
    MotorJuego* motorJuego = (MotorJuego*)arg; // Convierte el argumento genérico al tipo del motor de juego.
    struct termios viejo, nuevo; // Declara las estructuras para salvar y alterar configuraciones.
    tcgetattr(STDIN_FILENO, &viejo); // Resguarda los valores originales de la terminal actual.
    nuevo = viejo; // Copia las propiedades existentes para editarlas de forma segura.
    nuevo.c_lflag &= ~(ICANON | ECHO); // Remueve el modo canónico y el eco de caracteres en pantalla.
    tcsetattr(STDIN_FILENO, TCSANOW, &nuevo); // Sobrescribe los parámetros de forma inmediata.
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0); // Extrae las banderas operativas del archivo de entrada.
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK); // Activa el modo de lectura no bloqueante de forma segura.

    while (motorJuego->estaActivo()) { // Se ejecuta de forma continua mientras la partida persista.
        char tecla; // Variable auxiliar para almacenar el carácter presionado.
        if (read(STDIN_FILENO, &tecla, 1) > 0) { // Intenta extraer un byte de información del teclado.
            if (tecla == 'q' || tecla == 'Q') { // Evalúa si el usuario solicita salir.
                motorJuego->detener(); // Cambia el estado del sistema para forzar el apagado.
            } else if (tecla == 'p' || tecla == 'P') { // Evalúa si se solicita pausar la ejecución.
                motorJuego->alternarPausa(); // Invierte de forma segura el estado de pausa.
            }
        }
        usleep(20000); // Descansa el hilo por 20 milisegundos para no saturar el procesador
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &viejo); // Restaura el comportamiento estándar de la terminal
    return NULL; 
}