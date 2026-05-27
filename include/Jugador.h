#ifndef JUGADOR_H 
#define JUGADOR_H // Define el header.

#include "MotorJuego.h" // Permite acceder al mapa y sincronización compartida.
#include <pthread.h> // Necesario para instanciar el hilo individual de control.

class Jugador { // Representa la entidad del usuario dentro de la simulación.
private: 
    pthread_t hiloJugador; // Almacena el identificador del hilo del personaje.
    MotorJuego* motor; // Acceso al motor central.
    int posX; // Coordenada actual en el eje X de la matriz.
    int posY; // Coordenada actual en el eje Y de la matriz.
    int vidas; // Almacena el contador de salud del jugador.
    int id; // Identificador numérico para distinguir al jugador 1 del jugador 2.
    static void* rutinaJugador(void* arg); // Rutina concurrente para procesar la entidad.

public: 
    Jugador(int idJugador, int x, int y, MotorJuego* m); // Constructor parametrizado.
    ~Jugador(); // Destructor.
    void iniciar(); // Lanza el hilo independiente de este personaje.
    int obtenerX(); // Retorna la posición X.
    int obtenerY(); // Retorna la posición Y.
};

#endif