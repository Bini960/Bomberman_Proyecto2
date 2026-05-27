#ifndef PODER_H 
#define PODER_H // Declara el header del módulo.

class Poder { // Define el objeto encargado de los power-ups del laberinto.
private: 
    int tipoPoder; // Código numérico para diferenciar velocidad, radio u otras ventajas.
    int posX; // Coordenada X del beneficio.
    int posY; // Coordenada Y del beneficio.

public: 
    Poder(int x, int y, int tipo); // Constructor de la clase de mejoras.
    void aplicarEfecto(); // Ejecuta las modificaciones sobre los atributos del jugador seleccionado.
};

#endif 