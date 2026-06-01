#include "Poder.h" // Invocación de las firmas prototipo establecidas para el polimorfismo del juego.

Poder::Poder(int x, int y) { // Inicializa variables posicionales básicas desde las raíces abstractas de la definición.
    posX = x; // Establece ubicación inicial horizontal del bono flotante.
    posY = y; // Establece ubicación vertical espacial temporal.
}

PoderVelocidad::PoderVelocidad(int x, int y) : Poder(x, y) {} // Utiliza la delegación paramétrica llamando al molde del objeto primigenio.

void PoderVelocidad::aplicarEfecto() { // Declaración de método virtual preparatorio.
    // Estructura modular polimórfica preestablecida.
    // Actualmente las mejoras numéricas actúan directamente sobre el hilo de la clase Jugador para maximizar eficiencia de memoria de acceso local.
}

PoderRadio::PoderRadio(int x, int y) : Poder(x, y) {} // Herencia constructora simple sin parámetros de atributos dinámicos propios por el momento.

void PoderRadio::aplicarEfecto() { // Declaración polimórfica escalable obligatoria.
    // Permite delegar responsabilidades sin causar colisiones en la refactorización arquitectónica de clases en posteriores actualizaciones modulares de software.
}