#include<string>
#include<algorithm>
#include<cassert>

bool isAnagram(const std::string& a, const std::string& b) {
  auto ac = a;
  auto bc = b;
  std::sort(ac.begin(), ac.end());
  std::sort(bc.begin(), bc.end());
  return ac == bc;
}

int main() {
  assert(isAnagram("", ""));
  assert(isAnagram("a", "a"));
  assert(isAnagram("ab", "ba"));
  assert(isAnagram("skin", "snik"));
  assert(!isAnagram("skan", "snik"));
  return 0;
}
