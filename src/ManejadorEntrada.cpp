#include "ManejadorEntrada.h" // Incluye el encabezado correspondiente.
#include <iostream>
#include <termios.h> // Configuración de la terminal.
#include <fcntl.h>   // Modo de lectura no bloqueante.
#include <unistd.h>  // Funciones del sistema.


// Inicializa el manejador de entrada.
ManejadorEntrada::ManejadorEntrada(MotorJuego* m) {
    motor = m;
}


// Espera la finalización del hilo.
ManejadorEntrada::~ManejadorEntrada() {
    pthread_join(hiloEntrada, NULL);
}


// Crea el hilo de lectura del teclado.
void ManejadorEntrada::iniciar() {
    pthread_create(&hiloEntrada, NULL, rutinaEntrada, (void*)motor);
}


// Procesa la entrada del usuario.
void* ManejadorEntrada::rutinaEntrada(void* arg) {
    MotorJuego* motorJuego = (MotorJuego*)arg;

    // Guarda y modifica la configuración de la terminal.
    struct termios viejo, nuevo;
    tcgetattr(STDIN_FILENO, &viejo);
    nuevo = viejo;
    nuevo.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &nuevo);

    // Activa la lectura no bloqueante.
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    // Mantiene la lectura mientras el juego esté activo.
    while (motorJuego->estaActivo()) {
        char tecla;

        // Procesa las teclas presionadas.
        if (read(STDIN_FILENO, &tecla, 1) > 0) {

            // Finaliza la partida.
            if (tecla == 'q' || tecla == 'Q') {
                motorJuego->detener();
            }

            // Pausa o reanuda el juego.
            else if (tecla == 'p' || tecla == 'P') {
                motorJuego->alternarPausa();
            }
        }

        // Reduce el uso del procesador.
        usleep(20000);
    }

    // Restaura la configuración original.
    tcsetattr(STDIN_FILENO, TCSANOW, &viejo);

    return NULL;
}