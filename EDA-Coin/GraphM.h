#include "Graph.h"

// Implementación con matriz de adyacencia
class GraphM : public Graph {
private:
  int n, e;          // Almacena el número de vértices y ejes
  int ** matrix;     // Almacena los datos
  int * mark;        // Almacena las marcas

public:
  GraphM(int n) {
    this->n = n;
    e = 0;
    mark = new int[n]; // Inicializa las marcas
    for (int i = 0; i < n; i++)
      mark[i] = GRAPH_UNVISITED;
    matrix = new int *[n]; // Inicializa la matriz
    for (int i = 0; i < n; i++)
      matrix[i] = new int[n];
    for (int i = 0; i < n; i++) // Inicializa los pesos en cero
      for (int j = 0; j < n; j++)
        matrix[i][j] = 0;
  }

  ~GraphM() {
    for (int i = 0; i < n; i++)
      delete[] matrix[i];
    delete[] matrix;
    delete[] mark;
  }

  int getN() {
    return n;
  }

  int getE() {
    return e;
  }

  int getFirst(int v) {
    for (int i = 0; i < n; i++)
      if (matrix[v][i] != 0)
        return i;
    return n;    // Retorna n si no se encuentra
  }

  int getNext(int v, int v2) {
    for(int i = v2 + 1; i < n; i++)
      if (matrix[v][i] != 0)
        return i;
    return n;    // Retorna n si no se encuentra
  }

  void setEdge(int v, int v2, int w = 1) {
    if (w <= 0)
      return;

    if (matrix[v][v2] == 0)
      e++;
    matrix[v][v2] = w;
  }

  void removeEdge(int v, int v2) {
    if (matrix[v][v2] != 0)
      e--;
    matrix[v][v2] = 0;
  }

  bool isEdge(int v, int v2) {
    return matrix[v][v2] != 0;
  }

  int getWeight(int v, int v2) {
    return matrix[v][v2];
  }

  int getMark(int v) {
    return mark[v];
  }

  void setMark(int v, int value) {
    mark[v] = value;
  }
};
