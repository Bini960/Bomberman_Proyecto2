#include <iostream> // Incluye la librería de entrada y salida estándar del sistema.
#include "MotorJuego.h" // Vincula la definición de la clase administradora principal.

int main() { // Define el punto de entrada principal del programa al ejecutarse en el sistema operativo.
    MotorJuego motor; // Instancia el objeto del motor de juego reservando memoria en la pila.
    motor.iniciarMenu(); // Invoca el ciclo principal que maneja los menús y el control de partidas.
    return 0; // Finaliza la ejecución devolviendo un código de éxito al sistema operativo.
}