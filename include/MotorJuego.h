#ifndef MOTORJUEGO_H // Evita la inclusión múltiple del archivo de cabecera.
#define MOTORJUEGO_H // Define el símbolo del archivo de cabecera.

#include "Mapa.h" // Incluye la clase encargada del tablero.
#include <pthread.h> 

class MotorJuego { // Define la clase que controla el flujo principal de la simulación.
private: // Atributos privados de la clase.
    Mapa mapa; // Instancia compartida del mapa del juego.
    bool juegoActivo; // Bandera para determinar si la partida sigue en ejecución.
    bool pausado; // Bandera para controlar el estado de pausa del juego.
    pthread_mutex_t mutexEstado; // Mutex para proteger las banderas de estado global.
    pthread_cond_t condPausa; // Variable de condición para suspender los hilos durante la pausa.

public: // Métodos públicos de la clase.
    MotorJuego(); // Constructor de la clase.
    ~MotorJuego(); // Destructor de la clase.
    void inicializar(); // Configura los elementos iniciales antes de arrancar.
    void ejecutar(); // Contiene el ciclo principal de actualización del juego.
    void alternarPausa(); // Cambia de forma segura el estado de pausa.
    bool estaActivo(); // Retorna si la partida sigue activa.
    bool estaPausado(); // Retorna si la simulación está en pausa.
    void detener(); // Finaliza el ciclo de juego de manera ordenada.
    Mapa* obtenerMapa(); // Devuelve un puntero al mapa para el acceso de otras clases.
    pthread_mutex_t* obtenerMutexEstado(); // Devuelve un puntero al mutex de estado.
    pthread_cond_t* obtenerCondPausa(); // Devuelve un puntero a la variable de condición.
};

#endif // Fin de la condición de inclusión del archivo.