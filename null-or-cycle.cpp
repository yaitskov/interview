#include<iostream>
#include<cassert>
#include<cmath>

using namespace std;

struct Element {
  const Element * next;
  Element(const Element * next) : next(next) {}
  Element() : Element(nullptr) {}
  static bool isCycle(const Element * head) {
    char * cur = 0;
    while (head && (cur += sizeof(void*))) {
      head = head->next;
    }
    return head;
  }
};

int main() {
  Element * head = new Element;
  Element * const last = head;
  for (auto i = 0; i < 100000; ++i) {
    head = new Element(head);
  }
  assert(!Element::isCycle(head));
  last->next = head->next;
  assert(Element::isCycle(head));
  return 0;
}
