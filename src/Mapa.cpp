#include "Mapa.h" // Incluye el header correspondiente para implementar los métodos.
#include <iostream> // Permite la impresión de caracteres en la consola.

Mapa::Mapa() { // Implementación del constructor de la clase.
    pthread_mutex_init(&mutexMapa, NULL); // Inicializa el mutex del mapa de forma segura.
}

Mapa::~Mapa() { // Implementación del destructor de la clase.
    pthread_mutex_destroy(&mutexMapa); // Destruye el mutex para liberar recursos del sistema.
}

void Mapa::inicializarMapa() { // Implementa la creación del laberinto base.
    for (int i = 0; i < 13; i++) { // Recorre cada fila de la matriz.
        for (int j = 0; j < 15; j++) { // Recorre cada columna de la matriz.
            if (i == 0 || i == 12 || j == 0 || j == 14) { // Verifica si la celda es un borde externo.
                matriz[i][j] = '#'; // Coloca un muro fijo indestructible en el borde.
            } else if (i % 2 == 0 && j % 2 == 0) { // Verifica posiciones internas intercaladas.
                matriz[i][j] = '#'; // Coloca muros fijos internos del laberinto.
            } else { // Para el resto de las celdas internas transitables.
                matriz[i][j] = '.'; // Inicializa la celda como un espacio libre.
            }
        }
    }
}

void Mapa::dibujar() { // Implementa el renderizado en consola en tiempo real.
    pthread_mutex_lock(&mutexMapa); // Bloquea el acceso a la matriz antes de leerla.
    std::cout << "\033[H"; // Mueve el cursor al inicio de la terminal para evitar parpadeos.
    for (int i = 0; i < 13; i++) { // Recorre las filas de la matriz para su impresión.
        for (int j = 0; j < 15; j++) { // Recorre las columnas correspondientes.
            std::cout << matriz[i][j] << " "; // Imprime el carácter de la celda actual con un espacio.
        }
        std::cout << "\n"; // Añade un salto de línea al finalizar cada fila.
    }
    pthread_mutex_unlock(&mutexMapa); // Libera el mutex para permitir el acceso a otros hilos trabajadores.
}

void Mapa::mostrarMenu() { // Muestra las opciones del menú principal.
    std::cout << "--- BOMBERMAN CONCURRENTE ---\n"; 
    std::cout << "1. Modo Un Jugador\n"; 
    std::cout << "2. Modo Dos Jugadores\n"; 
    std::cout << "3. Ver Instrucciones\n"; 
    std::cout << "4. Puntajes Destacados\n"; 
    std::cout << "5. Salir del Juego\n"; 
}

void Mapa::mostrarInstrucciones() { // Muestra las reglas generales de la partida.
    std::cout << "--- INSTRUCCIONES ---\n"; 
    std::cout << "Jugador 1: WASD para moverse, F para colocar bomba.\n";
    std::cout << "Jugador 2: Flechas para moverse, Enter para colocar bomba.\n"; 
    std::cout << "Objetivo: Destruir obstaculos y sobrevivir.\n"; 
}

void Mapa::mostrarPuntajes() { // Muestra el registro histórico de partidas.
    std::cout << "--- MEJORES PUNTAJES ---\n";
    std::cout << "1. Anonimo - 100 pts\n"; 
}

void Mapa::actualizarCelda(int x, int y, char caracter) { // Modifica un elemento de forma segura.
    pthread_mutex_lock(&mutexMapa); // Solicita el candado del mapa para exclusión mutua.
    matriz[x][y] = caracter; // Asigna el nuevo carácter en las coordenadas especificadas.
    pthread_mutex_unlock(&mutexMapa); // Libera el candado del mapa inmediatamente.
}

char Mapa::obtenerCelda(int x, int y) { // Lee una posición de la matriz de forma segura.
    pthread_mutex_lock(&mutexMapa); // Bloquea el mapa para evitar lecturas inconsistentes de otros hilos.
    char valor = matriz[x][y]; // Almacena temporalmente el carácter presente en la celda.
    pthread_mutex_unlock(&mutexMapa); // Libera el mapa tras concluir la lectura del dato.
    return valor; // Devuelve el carácter obtenido de la matriz.
}