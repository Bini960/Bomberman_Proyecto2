/*
 * Autor: Franco Paiz
 * Clase encargada de representar una bomba dentro del juego.
 * Controla su activación, explosión y los efectos que genera sobre el mapa.
 */

#include "Bomba.h"

#include <unistd.h>
#include <cstdlib>
#include <vector> // Se incluye vector para manejar la memoria dinámica de forma segura.

/*
 * Constructor de la bomba.
 * Guarda la posición inicial, el radio de explosión y una referencia al motor del juego.
 */
Bomba::Bomba(int x, int y, int r, MotorJuego* m) {
    posX = x;
    posY = y;
    radio = r;
    motor = m;
}

/*
 * Destructor de la bomba.
 * No requiere liberar recursos adicionales.
 */
Bomba::~Bomba() { }

/*
 * Activa la bomba creando un hilo independiente que se encargará
 * de esperar y ejecutar la explosión.
 */
void Bomba::activar() {
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    // Configura el hilo como desacoplado para que gestione su propia finalización.
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_create(&hiloBomba, &attr, rutinaBomba, (void*)this);

    pthread_attr_destroy(&attr);
}

/*
 * Función ejecutada por el hilo de la bomba.
 * Espera unos segundos, genera la explosión y posteriormente limpia el área afectada.
 */
void* Bomba::rutinaBomba(void* arg) {
    Bomba* b = (Bomba*)arg;
    MotorJuego* m = b->motor;

    // Muestra la bomba colocada en el mapa.
    m->obtenerMapa()->actualizarCelda(b->posX, b->posY, '*');

    // Tiempo de espera antes de la detonación.
    sleep(3);

    // Direcciones de expansión de la explosión.
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    // CORRECCIÓN: Se reemplazan los arreglos estáticos de tamaño 20 por vectores dinámicos.
    // Esto previene el desbordamiento de memoria (Segmentation Fault) cuando el radio es muy grande.
    std::vector<int> afectadasX;
    std::vector<int> afectadasY;
    std::vector<bool> eraMuro; // Nuevo vector para rastrear si la celda era un muro destructible.

    // Registra el punto central de la explosión.
    afectadasX.push_back(b->posX);
    afectadasY.push_back(b->posY);
    eraMuro.push_back(false); // El centro nunca es un muro porque ahí se colocó la bomba.

    // Marca visualmente el centro de la explosión.
    m->obtenerMapa()->actualizarCelda(b->posX, b->posY, '~');

    // Recorre las cuatro direcciones principales.
    for (int i = 0; i < 4; i++) {

        // Avanza hasta alcanzar el radio máximo de la bomba.
        for (int r = 1; r <= b->radio; r++) {
            int nx = b->posX + dx[i] * r;
            int ny = b->posY + dy[i] * r;

            char celda = m->obtenerMapa()->obtenerCelda(nx, ny);

            // Los muros indestructibles bloquean la expansión.
            if (celda == '#') break;

            afectadasX.push_back(nx);
            afectadasY.push_back(ny);

            // Si encuentra un muro destruible, lo elimina, lo registra y detiene la propagación.
            if (celda == 'X') {
                eraMuro.push_back(true); // Registra que aquí había un muro destructible.
                m->obtenerMapa()->actualizarCelda(nx, ny, '~');
                m->sumarPunto(5);
                break;
            }

            // Si era un pasillo normal, simplemente lo marca como parte de la explosión.
            eraMuro.push_back(false);
            m->obtenerMapa()->actualizarCelda(nx, ny, '~');
        }
    }

    // Mantiene visible la explosión por un corto tiempo.
    usleep(500000);

    // Limpia todas las celdas afectadas.
    for (size_t i = 0; i < afectadasX.size(); i++) {
        char reemplazo = '.';

        // CORRECCIÓN: Ahora solo existe la probabilidad de generar un power-up 
        // estrictamente si la celda contenía un muro destructible ('X').
        if (eraMuro[i] && (rand() % 100 < 45)) {
            reemplazo = '+';
        }

        m->obtenerMapa()->actualizarCelda(
            afectadasX[i],
            afectadasY[i],
            reemplazo
        );
    }

    // Libera la memoria de la bomba una vez finalizado el proceso.
    delete b;

    return NULL;
}