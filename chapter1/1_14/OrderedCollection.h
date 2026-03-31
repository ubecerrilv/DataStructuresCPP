//
// Created by ubecerril on 3/30/26.
//

#ifndef CPP_ORDEREDCOLLECTION_H
#define CPP_ORDEREDCOLLECTION_H
#include <stdexcept>

template<typename Comparable>
class OrderedCollection {
private:
    unsigned long theSize;
    unsigned long theCapacity;
    Comparable *theArray;

public:
    explicit OrderedCollection(const unsigned long capacity):theSize{0}, theCapacity{capacity}, theArray(new Comparable[capacity]) { }
    ~OrderedCollection() { delete[] theArray; }
    unsigned long size() const { return theSize; }
    bool isEmpty() const { return theSize == 0; }
    void makeEmpty() { theSize = 0; }
    void insert(const Comparable &x) {
        if (theSize >= theCapacity) return;

        // Insertion sort
        int j;
        for (j = theSize ; j > 0 && theArray[j-1] > x; j--) {
            theArray[j] = theArray[j - 1];
        }
        theArray[j] = x;
        theSize++;
    }
    void remove(const Comparable &x) {
        if (isEmpty()) return;

        // Find the element and shift the array elements to the left
        int i = 0;
        for (; i < theSize; ++i) {
            if (theArray[i] == x) break;
        }
        if (i == theSize) return;

        for (int j = i; j < theSize - 1; ++j) {
            theArray[j] = theArray[j + 1];
        }
        theSize--;
    }
    Comparable& findMin() {
        // If the collection is empty we return a nullptr
        if (isEmpty()) throw std::underflow_error("Empty collection");
        return theArray[0];
    }
    Comparable& findMax() {
        // If the collection is empty we return a nullptr
        if (isEmpty()) throw std::underflow_error("Empty collection");
        return theArray[theSize -1];
    }
    const Comparable &operator[](const int index) const {
        return theArray[index];
    }
    Comparable &operator[](const int index) {
        return theArray[index];
    }
};
#endif //CPP_ORDEREDCOLLECTION_H
