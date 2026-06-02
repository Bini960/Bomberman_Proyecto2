# Bomberman Concurrente

Un juego de Bomberman para consola, desarrollado en C++ como proyecto de clase. Esta versión usa múltiples hilos con POSIX Pthreads para manejar la ejecución simultánea de jugadores, enemigos y bombas.

## ¿Qué es este proyecto?

- Una versión de Bomberman basada en texto (ASCII) que se ejecuta en la terminal.
- Combina lógica de juego con programación concurrente y sincronización de hilos.
- Soporta modo de 1 jugador contra inteligencia artificial y modo de 2 jugadores en la misma terminal.
- Guarda los puntajes en el archivo `puntajes.txt`.

## Estructura del proyecto

- `src/` : Código fuente en C++.
- `include/` : Archivos de cabecera (`.h`) con las clases y definiciones.
- `Makefile` : Archivo de compilación para generar el ejecutable.
- `config.txt` : Parámetros del proyecto y ajuste de variables.
- `puntajes.txt` : Archivo de resultados guardados.

## Archivos importantes

- `src/main.cpp` : Punto de entrada del juego.
- `src/MotorJuego.cpp` : Lógica principal del juego, ciclo de ejecución y estado.
- `src/Mapa.cpp` : Dibuja la consola, el menú y las instrucciones.
- `src/ManejadorEntrada.cpp` : Lee las teclas de forma asíncrona.
- `src/Jugador.cpp` : Controla las acciones del jugador y la interacción con el mapa.
- `src/Enemigo.cpp` : Lógica de movimiento y comportamiento de los enemigos.
- `src/Bomba.cpp` : Manejo de explosivos y detonaciones.
- `src/Poder.cpp` : Implementación de power-ups y efectos especiales.

## Requisitos

- Compilador `g++` compatible con C++11.
- Biblioteca POSIX Threads (`-pthread`).
- Terminal que soporte secuencias ANSI para colores y borrado de pantalla.
- En Windows, se recomienda usar WSL, Git Bash o MinGW-w64 con soporte POSIX.

## Compilación

Desde la carpeta del proyecto, ejecute:

```bash
make
```

Esto creará el ejecutable en `build/bomberman`.

Si no usa `make`, puede compilar manualmente con:

```bash
g++ -Wall -std=c++11 -Iinclude src/*.cpp -o build/bomberman -pthread
```

## Ejecución

Después de compilar, inicie el juego con:

```bash
./build/bomberman
```

En Windows con PowerShell o CMD, si el ejecutable es compatible, use:

```powershell
build\bomberman.exe
```

> Nota: Este proyecto está diseñado para entornos POSIX. Si tiene problemas en Windows, pruebe desde WSL o Git Bash.

## Controles del juego

### Comunes

- `P` : Pausar / reanudar el juego.
- `Q` : Salir del juego.

### Jugador 1

- `W` : Mover hacia arriba.
- `A` : Mover hacia la izquierda.
- `S` : Mover hacia abajo.
- `D` : Mover hacia la derecha.
- `F` : Colocar bomba.

### Jugador 2 (modo competitivo)

- Flechas del teclado : Mover.
- `Enter` : Colocar bomba.

## Cómo jugar

1. Ejecute el programa.
2. Seleccione una opción del menú:
   - Modo 1 jugador: juega contra enemigos controlados por IA.
   - Modo 2 jugadores: compiten en la misma pantalla.
   - Instrucciones: muestra los controles.
   - Puntajes destacados: lee `puntajes.txt`.
3. Avanza por el mapa, coloca bombas para destruir enemigos y muros destructibles.
4. Recoge power-ups (`+`) para mejorar tu capacidad.
5. El juego termina cuando el jugador pierde todas sus vidas o decide salir.

## Puntajes

- Los resultados se guardan en `puntajes.txt`.
- Si no existe, se crea al primer puntaje registrado.
- El archivo se muestra desde el menú de puntajes.

## Notas técnicas

- El proyecto usa `pthread_mutex_t` y `pthread_cond_t` para proteger el acceso al tablero y al estado del juego.
- El mapa se dibuja con caracteres coloreados usando códigos ANSI.
- Las teclas se leen en modo no bloqueante para permitir entrada continua sin frenar el bucle principal.

## Equipo de desarrollo

- Andrés Castro
- Estuardo García
- Junior Lancerio
- Franco Paiz

## Sugerencias para mejorar

- Agregar soporte para más niveles y dificultad progresiva.
- Incluir menú de selección de mapas personalizados.
- Añadir mejores sonidos o efectos visuales si se usa una librería de consola avanzada.
