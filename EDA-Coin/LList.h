#ifndef LLIST_H
#define LLIST_H

#include <cstdio>

#include "List.h"
#include "Node.h"

template <typename T> class LList : public List<T> {
private:
  Node<T> * head;                             // Puntero al nodo head
  Node<T> * tail;                             // Puntero al nodo tail
  Node<T> * curr;                             // Puntero a la posición actual
  int listSize;                               // Cantidad de elementos almacenados
  T dummy;                                    // Elemento vacío para getValue

  void init() {                               // Método auxiliar para inicializar la lista
    curr = tail = head = new Node<T>;
    listSize = 0;
  }

  void removeAll() {                          // Método auxiliar para eliminar todos los nodos
    while (head != NULL) {
      curr = head;
      head = head->next;
      delete curr;
    }
  }

public:
  LList(int maxSize = 0) {
    init();
  }

  ~LList() {
    removeAll();
  }

  void clear() {
    removeAll();
    init();
  }

  int getLength() const {
    return listSize;
  }

  bool moveToPos(int pos) {
    if ((pos < 0) || (pos > listSize))
      return false;

    curr = head;
    for(int i = 0; i < pos; i++)
      curr = curr->next;
    return true;
  }

  bool prev() {
    if (curr == head)
      return false;

    Node<T> * temp = head;
    while (temp->next != curr)
      temp = temp->next;
    curr = temp;
    return true;
  }

  bool next() {
    if (curr == tail)
      return false;

    curr = curr->next;
    return true;
  }

  void moveToStart() {
    curr = head;
  }

  void moveToEnd() {
    curr = tail;
  }

  int getCurrPos() const {
    Node<T> * temp = head;
    int i;
    for (i = 0; curr != temp; i++)
      temp = temp->next;
    return i;
  }

  bool insert(const T& value) {
    curr->next = new Node<T>(value, curr->next);
    if (tail == curr)
      tail = curr->next;
    listSize++;
    return true;
  }

  bool append(const T& value) {
    tail = tail->next = new Node<T>(value, NULL);
    listSize++;
    return true;
  }

  bool remove() {
    if (curr == tail)
      return false;

    Node<T> * ltemp = curr->next;
    if (tail == curr->next)
      tail = curr;
    curr->next = curr->next->next;
    delete ltemp;
    listSize--;
    return true;
  }

  const T& getValue() const {
    if (curr->next == NULL)
      return dummy;

    return curr->next->value;
  }
};

#endif // LLIST_H
