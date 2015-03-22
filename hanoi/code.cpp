#include<iostream>
#include<stack>
#include<cassert>
using namespace std;

template <class T>
class Hanoi {
  typedef stack<T> s;
  typedef s& sr;
  void validate(s s) {
    for (int i = s.size(); i > 1; --i) {
      T head = s.top();
      s.pop();
      assert(head < s.top());
    }
  }
public:
  void move(int n, sr s, sr d, sr o) {
    assert(n >= 0);
    validate(s); validate(o); validate(d);
    if (n == 1) {
      d.push(s.top());
      s.pop();
    } else if (n > 1) {
      move(n - 1, s, o, d);
      move(1, s, d, o);
      move(n - 1, o, d, s);
    }
  }
};

int main() {
  int height;
  cin >> height;
  stack<int> source, other, destination;
  for (auto i = 0; i < height; ++i) {
    source.push(height - i);
  }
  const auto sourceCopy = source;
  Hanoi<int> algorithm;
  algorithm.move(height, source, destination, other);
  assert(source.empty());
  assert(other.empty());
  assert(sourceCopy == destination);
  cout << "ok" << endl;
  return 0;
}
