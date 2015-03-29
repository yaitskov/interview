#include<vector>
#include<cassert>

using namespace std;

template<class T>
class Stack {
  const int cap;
  int index;
  T* items;
public:
  Stack(int cap) : cap(cap),
                   index(-1),
                   items(new T[cap]) {}
  ~Stack() { delete[] items; }
  void push(const T& a) {
    items[++index] = a;
  }
  const T& top() const {
    return items[index];
  }
  void pop() {
    items[--index];
  }
  int capacity() const {
    return cap;
  }
  int size() const {
    return index + 1;
  }
};
template <class T>
class Linked {
public:
  Stack<T> stack;
  Linked* next;
  Linked(int capacity, Linked* next = nullptr) : stack(capacity), next(next) {}
};
template <class T>
class SetOfStacks {
  Linked<T> * head;
  void safePopHead() {
    if (head->next) {
      auto newHead = head->next;
      delete head;
      head = newHead;
    }
  }
public:
  SetOfStacks(int capacity) : head(new Linked<T>(capacity)) {}
  ~SetOfStacks() {
    while (head) {
      auto p = head->next;
      delete head;
      head = p;
    }
  }
  void push(const T& a) {
    if (head->stack.size() == head->stack.capacity()) {
      head = new Linked<T>(head->stack.capacity(), head);
    }
    head->stack.push(a);
  }
  const T& top() const {
    if (head->stack.size()) {
      return head->stack.top();
    } else if (head->next) {
      return head->next->stack.top();
    }
    return top();
  }
  void pop() {
    if (head->stack.size()) {
      head->stack.pop();
    } else {
      safePopHead();
      pop();
    }
  }
};

int main() {
  const int size = 100;
  SetOfStacks<int> ss(3);
  vector<int> expected;
  vector<int> got;
  for (int i = 0; i < size; ++i) {
    ss.push(i);
    expected.push_back(size - i - 1);
  }
  for (int i = 0; i < size; ++i) {
    got.push_back(ss.top());
    ss.pop();
  }
  assert(got == expected);
  return 0;
}
