#include<iostream>
#include<cassert>
#include<memory>

using namespace std;

template <typename T>
struct Item {
  const T data;
  unique_ptr<Item> next;
  Item(T data, unique_ptr<Item> next = nullptr) : data(data), next(move(next)) {}

  static unique_ptr<Item> create(const char* s) {
    if (*s) {
      return unique_ptr<Item>(new Item(*s, create(s+1)));
    }
    return nullptr;
  }
  void remove() {
    assert(next);
    //swap(const_cast<T&>(this->data), const_cast<T&>(next->data));
    const_cast<T&>(this->data) = move(next->data);
    next = move(next->next);
  }
};

int main() {
  auto l = Item<char>::create("abcde");
  assert(l->/*b*/next->/*c*/next->data == 'c');
  l->/*b*/next->/*c*/next->remove();
  assert(l->/*b*/next->data == 'b');
  assert(l->/*b*/next->/*d*/next->data == 'd');
  return 0;
}
