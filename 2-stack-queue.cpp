#include<iostream>
#include<stack>
#include<cassert>
#include<vector>

using namespace std;

template <typename T>
class MyQueue {
  typedef stack<T> s;
  stack<T> in;
  static inline void move(s& src, s& dst) {
    dst.push(src.top());
    src.pop();
  }
public:
  void enqueue(const T& a) {
    in.push(a);
  }
  bool empty() const {
    return in.empty();
  }
  T dequeue() {
    stack<T> buffer;
    while (in.size() > 1) {
      move(in, buffer);
    }
    const T result = in.top();
    in.pop();
    while (buffer.size()) {
      move(buffer, in);
    }
    return result;
  }
};

int main() {
  MyQueue<int> q;
  for (int i = 0; i < 10; ++i) {
    q.enqueue(i);
  }
  vector<int> get;
  while (!q.empty()) {
    get.push_back(q.dequeue());
  }
  const vector<int> expected = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  assert(expected == get);
  return 0;
}
