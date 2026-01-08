//
// Created by ubecerril on 1/7/26.
// This file implements the list ADT with an array
//

#ifndef CPP_LIST_H
#define CPP_LIST_H
#include <initializer_list>
#include <utility>
#include <iosfwd>
#include <stdexcept>

template<typename Item>
class list
{
private:
    Item* array;
    size_t size;
    size_t capacity;

public:
    list(const Item* from, const size_t size)
    : array(new Item[size]),
      size(size),
      capacity(size)
    {
        for (size_t i = 0; i < size; i++)
        {
            array[i] = from[i];
        }
    }

    explicit list(std::initializer_list<Item> init)
    : array(new Item[init.size()]),
      size(init.size()),
      capacity(init.size())
    {
        size_t i = 0;
        for (const auto& item : init)
        {
            array[i++] = item;
        }
    }

    list()
    : array(nullptr),
      size(0),
      capacity(0){ }

    // Destructor
    ~list()
    {
        delete[] array;
    }

    // Copy constructor
    list(const list& copy)
    : array(new Item[copy.size]),
      size(copy.size),
      capacity(copy.size)
    {
        for (size_t i = 0; i < size; i++) {
            array[i] = copy.array[i];
        }
    }

    // Move constructor
    list(list&& rhs) noexcept
    : array(rhs.array),
      size(rhs.size),
      capacity(rhs.capacity)
    {
        rhs.array = nullptr;
        rhs.size = 0;
        rhs.capacity = 0;
    }

    // Copy assignment
    list& operator=(const list& rhs)
    {
        if (this != &rhs) {
            list temp(rhs);
            std::swap(array, temp.array);
            std::swap(size, temp.size);
            std::swap(capacity, temp.capacity);
        }
        return *this;
    }


    // Move assignment
    list& operator=(list&& rhs) noexcept
    {
        std::swap(array, rhs.array);
        std::swap(size, rhs.size);
        std::swap(capacity, rhs.capacity);
        return *this;
    }

    //Methods to for range-based fors
    Item* begin() noexcept {
        return array;
    }

    Item* end() noexcept {
        return array + size;
    }

    const Item* begin() const noexcept {
        return array;
    }

    const Item* end() const noexcept {
        return array + size;
    }

    /*
     * OPERATIONS
     */

    void makeEmpty()
    {
        size = 0;
        capacity = 0;
        delete[] array;
        array = nullptr;
    }

    bool empty() const
    {
        return size == 0;
    }

    size_t find(const Item& item)
    {
        for (size_t i = 0; i < size; i++) {
            if (array[i] == item)
                return i;
        }
        return -1;
    }

    Item& findKth(size_t k)
    {
        if (k >= size)
            throw std::out_of_range("Indice fuera de rango");
        return array[k];
    }

    void insert(const Item& item)
    {
        if (size == capacity)
        {
            capacity *= 2;
            Item* arrayAux = new Item[capacity];
            for (size_t i = 0; i < size; i++)
            {
                arrayAux[i] = array[i];
            }
            delete[] array;
            array = arrayAux;
        }

        array[size++] = item;
    }
};
#endif //CPP_LIST_H