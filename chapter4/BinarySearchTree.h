//
// Created by ubecerril on 1/19/26.
//

#pragma once
#include <algorithm>
#include "dsexceptions.h"
#include <iosfwd>
#include <iostream>

template <typename Comparable>
class BinarySearchTree {
public:
    // Normal constructor
    BinarySearchTree()
        :root(nullptr) {}

    // Big five
    BinarySearchTree(const BinarySearchTree& rhs) noexcept
        :root{nullptr} {
        root = clone(rhs.root);
    }
    BinarySearchTree (BinarySearchTree&& rhs) noexcept
        :root{rhs.root} {
        rhs.root = nullptr;
    }
    ~BinarySearchTree() {
        makeEmpty(root);
    }
    BinarySearchTree& operator= (const BinarySearchTree& rhs) {
        if (this != &rhs) {
            BinarySearchTree copy = rhs;
            std::swap(*this, copy);
        }
        return *this;
    }
    BinarySearchTree& operator= (BinarySearchTree&& rhs) noexcept {
        std::swap(*this, rhs.root);
        return *this;
    }

    // Normal routines, they normally call the private recursive function
    const Comparable& findMin() const {
        if (isEmpty())
            // Throw and exception
            throw UnderflowException{ };
        return findMin(root)->theElement;
    }
    const Comparable& findMax() const {
        if (isEmpty())
            // Throw and exception
            throw UnderflowException{ };
        return findMax(root)->theElement;
    }
    bool contains(const Comparable& x) const {
        return contains(x, root);
    }
    bool isEmpty() const {
        return root == nullptr;
    }
    void printTree(std::ostream& out = std::cout) const{
        if (isEmpty())
            out << "The tree is empty ):";
        else
            printTree(root, out);
    }
    void makeEmpty() {
        makeEmpty(root);
    }
    void insert(const Comparable& x) {
        insert(x, root);
    }
    void insert(Comparable&& x) {
        insert(std::move(x), root);
    }
    void remove (const Comparable& x) {
        remove(x, root);
    }



private:
    struct BinaryNode {
        Comparable theElement;
        BinaryNode *left, *right;

        BinaryNode(const Comparable &e, BinaryNode *l, BinaryNode *r)
            : theElement(e), left(l), right(r) { }
        BinaryNode(Comparable && e, BinaryNode *l, BinaryNode *r)
            : theElement(std::move(e)), left(l), right(r) { }
    };

    // Data member with the info of the root
    BinaryNode* root;

    // Private function members, they normally are recursive
    void insert(const Comparable& x, BinaryNode *&node) {
        // Case 1: x is not in the tree (insert the new node)
        if (node == nullptr) {
            node = new BinaryNode(x, nullptr, nullptr);
        }
        // Case 2: x is less than the node's element (go to left node)
        else if (x < node->theElement) {
            insert(x, node->left);
        }
        // Case 3: x is greater than the node's element (go to right node)
        else if (x > node->theElement) {
            insert(x, node->right);
        }
        // Case 4: x is equal to the node's element (do nothing)
        else {
            ;
        }
    }
    void insert(Comparable&& x, BinaryNode *&node) {
        // Case 1: x is not in the tree (insert the new node)
        if (node == nullptr) {
            node = new BinaryNode(std::move(x), nullptr, nullptr);
        }
        // Case 2: x is less than the node's element (go to left node)
        else if (x < node->theElement) {
            insert(std::move(x), node->left);
        }
        // Case 3: x is greater than the node's element (go to right node)
        else if (x > node->theElement) {
            insert(std::move(x), node->right);
        }
        // Case 4: x is equal to the node's element (do nothing)
        else {
            ;
        }
    }
    void remove (const Comparable& x, BinaryNode *&node) {
        // Element not found, do nothing
        if (node == nullptr) {
            return;
        }
        // x is less than node's element
        if (x < node->theElement) {
            remove(x, node->left);
        // x is greater than node's element
        }else if (x > node->theElement) {
            remove(x, node->right);

        // x is equal to node's element, and has two children
        }else if (node->left != nullptr && node->right != nullptr) {
            // Set current node's element as the smallest element of the right tree
            node->theElement = findMin(node->right)->theElement;
            // Remove that element
            remove(node->theElement, node->right);

        // x is equal to the node's element and has one child
        }else {
            // Save the current node as oldNode to later delete
            const BinaryNode* oldNode = node;
            // Make current node point to its child
            node = (node->left != nullptr) ? node->left : node->right;
            // Delete the oldNode
            delete oldNode;
        }
    }
    BinaryNode* findMin(BinaryNode* node) const {
        // Recursive approach

        if (node == nullptr) {
            return nullptr;
        }
        // Base case
        if (node->left == nullptr) {
            return node;
        }
        return findMin(node->left);

    }
    BinaryNode* findMax(BinaryNode* node) const {
        // Recursive approach

        if (node == nullptr) {
            return nullptr;
        }
        // Base case
        if (node->right == nullptr) {
            return node;
        }
        return findMin(node->right);
    }
    bool contains(const Comparable& x, BinaryNode* node) const {
        // If node is null return false
        if (node == nullptr) {
            return false;
        }
        // If x is less than element's node (go left)
        if (x < node->theElement) {
            return contains(x, node->left);
        }
        // If x is greater than element's node
        if (x > node->theElement) {
            return contains(x, node->right);
        }
        // Match found
        return true;
    }
    void makeEmpty(BinaryNode*& node) {
        // Do a postorder and delete the elements
        if (node != nullptr) {
            // Delete left
            makeEmpty(node->left);
            // Delete right
            makeEmpty(node->right);
            // Delete current node
            delete node;
        }
        // Make node to point to a nullptr
        node = nullptr;

    }
    void printTree(BinaryNode* node, std::ostream& out, int level = 0) const {
        if (node != nullptr) {
            printTree(node->left, out, level + 1);
            for (int i = 0; i < level; i++)
                std::cout << "  ";
            out << node->theElement << "\n";
            printTree(node->right, out, level + 1);
        }
    }
    BinaryNode* clone(BinaryNode* node) const {
        if (node != nullptr) {
            return new BinaryNode(node->theElement, clone(node->left), clone(node->right));
        }
        return nullptr;
    }
};
