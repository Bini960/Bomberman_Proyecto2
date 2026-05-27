#ifndef MANEJADORENTRADA_H // Evita problemas de inclusión de archivos.
#define MANEJADORENTRADA_H // Define el identificador del archivo.

#include "MotorJuego.h" // Enlaza el motor para notificar las acciones detectadas.
#include <pthread.h> // Requerido para almacenar el identificador del hilo de lectura.

class ManejadorEntrada { // Define la clase responsable de capturar las pulsaciones de la terminal.
private:
    pthread_t hiloEntrada; // Identificador oficial del hilo POSIX para el teclado.
    MotorJuego* motor; // Puntero al motor para interactuar con la partida activa.
    static void* rutinaEntrada(void* arg); // Función estática requerida por pthread_create como rutina.

public:
    ManejadorEntrada(MotorJuego* m); // Constructor que recibe la referencia del motor.
    ~ManejadorEntrada(); // Destructor para asegurar la liberación de recursos.
    void iniciar(); // Llama a la creación del hilo de entrada.
};

#endif // Fin del archivo de cabecera.