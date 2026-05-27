# Define el compilador de C++ a utilizar
CXX = g++

# Define las banderas de compilación
CXXFLAGS = -Wall -std=c++11 -Iinclude

# Define las banderas de enlace para incluir la librería de hilos POSIX obligatoria
LDFLAGS = -pthread

# Define los nombres de los directorios para organizar el entorno del proyecto
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = build

# Busca automáticamente todos los archivos con extensión .cpp dentro de la carpeta src
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Define los nombres de los archivos objeto .o correspondientes a partir de los archivos .cpp encontrados
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

# Define la ruta y el nombre del archivo ejecutable binario final
TARGET = $(BINDIR)/bomberman

# Regla predeterminada que se ejecuta al invocar el comando make sin argumentos
all: $(TARGET)

# Enlaza los archivos objeto en memoria para generar el archivo ejecutable final
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compila de forma individual cada archivo de código fuente .cpp transformándolo en un archivo objeto .o
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Elimina todos los archivos intermedios de compilación y los directorios generados para limpiar el proyecto
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Declara los objetivos falsos para evitar conflictos con archivos reales del mismo nombre
.PHONY: all clean