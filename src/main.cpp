#include <iostream> 
#include "MotorJuego.h" // Incluye la definición del archivo principal del juego.

int main() { // Punto de entrada principal del programa.
    MotorJuego motor; // Instancia el objeto del motor de juego.
    motor.inicializar(); // Llama a la configuración inicial del juego.
    motor.ejecutar(); // Inicia el ciclo principal de ejecución.
    return 0;
}