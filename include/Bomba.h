/*
 * Autor: Franco Paiz
 * Definición de la clase Bomba.
 * Esta clase representa las bombas colocadas por los jugadores y administra
 * su activación, explosión y efectos sobre el mapa.
 */

#ifndef BOMBA_H
#define BOMBA_H

#include "MotorJuego.h"
#include <pthread.h>

/*
 * Clase encargada de gestionar una bomba dentro del juego.
 * Cada bomba funciona mediante un hilo independiente que controla
 * el tiempo de espera antes de la explosión.
 */
class Bomba {
private:
    // Hilo que ejecuta la lógica de la bomba.
    pthread_t hiloBomba;

    // Referencia al motor principal del juego.
    MotorJuego* motor;

    // Posición de la bomba en el mapa.
    int posX;
    int posY;

    // Alcance de la explosión.
    int radio;

    // Función ejecutada por el hilo de la bomba.
    static void* rutinaBomba(void* arg);

public:
    /*
     * Constructor de la bomba.
     * Recibe la posición inicial, el radio de explosión y el motor del juego.
     */
    Bomba(int x, int y, int r, MotorJuego* m);

    // Destructor de la clase.
    ~Bomba();

    // Inicia el hilo encargado de la detonación.
    void activar();
};

#endif