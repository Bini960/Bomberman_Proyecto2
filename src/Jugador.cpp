#include "Jugador.h" // Enlaza el archivo del jugador.
#include <unistd.h> // Permite el uso de pausas de tiempo 

Jugador::Jugador(int idJugador, int x, int y, MotorJuego* m) { // Inicializa los atributos del jugador.
    id = idJugador; // Asigna el identificador único del usuario.
    posX = x; // Establece la fila inicial en la cuadrícula.
    posY = y; // Establece la columna inicial en la cuadrícula.
    vidas = 3; // Otorga el contador de tres vidas iniciales.
    motor = m; // Vincula el motor de la sesión.
}

Jugador::~Jugador() { // Implementación del destructor.
    pthread_join(hiloJugador, NULL); // Espera al hilo del jugador para evitar procesos zombies.
}

void Jugador::iniciar() { // Genera el proceso concurrente.
    pthread_create(&hiloJugador, NULL, rutinaJugador, (void*)this); // Inicializa el hilo pasando el objeto actual como argumento.
}

void* Jugador::rutinaJugador(void* arg) { // Lógica concurrente de la entidad.
    Jugador* j = (Jugador*)arg; // Convierte el parámetro al tipo de la clase actual.
    MotorJuego* m = j->motor; // Obtiene el acceso al motor de juego compartido.

    while (m->estaActivo()) { // Se ejecuta mientras la partida continúe activa.
        pthread_mutex_lock(m->obtenerMutexEstado()); // Solicita el candado global de estados del motor.
        while (m->estaPausado() && m->estaActivo()) { // Evalúa si se debe pausar la lógica del jugador.
            pthread_cond_wait(m->obtenerCondPausa(), m->obtenerMutexEstado()); // Espera a que termine la pausa.
        }
        pthread_mutex_unlock(m->obtenerMutexEstado()); // Libera el candado global tras validar la pausa.

        m->obtenerMapa()->actualizarCelda(j->posX, j->posY, (j->id == 1) ? 'P' : 'Q'); // Dibuja el identificador visual en el mapa seguro.
        usleep(50000); // Detiene el hilo por 50 milisegundos para regular los ciclos de actualización.
    }
    return NULL; // Concluye la función de forma correcta.
}

int Jugador::obtenerX() { return posX; } // Retorna la fila actual.
int Jugador::obtenerY() { return posY; } // Retorna la columna actual.