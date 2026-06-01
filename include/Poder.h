#ifndef PODER_H // Protege contra redefiniciones del archivo durante fase de enlazado.
#define PODER_H // Declara la cabecera del módulo abstracto.

class Poder { // Define la clase base abstracta preparativa para un sistema de beneficios polimórficos estructurados.
protected: // Permite el acceso exclusivo interno a clases de herencia directa.
    int posX; // Coordenada resguardada X en la matriz para mapear colisiones.
    int posY; // Coordenada resguardada Y en la matriz para mapeo virtual.

public: // Establece los métodos de interfaz expuesta al entorno.
    Poder(int x, int y); // Constructor base para fijar dimensiones desde su origen.
    virtual ~Poder() = default; // Destructor virtual imperativo para asegurar la correcta destrucción progresiva de memoria en derivaciones lógicas.
    virtual void aplicarEfecto() = 0; // Fuerza estrictamente un diseño puro abstrayendo la implementación obligatoria de rutinas hacia los subtipos específicos.
};

class PoderVelocidad : public Poder { // Subclase que hereda los atributos y extiende la interfaz base emulando un concepto concreto.
public: // Expone comportamiento derivado.
    PoderVelocidad(int x, int y); // Constructor derivativo que se ensambla a la llamada padre.
    void aplicarEfecto() override; // Exige implementar su firma única.
};

class PoderRadio : public Poder { // Subclase designada para contener una expansión ofensiva.
public: // Exposición de datos de clase.
    PoderRadio(int x, int y); // Constructor especializado.
    void aplicarEfecto() override; // Integra la variante operativa que muta el atributo ofensivo.
};

#endif // Fin de la declaración de bloque lógico estructural.