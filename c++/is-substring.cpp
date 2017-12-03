#include<iostream>
#include<cassert>

using namespace std;

bool isSubstring(const char * str, const char * sub) {
  const char * p;
  if (!*sub) {
    return true;
  }
  while (*str && *sub) {
    if (*str == *sub) {
      p = sub;
      do {
        ++str;
        ++p;
      } while (*p == *str && *p);
      if (!*p) {
        return true;
      }
    }
    ++str;
  }
  return false;
}

int main() {
  assert(isSubstring("a", ""));
  assert(isSubstring("a", "a"));
  assert(!isSubstring("a", "aa"));
  assert(isSubstring("aba", "ba"));
  assert(!isSubstring("abcdefg", "bcdeig"));
  assert(!isSubstring("abcdefg", "bcdeig"));
  assert(isSubstring("abcdefg", "bcdefg"));
  assert(isSubstring("abcdefg", "bcdef"));
  assert(!isSubstring("abcdef", "bcdefg"));
  return 0;
}
