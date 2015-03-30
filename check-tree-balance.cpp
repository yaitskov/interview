#include<cassert>
#include<algorithm>

using namespace std;

struct Balance {
  const unsigned int min : 16;
  const unsigned int max : 16;
  Balance(unsigned int min = 0, unsigned int max = 0) : min(min), max(max) {}
  bool isBalanced() const {
    return max - min < 2;
  }
  Balance merge(const Balance& o) const {
    return Balance(std::min(min, o.min) + 1, std::max(max, o.max) + 1);
  }
};

class Tree {
  const Tree* const left;
  const Tree* const right;
  static Balance branch(const Tree* node) {
    if (node) {
      return node->balance();
    }
    return Balance();
  }
public:
  Tree(Tree* left = nullptr, Tree* right = nullptr) : left(left), right(right) {}
  ~Tree() {
    if (left)   delete left;
    if (right)  delete right;
  }
  Balance balance() const {
    const auto lb = branch(left);
    if (!lb.isBalanced()) {
      return lb;
    }
    const auto rb = branch(right);
    if (!rb.isBalanced()) {
      return rb;
    }
    return lb.merge(rb);
  }
};

int main() {
  assert(Tree().balance().isBalanced());
  assert(Tree(new Tree()).balance().isBalanced());
  assert(Tree(new Tree(), new Tree()).balance().isBalanced());
  assert(Tree(new Tree(new Tree()), new Tree()).balance().isBalanced());
  assert(!Tree(new Tree(new Tree())).balance().isBalanced());
  assert(!Tree(new Tree(new Tree()), new Tree(new Tree(new Tree()))).balance().isBalanced());
  return 0;
}
