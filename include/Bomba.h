#ifndef BOMBA_H // Evita problemas de inclusión múltiple.
#define BOMBA_H // Define la cabecera de la bomba.

#include "MotorJuego.h" // Conecta con el mapa para alterar el laberinto al explotar.
#include <pthread.h> // Necesario para instanciar un hilo exclusivo por cada explosión colocada.

class Bomba { // Representa el objeto explosivo en la simulación.
private: 
    pthread_t hiloBomba; // Identificador del hilo asignado para la cuenta regresiva.
    MotorJuego* motor; // Referencia al motor del juego.
    int posX; // Fila donde fue depositada la bomba.
    int posY; // Columna donde fue depositada la bomba.
    int radio; // Distancia de celdas que abarcará la onda expansiva en cruz.
    static void* rutinaBomba(void* arg); // Rutina concurrente del temporizador.

public: 
    Bomba(int x, int y, int r, MotorJuego* m); // Constructor parametrizado.
    ~Bomba(); // Destructor.
    void activar(); // Lanza el hilo de cuenta regresiva de la bomba.
};

#endif 