#include <iostream>
#include <cstring>

class Persona {
private:
    char* nombre;   // atributo dinámico (apuntador)
    int edad;       // atributo simple

public:
    // 1. Constructor por defecto
    Persona();

    // 2. Constructor con parámetros
    Persona(const char* nombre, int edad);

    // 3. Destructor
    ~Persona();

    // 4. Constructor de copia
    Persona(const Persona& other);

    // 5. Operador de asignación por copia
    Persona& operator=(const Persona& other);

    // 6. Constructor de movimiento
    Persona(Persona&& other) noexcept;

    // 7. Operador de asignación por movimiento
    Persona& operator=(Persona&& other) noexcept;

    // Método auxiliar
    void mostrar() const;
};

/* =====================================================
   IMPLEMENTACIONES
   👉 TU TRABAJO ES COMPLETAR EL BIG FIVE
   ===================================================== */

Persona::Persona() {
    nombre = nullptr;
    edad = 0;
}

Persona::Persona(const char* nombre, int edad) {
    if(nombre != nullptr)
    {
        this->nombre = new char[std::strlen(nombre)+1];
        std::strcpy(this->nombre, nombre);
    }else
    {
        this->nombre = nullptr;
    }
    this->edad = edad;
}

Persona::~Persona() {
    delete[] nombre;
}

Persona::Persona(const Persona& other) {
    if(nombre != nullptr)
    {
        this->nombre = new char[std::strlen(other.nombre)+1];
        std::strcpy(this->nombre, other.nombre);
    }else
    {
        this->nombre = nullptr;
    }
    this->edad = other.edad;
}

Persona& Persona::operator=(const Persona& other) {
    if(this != &other)
    {
        Persona copy {other};
        std::swap(*this, copy);
    }
    return *this;
}

Persona::Persona(Persona&& other) noexcept : nombre{other.nombre}, edad{other.edad}{
    other.nombre = nullptr;
    other.edad = 0;
}

Persona& Persona::operator=(Persona&& other) noexcept {
    std::swap(nombre, other.nombre);
    std::swap(edad, other.edad);
    return *this;
}

void Persona::mostrar() const {
    std::cout << "Nombre: "
              << (nombre ? nombre : "null")
              << ", Edad: " << edad << std::endl;
}

/* =====================================================
   MAIN DE PRUEBAS
   ===================================================== */

int main() {

    std::cout << "=== Constructor normal ===\n";
    Persona p1("Juan", 25);
    p1.mostrar();

    std::cout << "\n=== Constructor de copia ===\n";
    Persona p2 = p1;  // constructor copia
    p2.mostrar();

    std::cout << "\n=== Operador asignación copia ===\n";
    Persona p3;
    p3 = p1;          // asignación copia
    p3.mostrar();

    std::cout << "\n=== Constructor de movimiento ===\n";
    Persona p4 = std::move(p1);
    p4.mostrar();
    p1.mostrar();     // debe quedar en estado válido

    std::cout << "\n=== Operador asignación movimiento ===\n";
    Persona p5;
    p5 = std::move(p2);
    p5.mostrar();
    p2.mostrar();     // debe quedar en estado válido

    std::cout << "\n=== Fin del programa ===\n";

    return 0;
}
