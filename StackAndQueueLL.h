//
// Created by valma on 9/25/2025.
//

#ifndef STACKANDQUEUELL_H
#define STACKANDQUEUELL_H

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


template<typename T>
class Stack {
    Node<T>* topN;
public:
    Stack(): topN(nullptr) {}

    void push (T data) {
        Node<T>* n = new Node(data);
        n->next = topN;
        topN = n;
    }

    void pop() {
        if(topN == nullptr) {
            throw std::out_of_range("Stack is empty");
        }
        Node<T>* temp = topN;
        topN = topN->next;
        delete temp;
    }

    T& top() {
        if(topN == nullptr) {
            throw std::out_of_range("Stack is empty");
        }
        return topN->data;
    }

    bool isEmpty() {
        return topN==nullptr;}
};

#endif //STACKANDQUEUELL_H
