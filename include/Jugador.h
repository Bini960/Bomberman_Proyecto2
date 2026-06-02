#ifndef JUGADOR_H
#define JUGADOR_H

#include "MotorJuego.h" // Dependencias del motor.
#include <pthread.h>    // Manejo de hilos.
#include <time.h>       // Control de tiempo.


// Representa a un jugador dentro de la partida.
class Jugador {
private:

    // Hilo principal del jugador.
    pthread_t hiloJugador;

    // Referencia al motor del juego.
    MotorJuego* motor;

    // Posición actual del jugador.
    int posX;
    int posY;

    // Estado del jugador.
    int vidas;
    int id;

    // Atributos de las bombas.
    int radioBomba;

    // Habilidades especiales.
    bool atraviesaMuros;
    time_t tiempoAtraviesaMuros;

    // Contenido original de la celda ocupada.
    char celdaAnterior;

    // Rutina ejecutada por el hilo.
    static void* rutinaJugador(void* arg);

public:

    // Constructor.
    Jugador(int idJugador, int x, int y, MotorJuego* m);

    // Destructor.
    ~Jugador();

    // Inicia el hilo del jugador.
    void iniciar();

    // Retorna las vidas restantes.
    int obtenerVidas();
};

#endif