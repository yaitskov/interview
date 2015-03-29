#include<iostream>
#include<stack>

using namespace std;

template<class T>
void sortStack(stack<T>& s) {
  if (s.empty()) {
    return;
  }
  stack<T> tmp;
  tmp.push(s.top());
  s.pop();
  while (1) {
    while (1) {
      if (s.empty()) {
        s = tmp;
        return;
      }
      if (tmp.top() > s.top()) {
        break;
      }
      tmp.push(s.top());
      s.pop();
    }
    int shift = 0;
    T c = s.top();
    s.pop();
    while (tmp.top() > c) {
      s.push(tmp.top());
      tmp.pop();
      ++shift;
    }
    tmp.push(c);
    for (int i = 0; i < shift; ++i) {
      tmp.push(s.top());
      s.pop();
    }
  }
  s = tmp;
}

int main() {
  stack<int> input;
  while (1) {
    int x;
    cin >> x;
    if (cin) {
      input.push(x);
    } else {
      break;
    }
  }
  sortStack(input);
  while (!input.empty()) {
    cout << input.top() << endl;
    input.pop();
  }
  return 0;
}
