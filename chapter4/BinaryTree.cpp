//
// Created by ubecerril on 1/15/26.
//

#include <iostream>
#include <stack>

struct binaryNode {
    char element;
    binaryNode* left;
    binaryNode* right;
};
using namespace std;

// Prototype functions
binaryNode* constructTree(const string& exp);
void printTree(binaryNode* root, int level );
void preOrder(const binaryNode* root);
void inOrder(const binaryNode* root);
void postOrder(const binaryNode* root);

int main() {
    cout << "This program shows how to build an expression tree from postfix expression" << endl;

    const string s {"12+345+**"};
    binaryNode* root = constructTree(s);
    cout << "This is the result tree:"  << endl;
    printTree(root, 0);

    cout << "This is the result tree in pre-order" << endl;
    preOrder(root);
    cout << endl;

    cout << "This is the result tree in in-order" << endl;
    inOrder(root);
    cout << endl;

    cout << "This is the result tree in post-order" << endl;
    postOrder(root);
    cout << endl;
}

binaryNode* constructTree(const string& exp) {
    // Create empty stack
    stack<binaryNode*> st{};

    // For each char in the input
    for (auto& c : exp) {
        // If an operand is found
        if (isdigit(c)) {
            // Insert a new node with the operand
            auto* node = new binaryNode();
            node->element = c;
            node->left = nullptr;
            node->right = nullptr;
            st.push(node);
        }else { // If an operator is found
            // Pop the two lastest operands or trees and create a new tree
            auto* left = st.top();
            st.pop();
            auto* right = st.top();
            st.pop();

            auto* newRoot = new binaryNode();
            newRoot->element = c;
            newRoot->left = left;
            newRoot->right = right;

            st.push(newRoot);
        }
    }

    return st.top();
}

void printTree(binaryNode* root, int level = 0) {
    if (root == nullptr)
        return;

    printTree(root->right, level + 1);

    for (int i = 0; i < level; i++)
        std::cout << "    ";

    std::cout << root->element << std::endl;

    printTree(root->left, level + 1);
}

void preOrder(const binaryNode* root) {
    if (root == nullptr)
        return;

    std::cout << root->element << " ";
    preOrder(root->left);
    preOrder(root->right);
}
void inOrder(const binaryNode* root) {
    if (root == nullptr)
        return;

    inOrder(root->left);
    std::cout << root->element << " ";
    inOrder(root->right);
}
void postOrder(const binaryNode* root) {
    if (root == nullptr)
        return;

    postOrder(root->left);
    postOrder(root->right);
    std::cout << root->element << " ";
}

