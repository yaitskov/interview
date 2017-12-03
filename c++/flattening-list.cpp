#include<cstring>
#include<cassert>
#include<set>

using namespace std;

template<typename T>
struct Item {
  typedef multiset<T> ItemSet;

  T data;
  Item * next;
  Item * prev;
  Item * child;

  Item(const T&& data, Item * next, Item * child)
    : data(data), next(next), child(child) {
    if (next) {
      next->prev = this;
    }
  }

  Item(const T&& data) : Item(move(data), nullptr, nullptr) {}

  static Item * Next(const T&& data, Item * next) {
    return new Item(move(data), next, nullptr);
  }

  static Item * Child(const T&& data, Item * child) {
    return new Item(move(data), nullptr, child);
  }

  static Item * flatten(Item * const root) {
    if (root->child) {
      Item * const childTail = flatten(root->child);
      childTail->next = root->next;
      if (root->next) {
        root->next->prev = childTail;
      }
      root->next = root->child;
      root->child->prev = root;
      if (childTail->next) {
        return flatten(childTail->next);
      }
      return childTail;
    } else {
      if (root->next) {
        return flatten(root->next);
      }
      return root;
    }
  }

  void levelItems(ItemSet& result) {
    result.insert(data);
    if (next) {
      next->levelItems(result);
    }
  }
};



typedef Item<int> Ii;

int main() {
  auto root = new Ii(5, Ii::Next(33, Ii::Next(17, new Ii(2, new Ii(1),
                                                     new Ii(2, new Ii(7),
                                                            new Ii(12, new Ii(5),
                                                                   Ii::Next(21, new Ii(3))))))),
                     Ii::Next(6, new Ii(25, Ii::Child(6, Ii::Child(9, new Ii(7))), new Ii(8))));
  Ii::flatten(root);
  Ii::ItemSet gotSet;
  root->levelItems(gotSet);
  Ii::ItemSet expectedSet = { 5, 33, 17, 2, 1, 2, 7, 12, 5, 21, 3, 6, 25, 6, 9, 7, 8 };
  assert(gotSet == expectedSet);
  return 0;
}
