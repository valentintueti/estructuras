//
// Created by valma on 9/25/2025.
//

#ifndef CIRCULARDOUBLYLINKEDLIST_H
#define CIRCULARDOUBLYLINKEDLIST_H
#include <iostream>
using namespace std;

template <typename T>
struct Node {
    Node* next;
    Node* prev;
    T data;

    Node(T val = T(), Node* nxt = nullptr, Node* prv = nullptr): data(val), next(nxt), prev(prv) {}
};

template <typename T>
class CDLinkedList {
    Node<T>* head;
public:
    CDLinkedList() {
        head = nullptr;
    }
  bool empty() {
        return head->next == head; // si el next del head (el segundo) apunta al head, la lista esta vacia
    }

    T front() {
        if (empty()) { // usamos la funciond e empty para verificar si la lista esta vacia
            return T(); // si la ista vacia retorna valor por defecto
        }

        return head->next->data; // sino, retorna el valor del primer nodo
    }

    void push_front(T val) {
        Node<T>* nuevo = new Node<T>(val); // crear el nodo para insertar
        nuevo->next = head->next; // asignar el next del nuevo nodo al antiguo primer nodo
        nuevo->prev = head; // asignar el prev del nuevo nodo al head
        head->next->prev = nuevo; // Actualizar el prev del antiguo primer nodo
        head->next = nuevo; // Poner el nuevo nodo como el primer nodo
    }

    T pop_front() {
        if (empty()) {
            return T(); // si la lista esta vacia retorna valor por defecto
        }

        Node<T>* temp = head->next; // temp que apunta al primer nodo
        T eliminar = temp->data; // guardar el valor del nodo a eliminar (el primero)
        head->next = temp->next; // conectar el next del head al segundo nodo
        temp->next->prev = head; // actualizar el prev del segundo nodo al head
        delete temp; // eliminar el temp ya que la informacion ya fue guardada
        return eliminar; // retornar el valor eliminado
    }

    void insert(T val, int pos) {
        if (pos < 0 or pos > this->size()) { // verificar si la posición es válida
            throw std::out_of_range("Posicion fuera del tamano de la lista");
        }

        int size = 0; // calcular el tamaño actual de la lista
        Node<T>* temp = head->next; // temp que apunta al primer nodo
        while (temp != head) { // recorrer la lista hasta llegar al head
            size++; // aumenta la varible size que calcula el tamaño
            temp = temp->next; // mover el temp al siguiente nodo
        }

        if (pos == 0) { // si esta al incio, usar push_front
            push_front(val); // push front al valor
            return;
        }

        if (pos == size) { // si esta al final, usar push_back
            push_back(val); // push back al valor
            return;
        }

        Node<T>* actual = head->next; // temp (actual) que apunta al nodo inicial
        for (int i = 0; i < pos; i++) { // recorrer la lista hasta la posición asignada
            actual = actual->next; // mover el temp (actual) al siguiente nodo para generar el ciclo
        }

        Node<T>* nuevo = new Node<T>(val); // crear el nuevo nodo
        nuevo->next = actual; // asignar el next del nuevo nodo al nodo en la posición actual
        nuevo->prev = actual->prev; // asignar el prev del nuevo nodo al nodo previo al actual
        actual->prev->next = nuevo; // actualizar el next del nodo previo al actual al nuevo nodo
        actual->prev = nuevo;  // actualizar el prev del nodo actual al nuevo nodo
    }

    T back() {
        if (empty()){throw std::out_of_range("List is empty");}

        return head->prev->data;
    }

    void push_back(T val) {
        Node<T>* newNode = new Node(val);

        if(!head){
          head = newNode;
          newNode->next = head;
          head->prev = head;
        }

        newNode->prev=head->prev;
        newNode->next =head;
        newNode->prev->next = newNode;
        head->prev = newNode;
    }

    T pop_back() {
        if (empty()){throw std::out_of_range("List is empty");}

        Node<T>* temp = head->prev;
        T val = temp->data;
        head->prev->prev->next =  head;
        head->prev = head->prev->prev;
        delete temp;
        return val;
    }

    void clear() {
        auto pt1 = head->next;
        while(pt1!= head) {
            auto temp = pt1;
            pt1 = pt1->next;
            delete temp;
        }
        head->next = head;
        head->prev = head;
    }


    int size() {
        if (empty()){return 0;}

        int i = 0;
        Node<T>* temp = head->next;
        while (temp != head) {
            i++;
            temp = temp->next;
        }
        return i;
    }

    void remove(int pos) {
        if(empty()) {throw std::out_of_range("List is empty");}

        if(pos<0 || pos>=size()) {throw std::out_of_range("Index out of range");}

        Node<T>* temp = head->next;
        int i = 0;
        while (i < pos) {
            temp = temp->next;
            i++;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
    }

    T operator[](int pos) {
        if(pos<0 or pos>=this->size()) {
            throw std::out_of_range("Index out of range");
        }
        Node<T>* temp = head->next;
        int i = 0;
        while (i < pos) {
            temp = temp->next;
            i++;
        }
        return temp->data;
    }

    void reverse() {
        Node<T>* actual = head;
        do {
            Node<T>* ptr = actual->next;
            actual->next = actual->prev;
            actual->prev = ptr;
            actual = ptr;
        }while(actual!=head);
    }

    void deletenode(Node*& curr) {
      Node* tail = head->prev
        Node* prev = curr->prev;
        Node* next = curr->next;
        Node* temp = curr;
        prev->next = next;
        next->prev = prev;
        if (curr == head)
            head = next;
        if (curr == tail)
            tail = prev;
        curr->next = nullptr;
        curr->prev = nullptr;
        curr = next;
        delete temp;
    }
};


#endif //CIRCULARDOUBLYLINKEDLIST_H
