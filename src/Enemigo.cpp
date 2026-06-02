/*
 * Autor: Franco Paiz
 * Implementación de la clase Enemigo.
 * Controla el comportamiento, movimiento y ciclo de vida de los enemigos dentro del juego.
 */

#include "Enemigo.h"
#include "MotorJuego.h"

#include <unistd.h>
#include <cstdlib>

/*
 * Constructor del enemigo.
 * Inicializa su posición, tipo de movimiento y referencia al motor del juego.
 */
Enemigo::Enemigo(int x, int y, int tipo, MotorJuego* m) {
    posX = x;
    posY = y;
    tipoMovimiento = tipo;
    motor = m;
    vivo = true;
}

/*
 * Destructor del enemigo.
 * Espera a que el hilo asociado finalice correctamente antes de liberar recursos.
 */
Enemigo::~Enemigo() {
    pthread_join(hiloEnemigo, NULL);
}

/*
 * Inicia el hilo encargado de ejecutar la lógica del enemigo.
 */
void Enemigo::iniciar() {
    pthread_create(&hiloEnemigo, NULL, rutinaEnemigo, (void*)this);
}

/*
 * Indica si el enemigo sigue activo dentro de la partida.
 */
bool Enemigo::estaVivo() { return vivo; }

/*
 * Función principal ejecutada por el hilo del enemigo.
 * Gestiona el movimiento, las colisiones y la interacción con el entorno.
 */
void* Enemigo::rutinaEnemigo(void* arg) {
    Enemigo* e = (Enemigo*)arg;
    MotorJuego* m = e->motor;

    // Dirección actual utilizada para los movimientos lineales.
    int dirActual = 0;

    // Mantiene al enemigo activo mientras la partida continúe.
    while (m->estaActivo() && e->vivo) {

        // Verifica si el juego se encuentra pausado.
        pthread_mutex_lock(m->obtenerMutexEstado());

        while (m->estaPausado() && m->estaActivo()) {
            pthread_cond_wait(
                m->obtenerCondPausa(),
                m->obtenerMutexEstado()
            );
        }

        pthread_mutex_unlock(m->obtenerMutexEstado());

        // Comprueba si el enemigo fue alcanzado por una explosión.
        char celdaActual = m->obtenerMapa()->obtenerCelda(e->posX, e->posY);

        if (celdaActual == '~') {
            e->vivo = false;
            m->sumarPunto(10);
            return NULL;
        }

        int nx = e->posX;
        int ny = e->posY;

        /*
         * Tipo 0: movimiento aleatorio.
         * Tipo 1: movimiento horizontal.
         * Tipo 2: movimiento vertical.
         */
        if (e->tipoMovimiento == 0) {
            dirActual = rand() % 4;
        } else if (e->tipoMovimiento == 1) {
            if (dirActual != 2 && dirActual != 3)
                dirActual = 2;
        } else if (e->tipoMovimiento == 2) {
            if (dirActual != 0 && dirActual != 1)
                dirActual = 0;
        }

        // Calcula la siguiente posición según la dirección elegida.
        if (dirActual == 0) nx--;
        if (dirActual == 1) nx++;
        if (dirActual == 2) ny--;
        if (dirActual == 3) ny++;

        // Verifica si la celda destino es transitable.
        char celda = m->obtenerMapa()->obtenerCelda(nx, ny);

        if (celda == '.' || celda == 'P' || celda == 'Q') {

            // Limpia la posición anterior.
            m->obtenerMapa()->actualizarCelda(e->posX, e->posY, '.');

            // Actualiza la posición del enemigo.
            e->posX = nx;
            e->posY = ny;

            // Dibuja al enemigo en su nueva ubicación.
            m->obtenerMapa()->actualizarCelda(e->posX, e->posY, 'E');

        } else {

            // Si encuentra un obstáculo, cambia de dirección.
            if (dirActual == 0)
                dirActual = 1;
            else if (dirActual == 1)
                dirActual = 0;
            else if (dirActual == 2)
                dirActual = 3;
            else if (dirActual == 3)
                dirActual = 2;
        }

        // Controla la velocidad de movimiento del enemigo.
        usleep(300000);
    }

    // Finaliza la ejecución del hilo.
    return NULL;
}