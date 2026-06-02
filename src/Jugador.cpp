#include "Jugador.h" // Enlaza el archivo del jugador.
#include <unistd.h>  // Permite el uso de pausas de tiempo.


// Inicializa los atributos del jugador.
Jugador::Jugador(int idJugador, int x, int y, MotorJuego* m) {
    id = idJugador;
    posX = x;
    posY = y;
    vidas = 3;
    motor = m;
}


// Espera la finalización del hilo.
Jugador::~Jugador() {
    pthread_join(hiloJugador, NULL);
}


// Crea el hilo del jugador.
void Jugador::iniciar() {
    pthread_create(&hiloJugador, NULL, rutinaJugador, (void*)this);
}


// Ejecuta la lógica concurrente del jugador.
void* Jugador::rutinaJugador(void* arg) {
    Jugador* j = (Jugador*)arg;
    MotorJuego* m = j->motor;

    // Mantiene activo al jugador mientras dure la partida.
    while (m->estaActivo()) {

        // Verifica si el juego está en pausa.
        pthread_mutex_lock(m->obtenerMutexEstado());
        while (m->estaPausado() && m->estaActivo()) {
            pthread_cond_wait(
                m->obtenerCondPausa(),
                m->obtenerMutexEstado()
            );
        }
        pthread_mutex_unlock(m->obtenerMutexEstado());

        // Actualiza la posición del jugador en el mapa.
        m->obtenerMapa()->actualizarCelda(
            j->posX,
            j->posY,
            (j->id == 1) ? 'P' : 'Q'
        );

        // Controla la velocidad de actualización.
        usleep(50000);
    }

    return NULL;
}


// Retorna la fila actual.
int Jugador::obtenerX() {
    return posX;
}


// Retorna la columna actual.
int Jugador::obtenerY() {
    return posY;
}