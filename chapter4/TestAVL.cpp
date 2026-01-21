#include <iostream>
#include "AVLTree.h"

int main() {
    AVLTree<int> tree;

    std::cout << "=== Insertando elementos ===\n";
    int values[] = {10, 20, 30, 40, 50, 25};

    for (int v : values) {
        std::cout << "Insertando: " << v << "\n";
        tree.insert(v);
    }

    std::cout << "\nÁrbol en orden (inorder traversal):\n";
    tree.printTree();

    std::cout << "\n=== Probando búsquedas ===\n";
    std::cout << "Contiene 25? " << (tree.contains(25) ? "Sí" : "No") << "\n";
    std::cout << "Contiene 99? " << (tree.contains(99) ? "Sí" : "No") << "\n";

    std::cout << "\n=== Mínimo y máximo ===\n";
    try {
        std::cout << "Mínimo: " << tree.findMin() << "\n";
        std::cout << "Máximo: " << tree.findMax() << "\n";
    } catch (...) {
        std::cout << "Error obteniendo min/max\n";
    }

    std::cout << "\n=== Eliminando nodos ===\n";
    int toRemove[] = {40, 30, 10};

    for (int v : toRemove) {
        std::cout << "Eliminando: " << v << "\n";
        tree.remove(v);
        std::cout << "Árbol actual:\n";
        tree.printTree();
        std::cout << "-----------------\n";
    }

    std::cout << "\n=== Probando árbol vacío ===\n";
    tree.makeEmpty();
    tree.printTree();

    std::cout << "\n=== Prueba con strings ===\n";
    AVLTree<std::string> strTree;
    strTree.insert("delta");
    strTree.insert("alpha");
    strTree.insert("charlie");
    strTree.insert("bravo");

    std::cout << "Árbol de strings:\n";
    strTree.printTree();

    return 0;
}
