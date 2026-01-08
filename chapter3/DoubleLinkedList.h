//
// Created by ubecerril on 1/8/26.
//

#ifndef CPP_DOUBLELINKEDLIST_H
#define CPP_DOUBLELINKEDLIST_H
#include <algorithm>

template<typename Object>
class List {
    /********************************************************************************************
     *                            CLASSES NEEDED BY LIST ITSELF
     ********************************************************************************************/
private:
    // This class' members cannot be accessed from outside even when they are public inside the struct,
    // this is because Node struct is a private member.
    struct Node {
        Object data;
        Node* prev;
        Node* next;

        // Constructor for a new node from an L-value, copy semantics
        explicit Node(const Object& data = Object {}, Node* prev = nullptr, Node* next = nullptr)
            : data (data), prev (prev), next (next)
        {}

        // Constructor for a new node from an R-value, move semantics
        explicit Node(Object&& d, Node* prev = nullptr, Node* next = nullptr)
            :data (std::move(d)), prev (prev), next (next)
        {}
    };

public:
    class const_iterator{};
    // Inheritance from const_iterator, an iterator can do same things const_iterator does.
    class iterator : public const_iterator{};

    /********************************************************************************************
     *                                      CLASS MEMBERS
     ********************************************************************************************/
private:
    Node* head;
    Node* tail;
    int thesize;

public:
};
#endif //CPP_DOUBLELINKEDLIST_H