template <typename T1> class List {
public:
  List() {} // Constructor por defecto
  virtual ~List() {} // Destructor

  virtual void clear() = 0;  // Limpia (inicializa) la lista
  virtual int getLength() const = 0; // Retorna el número de elementos

  virtual bool moveToPos(int pos) = 0; // Define la posición actual
  virtual bool prev() = 0; // Retrocede una posición
  virtual bool next() = 0; // Avanza una posición
  virtual void moveToStart() = 0; // Retrocede al principio
  virtual void moveToEnd() = 0;  // Avanza al final
  virtual int getCurrPos() const = 0; // Devuelve la posición actual

  virtual bool insert(const T1& value) = 0; // Inserta en pos. actual
  virtual bool append(const T1& value) = 0; // Inserta al final
  virtual bool remove() = 0;  // Elimina el elemento en pos. actual

  virtual const T1& getValue() const = 0; // Devuelve elemento actual

private:
  List(const List&) {} // Impide la copia
  void operator=(const List&) {} // Impide la asignación
};
