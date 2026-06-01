#ifndef MOTORJUEGO_H 
#define MOTORJUEGO_H 

#include "Mapa.h" // Incluye la definición de la clase responsable de dibujar el tablero.
#include <pthread.h> 
#include <vector> // Incluye la estructura de datos dinámica para manejar colecciones de objetos.
#include <string> // Incluye el manejo de cadenas de texto para la mensajería de la interfaz.

class Jugador;
class Enemigo; 
class ManejadorEntrada; 

class MotorJuego {
private: 
    Mapa mapa; // Instancia el administrador de la matriz gráfica de la consola.
    bool juegoActivo; // Bandera booleana para conocer si la partida está en curso.
    bool pausado; // Bandera booleana para controlar las interrupciones del juego.
    int puntos; // Almacena el valor numérico del puntaje del usuario.
    int nivel; // Controla la etapa de dificultad y cantidad de adversarios instanciados.
    int bombasActivas; // Cuenta el total de explosivos detonando en el mapa simultáneamente.
    int maxBombas; // Limita la cantidad de artefactos permitidos en pantalla.
    int modoJuego; // Determina si la partida es individual (1) o competitiva (2).
    std::string mensajeGlobal; // Almacena el texto informativo para la interfaz visual.
    pthread_mutex_t mutexEstado; // Candado para proteger los datos compartidos contra condiciones de carrera.
    pthread_cond_t condPausa; // Variable de condición para suspender hilos de forma pasiva sin gastar CPU.
    std::vector<Jugador*> jugadores; // Lista dinámica para almacenar punteros de usuarios.
    std::vector<Enemigo*> enemigos; // Lista dinámica para almacenar punteros de adversarios.
    ManejadorEntrada* manejador; // Puntero hacia la rutina lectora del teclado asíncrono.

public: 
    MotorJuego(); // Constructor que prepara las variables y mecanismos de sincronización.
    ~MotorJuego(); // Destructor para limpiar memoria dinámica y destruir candados.
    void iniciarMenu(); // Llama al inicio de la interfaz de opciones y bucle de juego.
    void inicializarNivel(); // Instancia las variables y oponentes para cada nueva etapa.
    void limpiarNivel(); // Elimina los hilos finalizados y vacía la memoria de la partida.
    void ejecutar(); // Entra en el ciclo principal de actualización gráfica y verificación.
    void alternarPausa(); // Detiene o reanuda la simulación notificando a los hilos.
    bool estaActivo(); // Retorna el estado del programa protegiendo la lectura con exclusión mutua.
    bool estaPausado(); // Retorna el estado de suspensión protegiendo la lectura.
    void detener(); // Ordena el cierre general bajando la bandera de ejecución a todos los subprocesos.
    void sumarPunto(int cantidad); // Aumenta la puntuación bloqueando variables compartidas de forma atómica.
    void registrarBomba(int variacion); // Aumenta o disminuye el límite de explosivos de forma segura.
    void verificarEstadoNivel(); // Revisa si los oponentes fueron eliminados para avanzar de etapa.
    void establecerMensaje(std::string mensaje); // Asigna un texto informativo para notificar beneficios al jugador.
    std::string obtenerMensaje(); // Retorna el texto almacenado protegiendo la memoria compartida.
    Mapa* obtenerMapa(); // Retorna la dirección de memoria de la matriz gráfica.
    pthread_mutex_t* obtenerMutexEstado(); // Retorna la ubicación del candado del motor para su uso en hilos.
    pthread_cond_t* obtenerCondPausa(); // Retorna la ubicación de la señal de pausa.
    int obtenerModo(); // Consulta el formato de juego elegido en el menú.
    int obtenerMaxBombas(); // Consulta la capacidad máxima de artefactos configurada.
};

#endif 