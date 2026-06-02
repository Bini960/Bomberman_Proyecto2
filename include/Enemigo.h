/*
 * Autor: Franco Paiz
 * Definición de la clase Enemigo.
 * Esta clase representa a los enemigos del juego y administra
 * su comportamiento, movimiento y estado dentro de la partida.
 */

#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "MotorJuego.h"
#include <pthread.h>

/*
 * Clase encargada de representar un enemigo en el mapa.
 * Cada enemigo se ejecuta mediante un hilo independiente
 * que controla sus movimientos y acciones.
 */
class Enemigo {
private:
    // Hilo asociado a la lógica del enemigo.
    pthread_t hiloEnemigo;

    // Referencia al motor principal del juego.
    MotorJuego* motor;

    // Posición actual del enemigo en el mapa.
    int posX;
    int posY;

    // Tipo de movimiento que utilizará el enemigo.
    int tipoMovimiento;

    // Indica si el enemigo sigue activo.
    bool vivo;

    // Función ejecutada por el hilo del enemigo.
    static void* rutinaEnemigo(void* arg);

public:
    /*
     * Constructor del enemigo.
     * Recibe la posición inicial, el tipo de movimiento y el motor del juego.
     */
    Enemigo(int x, int y, int tipo, MotorJuego* m);

    // Destructor de la clase.
    ~Enemigo();

    // Inicia el hilo encargado de controlar al enemigo.
    void iniciar();

    // Devuelve el estado actual del enemigo.
    bool estaVivo();
};

#endif/*
 * Autor: Franco Paiz
 * Definición de la clase Enemigo.
 * Esta clase representa a los enemigos del juego y administra
 * su comportamiento, movimiento y estado dentro de la partida.
 */

#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "MotorJuego.h"
#include <pthread.h>

/*
 * Clase encargada de representar un enemigo en el mapa.
 * Cada enemigo se ejecuta mediante un hilo independiente
 * que controla sus movimientos y acciones.
 */
class Enemigo {
private:
    // Hilo asociado a la lógica del enemigo.
    pthread_t hiloEnemigo;

    // Referencia al motor principal del juego.
    MotorJuego* motor;

    // Posición actual del enemigo en el mapa.
    int posX;
    int posY;

    // Tipo de movimiento que utilizará el enemigo.
    int tipoMovimiento;

    // Indica si el enemigo sigue activo.
    bool vivo;

    // Función ejecutada por el hilo del enemigo.
    static void* rutinaEnemigo(void* arg);

public:
    /*
     * Constructor del enemigo.
     * Recibe la posición inicial, el tipo de movimiento y el motor del juego.
     */
    Enemigo(int x, int y, int tipo, MotorJuego* m);

    // Destructor de la clase.
    ~Enemigo();

    // Inicia el hilo encargado de controlar al enemigo.
    void iniciar();

    // Devuelve el estado actual del enemigo.
    bool estaVivo();
};

#endif