//
// Created by ubecerril on 3/25/26.
//

#ifndef CPP_COLLECTION_H
#define CPP_COLLECTION_H

template<typename Object>
class Collection {
private:
    Object *array;
    int theCurrentSize;
    int capacity;

public:
    explicit Collection(const int capacity): capacity{capacity}, theCurrentSize{0}, array {new Object[capacity]} { }
    ~Collection() {
        delete[] array;
    }
    int size() const {
        return theCurrentSize;
    }
    void insert(const Object &x) {
        if (theCurrentSize == capacity) return;
        array[theCurrentSize++] = x;
    }
    const Object &operator[](const int index) const {
        return array[index];
    }
    Object &operator[](const int index) {
        return array[index];
    }
    bool isEmpty() const {
        return theCurrentSize == 0;
    }
    void makeEmpty() {
        // Lazy deletion
        theCurrentSize = 0;
    }
    void remove(const Object &x) {

    }
    bool contains(const Object &x) const {
        for (int i = 0; i < theCurrentSize; ++i) {
            if (array[i] == x) return true;
        }
        return false;
    }
};
#endif //CPP_COLLECTION_H