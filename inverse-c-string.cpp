#include<cstring>
#include<cassert>

using namespace std;

static void reverse(char* str) {
  if (!*str) {
    return;
  }
  char* end = str;
  while (*++end);
  while (str < --end) {
    *str ^= *end;
    *end ^= *str;
    *str ^= *end;
    ++str;
  }
}

int main() {
  char buf[100];
  strcpy(buf, "");
  reverse(buf);
  assert(!strcmp("", buf));

  strcpy(buf, "h");
  reverse(buf);
  assert(!strcmp("h", buf));

  strcpy(buf, "hello");
  reverse(buf);
  assert(!strcmp("olleh", buf));

  strcpy(buf, "he");
  reverse(buf);
  assert(!strcmp("eh", buf));
  return 0;
}
