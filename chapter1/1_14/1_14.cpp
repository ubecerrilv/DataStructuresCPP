//
// Created by ubecerril on 3/30/26.
//
#include <iostream>
#include "OrderedCollection.h"

using namespace std;

void printOrderedCollection(OrderedCollection<int>& oc);

int main(int argc, char *argv[]) {
    OrderedCollection<int> oc(10);

    // Insert elements
    oc.insert(5);
    oc.insert(2);
    oc.insert(8);
    oc.insert(1);
    oc.insert(7);

    cout << "Size: " << oc.size() << endl;
    printOrderedCollection(oc);

    // Show max and min
    if (!oc.isEmpty()) {
        cout << "Min: " << oc.findMin() << endl;
        cout << "Max: " << oc.findMax() << endl;
    }

    // Remove element
    oc.remove(5);
    cout << "After remove 5, size: " << oc.size() << endl;
    printOrderedCollection(oc);

    // Empty collection
    oc.makeEmpty();
    cout << "After makeEmpty, isEmpty: " << oc.isEmpty() << endl;

    return 0;
}

void printOrderedCollection(OrderedCollection<int>& oc) {
    for (int i = 0; i < oc.size(); ++i) {
        if (i == 0) cout << "{";
        if (i == oc.size() - 1) cout << oc[i] << "}";
        else cout << oc[i] << ", ";
    }
    cout << endl;
}