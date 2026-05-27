#include "Enemigo.cpp" // Enlace al oponente.
#include "Enemigo.h" // Incluye el header correspondiente.
#include <unistd.h>

Enemigo::Enemigo(int x, int y, int tipo, MotorJuego* m) { // Constructor base.
    posX = x; // Define la posición inicial en X.
    posY = y; // Define la posición inicial en Y.
    tipoMovimiento = tipo; // Define el patrón que seguirá su inteligencia artificial.
    motor = m; // Guarda la referencia del motor compartido.
}

Enemigo::~Enemigo() { // Destructor.
    pthread_join(hiloEnemigo, NULL); // Asegura la recolección del hilo de trabajo al cerrar.
}

void Enemigo::iniciar() { // Inicializa el ciclo en paralelo.
    pthread_create(&hiloEnemigo, NULL, rutinaEnemigo, (void*)this); // Arranca el hilo de patrullaje asíncrono.
}

void* Enemigo::rutinaEnemigo(void* arg) { // Lógica asíncrona de los enemigos.
    Enemigo* e = (Enemigo*)arg; // Convierte el puntero al contexto de la clase.
    MotorJuego* m = e->motor; // Accede a las variables del sistema global.

    while (m->estaActivo()) { // Itera mientras persista la sesión activa.
        pthread_mutex_lock(m->obtenerMutexEstado()); // Solicita el candado global de estados del motor.
        while (m->estaPausado() && m->estaActivo()) { // Evalúa si se debe pausar la lógica del enemigo.
            pthread_cond_wait(m->obtenerCondPausa(), m->obtenerMutexEstado()); // Detiene el hilo sin consumir ciclos de CPU.
        }
        pthread_mutex_unlock(m->obtenerMutexEstado()); // Remueve el candado global de control de estados.

        m->obtenerMapa()->actualizarCelda(e->posX, e->posY, 'E'); // Actualiza de forma segura la celda con el carácter del enemigo.
        usleep(200000); // Modula el avance pausando el hilo por 200 milisegundos.
    }
    return NULL; 
}