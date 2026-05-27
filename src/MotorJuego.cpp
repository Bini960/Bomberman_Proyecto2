#include "MotorJuego.h" // Incluye la definición de la clase correspondiente.
#include <unistd.h> // Proporciona la función usleep para el control del tiempo.

MotorJuego::MotorJuego() { // Implementación del constructor.
    juegoActivo = true; // Inicializa la partida en estado activo.
    pausado = false; // Inicializa el estado de pausa como desactivado.
    pthread_mutex_init(&mutexEstado, NULL); // Inicializa el mutex de control globales.
    pthread_cond_init(&condPausa, NULL); // Inicializa la variable de condición para la pausa.
}

MotorJuego::~MotorJuego() { // Implementación del destructor.
    pthread_mutex_destroy(&mutexEstado); // Libera los recursos del mutex de estado.
    pthread_cond_destroy(&condPausa); // Libera los recursos de la variable de condición.
}

void MotorJuego::inicializar() { // Implementa los preparativos del entorno.
    mapa.inicializarMapa(); // Rellena la matriz del mapa con el laberinto inicial.
}

void MotorJuego::ejecutar() { // Ciclo operativo principal.
    while (estaActivo()) { // Mantiene el juego en ejecución mientras la bandera sea verdadera.
        pthread_mutex_lock(&mutexEstado); // Solicita el candado de estado.
        while (pausado) { // Verifica si el juego fue suspendido temporalmente.
            pthread_cond_wait(&condPausa, &mutexEstado); // Libera el mutex y espera la señal de reanudación.
        }
        pthread_mutex_unlock(&mutexEstado); // Libera el candado de estado tras pasar la pausa.
        mapa.dibujar(); // Redibuja el tablero en la terminal.
        usleep(100000); // Pausa el hilo principal por 100 milisegundos para estabilizar los fotogramas.
    }
}

void MotorJuego::alternarPausa() { // Modifica el estado de suspensión.
    pthread_mutex_lock(&mutexEstado); // Bloquea las variables de estado.
    pausado = !pausado; // Invierte el valor lógico de la variable de pausa.
    if (!pausado) { // Si el juego se ha reanudado.
        pthread_cond_broadcast(&condPausa); // Envía una señal a todos los hilos en espera para despertar.
    }
    pthread_mutex_unlock(&mutexEstado); // Libera las variables de estado globales.
}

bool MotorJuego::estaActivo() { // Lee el estado de actividad de forma segura.
    pthread_mutex_lock(&mutexEstado); // Bloquea para evitar lecturas sucias.
    bool resultado = juegoActivo; // Copia el valor de la bandera.
    pthread_mutex_unlock(&mutexEstado); // Libera el bloqueo de estado.
    return resultado; // Retorna el estado actual.
}

bool MotorJuego::estaPausado() { // Lee el estado de pausa de forma segura.
    pthread_mutex_lock(&mutexEstado); // Aplica exclusión mutua a la variable.
    bool resultado = pausado; // Captura el valor actual de la pausa.
    pthread_mutex_unlock(&mutexEstado); // Remueve el bloqueo de exclusión mutua.
    return resultado; // Retorna si la simulación está en pausa.
}

void MotorJuego::detener() { // Apaga el motor de juego.
    pthread_mutex_lock(&mutexEstado); // Bloquea el estado global.
    juegoActivo = false; // Cambia la bandera para romper el ciclo principal.
    pthread_mutex_unlock(&mutexEstado); // Desbloquea el estado global.
}

Mapa* MotorJuego::obtenerMapa() { // Expone la dirección en memoria de la interfaz de la matriz.
    return &mapa; // Retorna el puntero directo al objeto del mapa.
}

pthread_mutex_t* MotorJuego::obtenerMutexEstado() { // Expone el candado global para los hilos secundarios.
    return &mutexEstado; // Retorna la dirección del mutex de estado.
}

pthread_cond_t* MotorJuego::obtenerCondPausa() { // Expone la variable de condición para los hilos trabajadores.
    return &condPausa; // Retorna la dirección de la variable de condición.
}