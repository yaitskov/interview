#include<iostream>
#include<set>
#include<list>
#include<cassert>

using namespace std;

template <typename T>
struct Item {
  const T data;
  Item* next;
  Item(T data, Item* next = nullptr) : data(data), next(next) {}
  ~Item() {
    if (next) {
      delete next;
    }
  }
  Item* lastNth(int n) {
    Item* p = this;
    Item* pnth = p;
    while (n-- > 0 && p) {
      p = p->next;
    }
    if (!p) {
      return nullptr;
    }
    while (p->next) {
      pnth = pnth->next;
      p = p->next;
    }
    return pnth;
  }
};

typedef Item<int> ii;

int main() {
  assert(ii(1, new ii(2, new ii(3, new ii(4)))).lastNth(0)->data == 4);
  assert(ii(1, new ii(2, new ii(3, new ii(4)))).lastNth(1)->data == 3);
  assert(ii(1, new ii(2, new ii(3, new ii(4)))).lastNth(2)->data == 2);
  assert(ii(1, new ii(2, new ii(3, new ii(4)))).lastNth(3)->data == 1);
  assert(ii(1, new ii(2, new ii(3, new ii(4)))).lastNth(4) == nullptr);
  assert(ii(1).lastNth(1) == nullptr);
  assert(ii(1).lastNth(0)->data == 1);
  return 0;
}
