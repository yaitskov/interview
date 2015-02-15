#include<cstring>
#include<cassert>

int countChar(const char c, const char* input) {
  auto result = 0;
  while (*input) {
    result += (*input++ == c);
  }
  return result;
}

char* escapeChar(const char c, const char* input, const char* replacement) {
  const auto repLen = strlen(replacement);
  const auto numC = countChar(c, input);
  char* output = new char[numC * repLen + strlen(input) + 1];
  char* outputEnd = output;
  while (*input) {
    if (c == *input) {
      ++input;
      for (auto i = 0; i < repLen; ++i) {
        *outputEnd++ = replacement[i];
      }
    } else {
      *outputEnd++ = *input++;
    }
  }
  *outputEnd++ = 0;
  return output;
}

int main() {
  assert(!strcmp("", escapeChar(' ', "", "%20")));
  assert(!strcmp("hello%20world", escapeChar(' ', "hello world", "%20")));
  assert(!strcmp("hello%20%20%20world", escapeChar(' ', "hello   world", "%20")));
  return 0;
}
