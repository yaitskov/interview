#include<cassert>
#include<vector>
#include<algorithm>
#include<stack>

using namespace std;

template <typename T>
class StackMin {
  stack<T> items;
  stack<T> mins;
public:
  const T& min() const {
    return mins.top();
  }
  void push(const T& a) {
    items.push(a);
    if (mins.empty()) {
      mins.push(a);
    } else {
      mins.push(std::min(a, mins.top()));
    }
  }
  bool empty() const {
    return items.empty();
  }
  const T& top() const {
    return items.top();
  }
  void pop() {
    mins.pop();
    items.pop();
  }
};

int main() {
  StackMin<int> s;
  vector<pair<int, int>> itemsMins = { {4, 4}, {2, 2}, {3, 2}, {1, 1}, {0, 0} };
  for (auto p : itemsMins) {
    s.push(p.first);
    assert(s.min() == p.second);
  }
  vector<int> mins = { 0, 1, 2, 2, 4 };
  for (auto m : mins) {
    assert(s.min() == m);
    s.pop();
  }
  return 0;
}
