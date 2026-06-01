#ifndef MAPA_H // Evita problemas de redefinición en cascada.
#define MAPA_H // Declara la cabecera oficial del renderizador gráfico.

#include <pthread.h> // Incluye la librería POSIX para utilizar sincronización espacial.
#include <string> // Incluye librerías de cadenas para el texto informativo.

class Mapa { // Administra la matriz bidimensional y la interacción visual por consola.
private: 
    char matriz[13][15]; // Reserva un bloque estático de memoria para el laberinto.
    pthread_mutex_t mutexMapa; // Declara el candado exclusivo para prevenir desajustes gráficos al dibujar simultáneamente.

public: 
    Mapa(); // Constructor encargado de preparar el candado de la matriz.
    ~Mapa(); // Destructor para recolección de variables POSIX.
    void inicializarMapa(); // Ejecuta la construcción espacial de bloques y pasillos.
    void dibujar(int vidas1, int vidas2, int puntos, int nivel, int modo, std::string mensaje); // Proyecta el modelo de memoria en la terminal de usuario usando caracteres ANSI.
    int mostrarMenu(); // Administra las pantallas de inicio solicitando comandos de navegación.
    void mostrarInstrucciones(); // Despliega la documentación estática de los controles.
    void mostrarPuntajes(); // Lee registros físicos de disco para exponer el historial.
    void guardarPuntaje(int puntos); // Graba en un archivo plano un nuevo récord obtenido.
    void actualizarCelda(int x, int y, char caracter); // Sobrescribe de forma atómica una coordenada espacial.
    char obtenerCelda(int x, int y); // Lee y extrae con exclusión mutua el valor de una casilla.
};

#endif 