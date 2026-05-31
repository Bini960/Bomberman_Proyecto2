#ifndef MOTORJUEGO_H // Evita la inclusión múltiple del archivo de cabecera.
#define MOTORJUEGO_H // Define el símbolo del archivo de cabecera.

#include "Mapa.h" // Incluye la clase encargada del tablero.
#include <pthread.h> 
#include <vector> // Incluye la estructura de datos estándar.

class Jugador; 
class Enemigo; 
class ManejadorEntrada; 

class MotorJuego { // Clase administradora 
private: 
    Mapa mapa; // Instancia el entorno visual de la consola.
    bool juegoActivo; // Bandera atómica simulada para el ciclo de vida.
    bool pausado; // Bandera para controlar la suspensión temporal.
    pthread_mutex_t mutexEstado; // Candado para proteger las banderas globales.
    pthread_cond_t condPausa; // Señal de condición para pausar hilos pasivamente.
    std::vector<Jugador*> jugadores; // Contenedor dinámico de punteros a personajes.
    std::vector<Enemigo*> enemigos; // Contenedor dinámico de punteros a adversarios.
    ManejadorEntrada* manejador; // Puntero hacia el hilo de lectura de consola.

public: 
    MotorJuego(); // Constructor que inicializa las variables de estado.
    ~MotorJuego(); // Destructor que libera la memoria dinámica asignada.
    void inicializar(); // Instancia las entidades y lanza sus hilos.
    void ejecutar(); // Gestiona el bucle de actualización de fotogramas.
    void alternarPausa(); // Invierte de forma segura el estado de suspensión.
    bool estaActivo(); // Extrae de forma segura el estado de ejecución.
    bool estaPausado(); // Extrae de forma segura el estado de pausa.
    void detener(); // Rompe el ciclo principal y solicita el cierre.
    Mapa* obtenerMapa(); // Retorna la dirección en memoria de la matriz.
    pthread_mutex_t* obtenerMutexEstado(); // Retorna el candado de control global.
    pthread_cond_t* obtenerCondPausa(); // Retorna la señal de suspensión.
};

#endif // Cierra la directiva de compilación condicional.