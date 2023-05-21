#ifndef GRAPH_H
#define GRAPH_H

#define GRAPH_UNVISITED 0
#define GRAPH_VISITED 1

// ADT de grafo
class Graph {
public:
  Graph() {} // Constructor por defecto
  virtual ~Graph() {} // Destructor

  virtual int getN() = 0; // Retorna el número de vértices
  virtual int getE() = 0; // Retorna el número de ejes

  virtual int getFirst(int v) = 0; // Retorna el primer vecino de v
  virtual int getNext(int v, int v2) = 0; // Retorna el próximo vecino de v

  virtual void setEdge(int v, int v2, int w) = 0; // Pone un eje entre v y v2
  virtual void removeEdge(int v, int v2) = 0; // Elimina el eje entre v y v2
  virtual bool isEdge(int v, int v2) = 0; // Dice si v y v2 están conectados
  virtual int getWeight(int v, int v2) = 0; // Retorna el peso entre v y v2

  virtual void setMark(int v, int value) = 0; // Pone la marca de un vértice
  virtual int getMark(int v) = 0; // Retorna la marca de un vértice

private:
  Graph(const Graph&) {} // Impide la copia
  void operator=(const Graph&) {} // Impide la asignación
};

#endif // GRAPH_H
