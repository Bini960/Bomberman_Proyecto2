#include "Bomba.h" // Incluye el header de la bomba.
#include <unistd.h> 

Bomba::Bomba(int x, int y, int r, MotorJuego* m) { // Constructor base de inicialización.
    posX = x; // Guarda la coordenada en el eje X.
    posY = y; // Guarda la coordenada en el eje Y.
    radio = r; // Determina el alcance de la detonación.
    motor = m; // Vincula el motor de juego general.
}

Bomba::~Bomba() { // Destructor.
    pthread_join(hiloBomba, NULL); // Asegura cerrar el hilo tras concluir el impacto visual.
}

void Bomba::activar() { // Dispara la lógica paralela.
    pthread_create(&hiloBomba, NULL, rutinaBomba, (void*)this); // Genera el hilo con el conteo regresivo de detonación.
}

void* Bomba::rutinaBomba(void* arg) { // Manejador asíncrono de la bomba.
    Bomba* b = (Bomba*)arg; // Convierte la referencia genérica a objeto Bomba.
    MotorJuego* m = b->motor; // Accede al motor de la aplicación.

    m->obtenerMapa()->actualizarCelda(b->posX, b->posY, '*'); // Imprime el símbolo de la bomba activa en el tablero protegido.
    sleep(3); // Ejecuta el conteo regresivo de 3 segundos suspendiendo este hilo específico.

    m->obtenerMapa()->actualizarCelda(b->posX, b->posY, '~'); // Genera el epicentro visual de la onda expansiva en el mapa.
    usleep(500000); // Mantiene el carácter de explosión visible por 500 milisegundos en consola.
    m->obtenerMapa()->actualizarCelda(b->posX, b->posY, '.'); // Limpia la celda restituyendo el espacio transitable.

    return NULL; 
}