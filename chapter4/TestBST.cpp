//
// Created by ubecerril on 1/19/26.
//

#include "BinarySearchTree.h"
#include <iostream>

int main() {
    BinarySearchTree<int> bst;

    // Insertar elementos
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int v : values) {
        bst.insert(v);
    }

    std::cout << "Arbol en orden (inorder):\n";
    bst.printTree();
    std::cout << "\n";

    // Probar contains
    std::cout << "Contiene 40? " << (bst.contains(40) ? "Si" : "No") << "\n";
    std::cout << "Contiene 25? " << (bst.contains(25) ? "Si" : "No") << "\n";

    // Probar findMin y findMax
    std::cout << "Minimo: " << bst.findMin() << "\n";
    std::cout << "Maximo: " << bst.findMax() << "\n";

    // Probar remove
    std::cout << "\nEliminando 20 (hoja)...\n";
    bst.remove(20);
    bst.printTree();
    std::cout << "\n";

    std::cout << "Eliminando 30 (un hijo)...\n";
    bst.remove(30);
    bst.printTree();
    std::cout << "\n";

    std::cout << "Eliminando 50 (dos hijos, raiz)...\n";
    bst.remove(50);
    bst.printTree();
    std::cout << "\n";

    // Probar constructor copia (clone)
    std::cout << "\nCreando copia del arbol...\n";
    BinarySearchTree<int> bstCopy = bst;

    std::cout << "Arbol original:\n";
    bst.printTree();
    std::cout << "\n";

    std::cout << "Arbol copiado:\n";
    bstCopy.printTree();
    std::cout << "\n";

    // Probar makeEmpty
    std::cout << "\nVaciando arbol original...\n";
    bst.makeEmpty();

    std::cout << "Arbol original vacio? "
              << (bst.isEmpty() ? "Si" : "No") << "\n";

    std::cout << "Arbol copiado sigue intacto:\n";
    bstCopy.printTree();
    std::cout << "\n";

    return 0;
}
