#include <cstdio>

#include "Queue.h"
#include "LList.h"

template <typename T> class LQueue : public Queue<T> {
private:
  LList<T> list;

public:
  LQueue() {
  }

  ~LQueue() {
  }

  void clear() {
    list.clear();
  }

  bool enqueue(const T& value) {
    return list.append(value);
  }

  T dequeue() {
    list.moveToStart();
    T temp = list.getValue();
    list.remove();
    return temp;
  }

  const T& getFrontValue() {
    list.moveToStart();
    return list.getValue();
  }

  int getLength() const {
    return list.getLength();
  }
};
