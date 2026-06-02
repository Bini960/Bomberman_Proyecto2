#ifndef MANEJADORENTRADA_H
#define MANEJADORENTRADA_H

#include "MotorJuego.h" // Dependencias del motor.
#include <pthread.h>    // Manejo de hilos.


// Gestiona la entrada del teclado.
class ManejadorEntrada {
private:

    // Hilo encargado de capturar entradas.
    pthread_t hiloEntrada;

    // Referencia al motor del juego.
    MotorJuego* motor;

    // Rutina ejecutada por el hilo.
    static void* rutinaEntrada(void* arg);

public:

    // Constructor.
    ManejadorEntrada(MotorJuego* m);

    // Destructor.
    ~ManejadorEntrada();

    // Inicia el hilo de captura.
    void iniciar();
};

#endif