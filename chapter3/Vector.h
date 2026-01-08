//
// Created by ubecerril on 1/7/26.
//

#ifndef CPP_VECTOR_H
#define CPP_VECTOR_H
#include <bits/std_thread.h>

template<typename Object>
class vector
{
private:
    Object* objects;
    int theSize;
    int theCapacity;

public:
    static constexpr int SPARE_CAPACITY = 16;

    explicit vector(const int initialSize = 0):
    theSize {initialSize},
    theCapacity {initialSize + SPARE_CAPACITY}
    {
        objects = new Object[theCapacity];
    }

    // Big five
    // Copy constructor
    vector (const vector& v):
    theSize {v.theSize},
    theCapacity {v.theCapacity},
    objects {nullptr}
    {
        //Copy all objects
        objects = new Object[theCapacity];
        for (int i = 0; i < theCapacity; i++)
        {
            objects[i] = v.objects[i];
        }
    }

    // Copy assignment
    vector& operator= (const vector& v)
    {
        // It uses the copy constructor
        vector copy {v};
        std::swap(*this, copy);
        return *this;
    }

    // Destructor
    ~vector(){delete [] objects;}

    // Move constructor
    vector (vector&& v) noexcept :objects {v.objects}, theSize(v.theSize), theCapacity {v.theCapacity}
    {
        v.objects = nullptr;
        v.theSize = 0;
        v.theCapacity = 0;
    }

    // Move assignment
    vector& operator= (vector&& v) noexcept
    {
        std::swap(objects, v.objects);
        std::swap(theSize, v.theSize);
        std::swap(theCapacity, v.theCapacity);

        return *this;
    }

    /**************************************************/
    void reserve(const int newCapacity)
    {
        if (newCapacity < theSize)
            return;

        Object* newObjects = new Object[newCapacity];
        for (int i =0; i<theSize; i++)
            newObjects[i] = std::move(objects[i]);

        theCapacity = newCapacity;
        std::swap(objects, newObjects);
        delete[] newObjects;
    }

    void resize(const int newSize)
    {
        if (newSize > theCapacity)
            reserve(newSize * 2);
        theSize = newSize;
    }

    /**************************************************/
    Object& operator [](const int index)
    { return objects[index]; }

    const Object& operator [](const int index) const
    { return objects[index]; }

    /**************************************************/
    bool empty () const
    { return theSize == 0; }

    int size () const
    { return theSize;}

    int capacity () const
    { return theCapacity; }

    /**************************************************/
    void push_back(Object& x) {
        if (theSize == theCapacity)
            reserve(2 * theCapacity + 1);
        objects[theSize++] = x;
    }

    void push_back(Object&& x) {
        if (theSize == theCapacity)
            reserve(2 * theCapacity + 1);
        objects[theSize++] = std::move(x);
    }

    void pop_back() {
        --theSize;
    }

    const Object& back ( ) const {
        return objects[theSize-1];
    }

    // Declare iterators type
    typedef Object* iterator;
    typedef const Object* const_iterator;

    iterator begin()
    { return &objects[0]; }

    const iterator begin () const
    { return &objects[0]; }

    iterator end()
    { return &objects[size()]; }

    const iterator end() const
    { return &objects[size()]; }
};

#endif //CPP_VECTOR_H