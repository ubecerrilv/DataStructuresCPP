//
// Created by ubecerril on 1/21/26.
//

#ifndef CPP_AVLTREE_H
#define CPP_AVLTREE_H

#pragma once
#include <algorithm>
#include <iostream>

#include "dsexceptions.h"

template <typename Comparable>
class AVLTree {
public:
    // Normal constructor
    AVLTree()
        :root{nullptr}{}

    // Big five
    AVLTree(const AVLTree& rhs)
        :root{nullptr} {
        root =  clone(rhs.root);
    }
    AVLTree(AVLTree&& rhs) noexcept
        :root{rhs.root} {
        rhs.root = nullptr;
    }
    ~AVLTree() {
        makeEmpty();
    }
    AVLTree& operator=(const AVLTree& rhs) {
        if (this != &rhs) {
            AVLTree copy{rhs};
            std::swap(*this, copy);
        }
        return *this;
    }
    AVLTree& operator=(AVLTree&& rhs) noexcept {
        if (this != &rhs) {
            std::swap(root, rhs.root);
        }
        return *this;
    }

    // Normal routines, normally they call the private routines
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }
    bool isEmpty( ) const
    {
        return root == nullptr;
    }
    void printTree(std::ostream& out = std::cout ) const
    {
        if( isEmpty( ) )
            std::cout << "Empty tree\n";
        else
            printTree( root, out );
    }
    void makeEmpty( )
    {
        makeEmpty( root );
    }
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
    void remove( const Comparable & x )
    {
        remove( x, root );
    }

private:
    // AVL node structure
    struct AVLNode {
        Comparable element;
        AVLNode* left;
        AVLNode* right;
        int height;

        AVLNode(const Comparable& ele, AVLNode* left, AVLNode* right, int height = 0)
            :element{ele}, left{left}, right{right}, height{height} {}

        AVLNode(Comparable&& ele, AVLNode* left, AVLNode* right, int height = 0)
            :element{std::move(ele)}, left{left}, right{right}, height{height} {}
    };

    // Data member
    AVLNode* root;

    // Maximum heigh distance allow before a balance to be performed
    static constexpr int ALLOWED_IMBALANCE = 1;

    // Private recursive routines
    void insert( const Comparable & x, AVLNode * & t )
    {
        if( t == nullptr )
            t = new AVLNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );

        // After insert, we check and balance if needed
        balance( t );
    }
    void insert( Comparable && x, AVLNode * & t )
    {
        if( t == nullptr )
            t = new AVLNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );

        // After insert, we check and balance if needed
        balance( t );
    }
    void remove( const Comparable & x, AVLNode * & t )
    {
        if( t == nullptr )
            return;

        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            AVLNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }

        // After delete we need to balance each subtree
        balance( t );
    }
    AVLNode * findMin( AVLNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }
    AVLNode * findMax( AVLNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }
    bool contains( const Comparable & x, AVLNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
    void makeEmpty( AVLNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }
    void printTree(AVLNode* node, std::ostream& out, int level = 0) const {
        if (node != nullptr) {
            printTree(node->left, out, level + 1);
            for (int i = 0; i < level; i++)
                std::cout << "  ";
            out << node->element << "\n";
            printTree(node->right, out, level + 1);
        }
    }
    AVLNode * clone( AVLNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new AVLNode{ t->element, clone( t->left ), clone( t->right ), t->height };
    }

    // Methods to manage the AVLTree rotations
    int height( AVLNode *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }
    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    // Assume t is balanced or within one of being balanced
    void balance( AVLNode * & t )
    {
        if( t == nullptr )
            return;

        // If we have an imbalance (left higher to right)
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE ) {
            // Imbalance in left-left child
            if( height( t->left->left ) >= height( t->left->right ) ) {
                rotateWithLeftChild( t );
            // Imbalance in left-right child
            }else {
                doubleWithLeftChild( t );
            }

        // If we have and imbalance (right higher than left)
        }else if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE ) {
            // Imbalance in right-right child
            if( height( t->right->right ) >= height( t->right->left ) ) {
                rotateWithRightChild( t );
            // Imbalance in right-left child
            }else {
                doubleWithRightChild( t );
            }
        }

        // Update the height, each node is one level higher than the higher of its children
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }

    void rotateWithLeftChild( AVLNode * & k2 )
    {
        // Perform the rotation
        AVLNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;

        // Update the height of the moved nodes
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;

        // Update the root
        k2 = k1;
    }
    void rotateWithRightChild( AVLNode * & k1 )
    {
        // Perform the rotation
        AVLNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;

        //Update the height of the moved nodes
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;

        // Update the root
        k1 = k2;
    }
    void doubleWithLeftChild( AVLNode * & k3 )
    {
        // A double left rotation is a simple right rotation on the left child and a simple left rotation on the root node
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }
    void doubleWithRightChild( AVLNode * & k1 )
    {
        // A double right rotation is a simple left  rotation in the right child and a simple right rotation on the root node
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }
};
#endif //CPP_AVLTREE_H
