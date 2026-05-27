#ifndef MAPA_H // Evita la inclusión múltiple del archivo
#define MAPA_H // Define el símbolo del archivo

#include <pthread.h> // Proporciona las funciones para hilos POSIX

class Mapa { // Define la clase encargada de la interfaz gráfica y el tablero.
private: 
    char matriz[13][15]; // Matriz bidimensional para el laberinto (13 filas por 15 columnas)
    pthread_mutex_t mutexMapa; // Mutex para proteger el acceso concurrente a la matriz

public: 
    Mapa(); // Constructor de la clase
    ~Mapa(); // Destructor de la clase
    void inicializarMapa(); // Llena la matriz con los muros y espacios vacíos iniciales
    void dibujar(); // Renderiza el mapa y las estadísticas en la consola
    void mostrarMenu(); // Muestra el menú principal interactivo
    void mostrarInstrucciones(); // Muestra la pantalla con las reglas y controles
    void mostrarPuntajes(); // Muestra la tabla de mejores puntuaciones
    void actualizarCelda(int x, int y, char caracter); // Modifica de forma segura una posición del mapa
    char obtenerCelda(int x, int y); // Lee de forma segura el contenido de una posición
};

#endif // Fin de la condición 