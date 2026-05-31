#ifndef PODER_H // Protege contra redefiniciones del archivo.
#define PODER_H // Declara la cabecera del módulo.

class Poder { // Define la clase base abstracta para los beneficios.
protected: // Permite el acceso a clases derivadas.
    int posX; // Coordenada X en la matriz.
    int posY; // Coordenada Y en la matriz.

public: // Métodos de acceso general.
    Poder(int x, int y); // Constructor base de inicialización.
    virtual ~Poder() = default; // Destructor virtual para asegurar limpieza polimórfica segura.
    virtual void aplicarEfecto() = 0; // Método virtual puro, obliga a las clases hijas a implementarlo.
};

class PoderVelocidad : public Poder { // Hereda de la clase base para crear un objeto específico.
public: // Métodos del beneficio de velocidad.
    PoderVelocidad(int x, int y); // Constructor especializado.
    void aplicarEfecto() override; // Sobrescribe el método para aplicar su lógica única.
};

class PoderRadio : public Poder { // Hereda de la clase base para crear la mejora explosiva.
public: // Métodos del beneficio de explosión.
    PoderRadio(int x, int y); // Constructor especializado.
    void aplicarEfecto() override; // Sobrescribe el método con su comportamiento único.
};

#endif // Fin de la declaración de clases.