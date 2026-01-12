//
// Created by ubecerril on 1/8/26.
//

#ifndef CPP_DOUBLELINKEDLIST_H
#define CPP_DOUBLELINKEDLIST_H
#include <algorithm>
#include <list>

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
    class const_iterator {
    protected:
        List<Object>* theList;
        Node* current;

        Object& retrieve() const
        { return current->data; }

        const_iterator(List<Object>& lst, Node* p) : theList{&lst}, current{p}
        {}

        // Method to prove the list is valid
        void assertIsValid() {
            // Iterator not associated to any list, current to null (uninitialized iterator) and pointing to a valid node.
            if (theList == nullptr || current == nullptr || current == theList->head)
                // Throw the exception
                ;
        }

        // Declare class List as friend so we can use private methods in it.
        friend class List<Object>;

    public:
        const_iterator () : theList{nullptr},current{nullptr} {}

        const Object& operator*() const
        { return retrieve(); }

        // ++ prefix operator
        const_iterator& operator++()
        {
            current = current->next;
            return *this;
        }
        // ++ postfix operator
        const_iterator operator++(int)
        {
            const_iterator old = *this;
            ++*this;
            return old;
        }

        // == and != operators
        bool operator==(const const_iterator& rhs) const
        {
           // If they point to the same memory address they are equal
            return current == rhs.current;
        }
        bool operator!=(const const_iterator& rhs) const
        {
            // It uses operator == we just overloaded above
            return !(*this == rhs);
        }

    };

    // Inheritance from const_iterator, an iterator can do same things const_iterator does.
    class iterator : public const_iterator {
    public:
        iterator (){}

        // Accessor and mutator for * operator
        Object& operator*()
        { return const_iterator::retrieve(); }
        const Object& operator*() const
        { return const_iterator::retrieve(); }

        // Overload ++ operator because it returns a different type
        iterator& operator++() {
            this->current = this->current->next;
            return *this;
        }
        iterator operator++( int ) {
            iterator old = *this;
            ++*this;
            return old;
        }

    protected:
        explicit iterator(List<Object>& lst, Node* p) : const_iterator(lst, p) {}
        friend class List<Object>;
    };

    /********************************************************************************************
     *                                      CLASS MEMBERS
     ********************************************************************************************/
private:
    Node* head;
    Node* tail;
    int theSize;

public:
    // Zero params constructor
    List()
    { init (); }

    // Big five
    List(const List& rhs)
    {
        // Create an empty list and copy each element from the parameter to the new list
        init();
        for (const auto& obj: rhs)
            push_back(obj);
    }
    ~List()
    {
        // Clear each node, delete tail and head
        clear();
        delete head;
        delete tail;
    }
    List& operator=(const List& rhs)
    {
        // Create new list and swap with this, after the function call, the copy list (old this) will be destroyed
        List copy(rhs);
        std::swap(*this, copy);
        return *this;
    }
    explicit List(List&& rhs) noexcept
        :head(rhs.head), tail(rhs.tail), theSize(rhs.theSize){
        // Initialize elements by copy (trivial types) and leave parameter rhs with valid values.
        rhs.head = rhs.tail = nullptr;
        rhs.theSize = 0;
    }
    List& operator=(List && rhs) noexcept {
        // Just swap each attribute
        std::swap(head, rhs.head);
        std::swap(tail, rhs.tail);
        std::swap(theSize, rhs.theSize);

        return *this;
    }

    // Iterators
    iterator begin()
    { return {*this, head->next}; }
    const_iterator begin() const
    { return {*this, head->next}; }
    iterator end ()
    { return {*this, tail}; }
    const_iterator end() const
    { return {*this, tail}; }

    int size () const
    { return theSize; }
    bool empty() const
    {return theSize == 0; }
    void clear()
    {
        while (!empty())
            pop_front();
    }

    Object& front()
    { return *begin(); }
    const Object& front() const
    { return *begin(); }
    Object& back()
    { return *--end(); }
    const Object& back() const
    { return *--end(); }

    // Operations to pop elements
    void pop_front()
    { erase(begin()); }
    void pop_back()
    { erase(--end()); }

    // Operations to push elements
    void push_front(const Object& data)
    { insert(begin(), data); }
    void push_front(Object&& data)
    { insert(begin(), std::move(data)); }

    void push_back(const Object& data)
    { insert(end(), data); }
    void push_back(Object&& data)
    { insert(end(), std::move(data)); }

    // Operations to insert elements before a given node
    iterator insert(iterator itr, Object& data)
    {
        // Create a new node and change the pointers accordingly
        Node* p = itr->current;
        ++theSize;
        return { p->prev->next = p->prev = new Node(data, p->prev, p) };
    }
    iterator insert(const_iterator itr, Object&& data)
    {
        // Create a new node and change the pointers accordingly
        Node* p = itr->current;
        ++theSize;
        return { p->prev->next = p->prev = new Node(std::move(data), p->prev, p) };
    }

    // Operations to erase a node from the list
    iterator erase(iterator itr)
    {
        // Create a new iterator to return
        Node* p = itr->current;
        iterator retValue {p->next};

        // Change pointers and delete memory
        p->prev->next = p->next;
        p->next->prev = p->prev;
        --theSize;
        delete *itr;

        return retValue;
    }
    iterator erase(iterator from, iterator to) {
        while (from != to) {
            from = erase(from);
        }
        return to;
    }

private:
    // Method to initialize an empty list
    void init() {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }
};
#endif //CPP_DOUBLELINKEDLIST_H