template <typename T> class Node {
public:
  T value;        // Elemento para este nodo
  Node * next;    // Puntero al nodo siguiente

  Node(const T& value, Node * next = NULL) {
    this->value = value;
    this->next = next;
  }

  Node(Node * next = NULL) {
    this->next = next;
  }
};