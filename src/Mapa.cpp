#include "Mapa.h" // Incluye definiciones locales del tablero gráfico.
#include <iostream> // Agrega los canales de entrada y salida estándar de la consola.
#include <cstdlib> // Agrega herramientas matemáticas para generación de obstáculos aleatorios.
#include <fstream> // Habilita la lectura y escritura de archivos planos en disco duro.
#include <unistd.h> // Provee la manipulación de descargas de búfer.

Mapa::Mapa() { // Constructor general.
    pthread_mutex_init(&mutexMapa, NULL); // Inicializa el recurso de exclusión mutua para la matriz visual.
}

Mapa::~Mapa() { // Operación destructiva del objeto.
    pthread_mutex_destroy(&mutexMapa); // Devuelve la memoria del candado al kernel de Linux.
}

void Mapa::inicializarMapa() { // Prepara la geografía virtual de cada partida.
    for (int i = 0; i < 13; i++) { // Ejecuta bucle lineal sobre el eje vertical Y.
        for (int j = 0; j < 15; j++) { // Ejecuta bucle lineal sobre el eje horizontal X.
            if (i == 0 || i == 12 || j == 0 || j == 14) { // Delimita matemáticamente los márgenes extremos externos.
                matriz[i][j] = '#'; // Sella la casilla asignando un muro inquebrantable de hardware.
            } else if (i % 2 == 0 && j % 2 == 0) { // Evalúa paridad espacial para construir bloques intercalados centrales.
                matriz[i][j] = '#'; // Erige un obstáculo fijo arquitectónico.
            } else { // Asume el espacio restante como área interna navegable.
                if (rand() % 100 < 30 && (i > 2 || j > 2)) matriz[i][j] = 'X'; // Asigna bloques destructibles en un treinta por ciento de probabilidad, evadiendo el punto de aparición primario.
                else matriz[i][j] = '.'; // Coloca suelo base en los fragmentos vacíos.
            }
        }
    }
}

void Mapa::dibujar(int vidas1, int vidas2, int puntos, int nivel, int modo, std::string mensaje) { // Dibuja todos los elementos en consola junto con el texto informativo.
    pthread_mutex_lock(&mutexMapa); // Congela temporalmente la matriz para extraer un fotograma coherente sin superposiciones.
    std::cout << "\033[H"; // Emite un código de control ANSI moviendo el cursor al origen sin alterar el fondo previo causando cero parpadeo.
    std::cout << "\033[97m=== BOMBERMAN CONCURRENTE ===\033[0m\033[K\n\n"; // Imprime el título brillante y ejecuta K para limpiar el sobrante lateral.

    for (int i = 0; i < 13; i++) { // Navega de arriba abajo en el renderizado.
        for (int j = 0; j < 15; j++) { // Navega de izquierda a derecha.
            char c = matriz[i][j]; // Atrapa el dato en caché.
            // Evalúa el contenido y asigna un tono específico de color de escape ANSI antes de imprimir.
            if (c == '#') std::cout << "\033[90m#\033[0m "; // Pinta los muros perimetrales en gris.
            else if (c == 'X') std::cout << "\033[33mX\033[0m "; // Pinta los obstáculos blandos en tono ocre amarillo.
            else if (c == 'P') std::cout << "\033[96mP\033[0m "; // Tiñe al protagonista de color cian visible.
            else if (c == 'Q') std::cout << "\033[93mQ\033[0m "; // Tiñe al oponente humano de color dorado.
            else if (c == 'E') std::cout << "\033[95mE\033[0m "; // Destaca a las máquinas con color magenta.
            else if (c == '*') std::cout << "\033[97m*\033[0m "; // Realza las bombas activas en color lumínico blanco.
            else if (c == '~') std::cout << "\033[91m~\033[0m "; // Representa el espectro térmico en rojo fuerte.
            else if (c == '+') std::cout << "\033[92m+\033[0m "; // Refleja los power-ups con tono verde llamativo.
            else std::cout << ". "; // Rellena el fondo con símbolos de camino pasivos.
        }
        
        // Renderiza lateralmente información cuantitativa acoplando las mediciones dinámicas del hilo maestro.
        if (i == 2) std::cout << "   \033[96mVidas P1: " << vidas1 << "\033[0m"; // Expone salud individual 1.
        else if (i == 3 && modo == 2) std::cout << "   \033[93mVidas P2: " << vidas2 << "\033[0m"; // Expone salud competitiva en condicional.
        else if (i == 5) std::cout << "   \033[95mPuntos: " << puntos << "\033[0m"; // Demuestra desempeño acumulado.
        else if (i == 6 && modo == 1) std::cout << "   \033[92mNivel: " << nivel << "\033[0m"; // Monitorea avance en progreso de campaña.
        else if (i == 8) std::cout << "   [P] Pausar | [Q] Salir"; // Entrega indicaciones clave fijas.
        else if (i == 10) std::cout << "   \033[93m" << mensaje << "\033[0m"; // Imprime los mensajes dinámicos notificados por el Motor y variables de tiempo.
        
        std::cout << "\033[K\n"; // Envía instrucción para cercenar cualquier resto de líneas superpuestas de la consola matriz de Linux.
    }
    std::cout << "\033[J" << std::flush; // Ordena despachar inmediatamente la memoria gráfica hacia la pantalla forzando el visualizador y suprimiendo basura terminal inferior.
    pthread_mutex_unlock(&mutexMapa); // Abandona la retención del arreglo admitiendo escrituras futuras.
}

int Mapa::mostrarMenu() { // Genera la navegación interactiva de inicio.
    std::cout << "\033[2J\033[H"; // Borra la consola entera preparando un entorno limpio para el pre-juego.
    std::cout << "--- BOMBERMAN CONCURRENTE ---\n"; // Despliega texto base.
    std::cout << "1. Modo Un Jugador (Contra IA)\n"; 
    std::cout << "2. Modo Dos Jugadores (Competitivo)\n"; 
    std::cout << "3. Ver Instrucciones\n"; 
    std::cout << "4. Puntajes Destacados\n"; 
    std::cout << "5. Salir del Juego\n"; 
    std::cout << "Seleccione una opcion: "; // Entrega entrada para el flujo.
    
    int opcion = 0; // Prepara un almacenamiento local predeterminado seguro.
    // Obliga al flujo a esperar una entrada válida y desecha basura si el usuario oprime teclas erróneas (letras de movimiento arrastradas).
    if (!(std::cin >> opcion)) { // Detecta anomalías o incompatibilidad de datos numéricos.
        std::cin.clear(); // Limpia la bandera de interbloqueo del flujo interno de cin.
        std::cin.ignore(10000, '\n'); // Descarta miles de caracteres atrapados en el buffer temporal del hardware.
    }
    return opcion; // Devuelve la selección procesada.
}

void Mapa::mostrarInstrucciones() { // Proyecta documentación de asistencia.
    std::cout << "\033[2J\033[H--- INSTRUCCIONES ---\n"; // Vuelve a ejecutar limpieza absoluta.
    std::cout << "Jugador 1 (P): WASD para moverse, F para bomba.\n"; // Dicta distribución motora primaria.
    std::cout << "Jugador 2 (Q): Flechas para moverse, Enter para bomba.\n"; // Dicta distribución secundaria.
    std::cout << "Muros amarillos (X) son destructibles. Los grises (#) no.\n"; // Brinda datos técnicos de colisión.
    std::cout << "Los signos (+) te brindaran poderes aleatorios.\n"; // Notifica la funcionalidad polimórfica.
    std::cout << "Presione cualquier tecla y luego Enter para regresar..."; // Imprime advertencia de retorno pasivo.
    std::string pausa; // Declara objeto inerte.
    std::cin >> pausa; // Suspende lectura esperando al usuario humano.
}

void Mapa::mostrarPuntajes() { // Construye salida analítica archivada.
    std::cout << "\033[2J\033[H--- MEJORES PUNTAJES ---\n"; // Formatea terminal.
    std::ifstream archivo("puntajes.txt"); // Emplea controlador de entrada para ubicar el archivo en la unidad de disco.
    std::string linea; // Prepara reservorio para lectura línea a línea.
    if (archivo.is_open()) { // Valida si el archivo físico se logró cargar exitosamente en memoria RAM.
        while (getline(archivo, linea)) { // Extrae secuencialmente el texto de cada registro.
            std::cout << linea << "\n"; // Empuja el historial a la visualización.
        }
        archivo.close(); // Corta el enlace de consumo con el sistema de archivos de Windows/Linux.
    } else { // Resuelve rutas no ubicadas.
        std::cout << "No hay puntajes registrados aun.\n"; // Manejo de excepciones visuales.
    }
    std::cout << "Presione cualquier letra y Enter para regresar..."; // Solicitud al espectador.
    std::string pausa; // Elemento inactivo local.
    std::cin >> pausa; // Captura para reanudar el hilo maestro.
}

void Mapa::guardarPuntaje(int puntos) { // Graba de forma persistente.
    if (puntos > 0) { // Evalúa que los resultados merezcan catalogarse.
        std::ofstream archivo("puntajes.txt", std::ios::app); // Prepara enlace de salida activando modalidad de anexión para no destruir el documento viejo.
        if (archivo.is_open()) { // Verifica permisos operativos de disco.
            archivo << "Jugador - " << puntos << " pts\n"; // Inyecta el resultado formateado al final del documento.
            archivo.close(); // Ejecuta liberación formal de la ruta de archivo para no causar fragmentación en el OS.
        }
    }
}

void Mapa::actualizarCelda(int x, int y, char caracter) { // Aplica escritura concurrente atómica controlada.
    pthread_mutex_lock(&mutexMapa); // Bloquea acceso bidireccional evitando sobrescritura corrupta de dos hilos simultáneos en celdas distintas.
    matriz[x][y] = caracter; // Asienta el reemplazo espacial en coordenadas precisas.
    pthread_mutex_unlock(&mutexMapa); // Destraba la puerta otorgando permiso al siguiente hilo que solicite cambios.
}

char Mapa::obtenerCelda(int x, int y) { // Extrae valores espaciales con garantías atómicas concurrentes.
    pthread_mutex_lock(&mutexMapa); // Sella la estructura mientras verifica contenido de colisión inminente.
    char valor = matriz[x][y]; // Realiza copia superficial y veloz del punto solicitado para no saturar procesos bloqueantes.
    pthread_mutex_unlock(&mutexMapa); // Suelta inmediatamente las reglas de exclusión.
    return valor; // Retorna réplica limpia e imperturbable.
}