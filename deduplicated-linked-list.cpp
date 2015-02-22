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
  Item* deduplicate() {
    set<T> found;
    Item* p = this;
    found.insert(data);
    while (p->next) {
      Item* n = p->next;
      if (found.find(n->data) == found.end()) {
        p = n;
        found.insert(p->data);
      } else {
        p->next = n->next;
        n->next = nullptr;
        delete n;
      }
    }
    return this;
  }
  list<T> toList() {
    if (next) {
      auto result = next->toList();
      result.push_front(data);
      return result;
    }
    return list<T>({ data });
  }
};

typedef Item<int> ii;

int main() {
  assert(ii(1, new ii(3, new ii(2, new ii(1)))).deduplicate()->toList() == list<int>({1,3,2}));
  assert(ii(1, new ii(1, new ii(2, new ii(1)))).deduplicate()->toList() == list<int>({1,2}));
  assert(ii(1, new ii(2, new ii(2, new ii(1)))).deduplicate()->toList() == list<int>({1,2}));
  assert(ii(1, new ii(2, new ii(2, new ii(3)))).deduplicate()->toList() == list<int>({1,2,3}));
  return 0;
}
