#include "Poder.h" // Enlaza el header correspondiente de ventajas.

Poder::Poder(int x, int y, int tipo) { // Constructor de asignación.
    posX = x; // Fija la coordenada de la fila del beneficio.
    posY = y; // Fija la coordenada de la columna del beneficio.
    tipoPoder = tipo; // Define el tipo de beneficio específico.
}

void Poder::aplicarEfecto() { // Modifica atributos lógicos de las entidades de forma secuencial.
    if (tipoPoder == 1) { // Valida si el tipo representa un aumento de velocidad.
        // Espacio para incrementar la velocidad modificando el retardo del hilo del jugador.
    } else if (tipoPoder == 2) { // Valida si representa un aumento del rango explosivo.
        // Espacio para ampliar el radio en las propiedades del objeto bomba del jugador.
    }
}