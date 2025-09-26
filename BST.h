//
// Created by valma on 9/25/2025.
//

#ifndef BST_H
#define BST_H
#include <iostream>

struct Node {
    T data;
    Node* next;
    Node(T d= T(), Node* n = nullptr): data(d), next(n){}
};

template <typename T>
class Queue {
    Node<T>* frontN;
    Node<T>* backN;
public:

    Queue(): frontN(nullptr), backN(nullptr){}
    void enqueue(T x) {
        Node<T>* n = new Node(x);
        if(backN == nullptr) {
            frontN = backN = n;
        }else {
            backN->next = n;
            backN = n;
        }
    }


    void dequeue() {
        if(frontN == nullptr) {
            throw std::out_of_range("Queue is empty");
        }

        Node<T>* temp = frontN;
        frontN = frontN->next;
        if(frontN == nullptr) {
            backN = nullptr;
        }

        delete temp;
    }

    T& front() {
        if(frontN == nullptr) {
            throw std::out_of_range("Queue is empty");
        }
        return frontN->data;
    }

    bool isEmpty() {
        return frontN == nullptr;
    }
};

struct NodeBT {
    int data;
    NodeBT* left{nullptr};
    NodeBT* right{nullptr};
    explicit NodeBT(int data_) : data(data_) {}
};

class BSTree {
    NodeBT* root{nullptr};

public:
    BSTree() = default;
    ~BSTree() { clear(root); }

    // (Opcional) copia/move si los necesitas:
    BSTree(const BSTree& other) : root(clone(other.root)) {}
    BSTree& operator=(const BSTree& other) {
        if (this != &other) { clear(root); root = clone(other.root); }
        return *this;
    }
    BSTree(BSTree&& other) noexcept : root(other.root) { other.root = nullptr; }
    BSTree& operator=(BSTree&& other) noexcept {
        if (this != &other) { clear(root); root = other.root; other.root = nullptr; }
        return *this;
    }

    bool contains(int value) const {          // versión iterativa de find
        NodeBT* cur = root;
        while (cur) {
            if (value < cur->data) cur = cur->left;
            else if (value > cur->data) cur = cur->right;
            else return true;
        }
        return false;
    }

    // Mantén tu API "find" si quieres:


    void insert(int value) {
        NodeBT** cur = &root;
        while (*cur) {
            if (value < (*cur)->data) cur = &(*cur)->left;
            else if (value > (*cur)->data) cur = &(*cur)->right;
            else return; // ya existe, no insertamos duplicados
        }
        *cur = new NodeBT(value);
    }

    bool erase(int value) {                    // borra por valor
        return eraseNode(root, value);
    }

private:
    static void clear(NodeBT*& n) {
        if (!n) return;
        clear(n->left);
        clear(n->right);
        delete n;
        n = nullptr;
    }

    static NodeBT* clone(NodeBT* n) {
        if (!n) return nullptr;
        NodeBT* r = new NodeBT(n->data);
        r->left = clone(n->left);
        r->right = clone(n->right);
        return r;
    }

    static bool eraseNode(NodeBT*& n, int value) {
        if (!n) return false;
        if (value < n->data) return eraseNode(n->left, value);
        if (value > n->data) return eraseNode(n->right, value);

        // Encontrado
        if (!n->left) { NodeBT* r = n->right; delete n; n = r; return true; }
        if (!n->right){ NodeBT* l = n->left;  delete n; n = l; return true; }

        // Dos hijos: usar sucesor in-order (mínimo del subárbol derecho)
        NodeBT** succ = &n->right;
        while ((*succ)->left) succ = &(*succ)->left;
        n->data = (*succ)->data;
        NodeBT* toDel = *succ;
        *succ = (*succ)->right;
        delete toDel;
        return true;
    }
};

void postOrder(NodeBT* node) {
    if (node == nullptr) return;
    postOrder(node->left);   // 1. Recorre subárbol izquierdo
    postOrder(node->right);  // 2. Recorre subárbol derecho
    std::cout << node->data << " "; // 3. Visita nodo actual
}

void inOrder(NodeBT* node){
    if (node == nullptr) return;
    inOrder(node->left);                 // 1. izquierda
    std::cout << node->data << " ";      // 2. nodo
    inOrder(node->right);                // 3. derecha
}

void postOrder(NodeBT* node) const {
    if (node == nullptr) return;
    postOrder(node->left);              // 1. izquierda
    postOrder(node->right);             // 2. derecha
    std::cout << node->data << " ";     // 3. nodo
}

void levelOrder(NodeBT* root) {
    if (!root) return;

    Queue<NodeBT*> q;
    q.enqueue(root);

    while (!q.isEmpty()) {
        NodeBT* node = q.front(); q.dequeue();
        std::cout << node->data << " ";

        if (node->left)  q.enqueue(node->left);
        if (node->right) q.enqueue(node->right);
    }
}


#endif //BST_H
