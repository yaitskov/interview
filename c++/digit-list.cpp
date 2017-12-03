#include<iostream>
#include<cassert>
#include<sstream>

using namespace std;

template <typename T>
struct Digit {
  typedef Digit* pDigit;
  const T digit;
  pDigit next;
  Digit(T digit, pDigit next = nullptr) : digit(digit), next(next) {}
  ~Digit() {
    if (next) {
      delete next;
    }
  }
  string toString() {
    auto p = this;
    stringstream s;
    while (p) {
      s << p->digit;
      p = p->next;
    }
    return s.str();
  }
  static pDigit create(const char* s) {
    if (*s) {
      return new Digit(*s - '0', create(s+1));
    }
    return nullptr;
  }
  static pDigit sum(pDigit a, pDigit b) {
    pDigit r = nullptr;
    pDigit head = nullptr;
    T overflow = 0;
    while (a && b) {
      auto s = a->digit + b->digit + overflow;
      if (r) {
        r->next = new Digit(s % 10);
        r = r->next;
      } else {
        head = r = new Digit(s % 10);
      }
      overflow = s / 10;
      a = a->next;
      b = b->next;
    }
    if (b) {
      a = b;
    }
    while (a) {
      auto s = a->digit + overflow;
      r->next = new Digit(s % 10);
      r = r->next;
      overflow = s / 10;
      a = a->next;
    }
    if (overflow) {
      r->next = new Digit(overflow);
    }
    return head;
  }
};

int main() {
  auto n1 = Digit<int>::create("315");
  auto n2 = Digit<int>::create("592");
  auto r = Digit<int>::sum(n1, n2);
  assert(r->toString() == "808");
  delete r;
  delete n1;
  delete n2;
  return 0;
}
