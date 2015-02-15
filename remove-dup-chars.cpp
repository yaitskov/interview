#include<cstring>
#include<cassert>

void shift(char * s) {
  while (*s) {
    *s = *(s + 1);
    ++s;
  }
}

void eraseChar(char c, char * s) {
  while (*s) {
    if (c == *s) {
      shift(s);
    }
    s++;
  }
}

void dedup(char * s) {
  while (*s) {
    eraseChar(*s, s + 1);
    ++s;
  }
}

void test(const char * expected, const char * input) {
  char * got = new char[strlen(input) + 1];
  strcpy(got, input);
  dedup(got);
  assert(!strcmp(expected, got));
  delete[] got;
}

int main() {
  test("", "");
  test("a", "a");
  test("a", "aa");
  test("ab", "aba");
  test("abc", "abbcca");
  return 0;
}
