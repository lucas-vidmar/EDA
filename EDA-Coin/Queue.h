template <typename T1> class Queue {
public:
  Queue() {} // Constructor por defecto
  virtual ~Queue() {} // Destructor

  virtual void clear() = 0; // Limpia (inicializa) la cola

  virtual bool enqueue(const T1& value) = 0; // Encola un elemento
  virtual T1 dequeue() = 0; // Desencola un elemento

  virtual const T1& getFrontValue() = 0; // Retorna front
  virtual int getLength() const = 0; // Retorna el número de elementos

private:
  Queue(const Queue&) {} // Impide la copia
  void operator=(const Queue&) {} // Impide la asignación
};
