//
// Created by ubecerril on 3/30/26.
//
#include "Collection.h"
#include <iostream>

using namespace std;

void printCollection(Collection<int> &collection);

int main(int argc, char *argv[]) {
    // Create elements
    Collection<int> collection(10);

    // Check emptiness
    if (collection.isEmpty()) {
        cout << "Collection is empty" << endl;
    }

    // Insert elements
    for (int i = 0; i < 10; i++) {
        collection.insert(i);
    }

    // Print elements
    cout << "Elements in the collection: " << endl;
    printCollection(collection);

    // Check contains method
    cout << "Does the collection contains 4?: "<< collection.contains(4)<< endl;
    cout << "Does the collection contains 10?: "<< collection.contains(10)<< endl;

    // Remove method
    cout << "Collection before the remove: " << endl;
    printCollection(collection);

    cout << "Collection after remove 7: " << endl;
    collection.remove(7);
    printCollection(collection);

    // Make empty and check emptiness again
    collection.makeEmpty();
    if (collection.isEmpty())  cout << "Collection is empty again" << endl;
}

void printCollection(Collection<int> &collection) {
    for (int i = 0; i < collection.size(); ++i) {
        if (i == 0) cout << "{";
        if (i == collection.size() - 1) cout << collection[i] << "}";
        else cout << collection[i] << ", ";
    }
    cout << endl;
}