#ifndef ENEMIGO_H 
#define ENEMIGO_H // Define el header de enemigos.

#include "MotorJuego.h" // Conecta con el motor de juego para consultar la pausa.
#include <pthread.h> // Necesario para instanciar el hilo individual de ejecución.

class Enemigo { // Modela a los oponentes automatizados de la simulación.
private: 
    pthread_t hiloEnemigo; // Identificador del hilo POSIX asignado al enemigo.
    MotorJuego* motor; // Puntero al motor general de control.
    int posX; // Fila del oponente en la cuadrícula del laberinto.
    int posY; // Columna del oponente en la cuadrícula del laberinto.
    int tipoMovimiento; // Variable para implementar diferentes patrones de movimiento (Puntos extra).
    static void* rutinaEnemigo(void* arg); // Función de ejecución independiente de la entidad.

public: 
    Enemigo(int x, int y, int tipo, MotorJuego* m); // Constructor con asignación de patrón de inteligencia.
    ~Enemigo(); // Destructor para control de hilos.
    void iniciar(); // Lanza la ejecución en paralelo del enemigo.
};

#endif 