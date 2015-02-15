#include<cassert>

bool isIn(const char c, const char * s) {
  while (*s) {
    if (c == *s++) {
      return true;
    }
  }
  return false;
}

bool isUniq(const char * s) {
  while (*s) {
    if (isIn(*s, s + 1)) {
      return false;
    }
    ++s;
  }
  return true;
}

int main() {
  assert(isUniq(""));
  assert(isUniq("a"));
  assert(isUniq("abc"));
  assert(!isUniq("abbc"));
  assert(!isUniq("abcad"));
}
