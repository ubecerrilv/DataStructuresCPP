//
// Created by ubecerril on 1/7/26.
//

#include <iostream>
#include "List.h"

int main()
{
    std::cout << "=== Constructor por defecto ===\n";
    list<int> l1;
    std::cout << "Esta vacia? " << (l1.empty() ? "si" : "no") << "\n";

    std::cout << "\n=== Insertando elementos ===\n";
    for (int i = 1; i <= 5; i++)
        l1.insert(i * 10);

    std::cout << "Contenido de l1: ";
    for (const auto& x : l1)
        std::cout << x << " ";
    std::cout << "\n";

    std::cout << "\n=== Constructor con initializer_list ===\n";
    list<int> l2{1, 2, 3, 4, 5};
    std::cout << "Contenido de l2: ";
    for (const auto& x : l2)
        std::cout << x << " ";
    std::cout << "\n";

    std::cout << "\n=== Constructor desde arreglo ===\n";
    int arr[] = {7, 8, 9};
    list<int> l3(arr, 3);
    std::cout << "Contenido de l3: ";
    for (const auto& x : l3)
        std::cout << x << " ";
    std::cout << "\n";

    std::cout << "\n=== find ===\n";
    std::cout << "Indice del 30 en l1: " << l1.find(30) << "\n";
    std::cout << "Indice del 100 en l1: " << l1.find(100) << "\n";

    std::cout << "\n=== findKth ===\n";
    std::cout << "Elemento en posicion 2 de l1: " << l1.findKth(2) << "\n";

    std::cout << "\n=== Copy constructor ===\n";
    list<int> l4(l1);
    std::cout << "Contenido de l4: ";
    for (const auto& x : l4)
        std::cout << x << " ";
    std::cout << "\n";

    std::cout << "\n=== Move constructor ===\n";
    list<int> l5(std::move(l2));
    std::cout << "Contenido de l5: ";
    for (const auto& x : l5)
        std::cout << x << " ";
    std::cout << "\n";

    std::cout << "\n=== Copy assignment ===\n";
    l3 = l1;
    std::cout << "Contenido de l3: ";
    for (const auto& x : l3)
        std::cout << x << " ";
    std::cout << "\n";

    std::cout << "\n=== Move assignment ===\n";
    l4 = std::move(l5);
    std::cout << "Contenido de l4: ";
    for (const auto& x : l4)
        std::cout << x << " ";
    std::cout << "\n";

    std::cout << "\n=== makeEmpty ===\n";
    l1.makeEmpty();
    std::cout << "l1 esta vacia? " << (l1.empty() ? "si" : "no") << "\n";

    return 0;
}
