#include<iostream>
#include<cstring>
#include<cassert>
#include<vector>

using namespace std;

int factorial(int n) {
  return (n < 1) ? 1 : n * factorial(n - 1);
}

template<class T>
vector<vector<T> > permutate(const vector<T>& input) {
  vector<vector<T> > result;
  auto copy = input;
  auto it = copy.begin();
  while (it != copy.end()) {
    T item = *it;
    copy.erase(it);
    vector<vector<T>> subresult = permutate(copy);
    if (subresult.empty()) {
      result.push_back(vector<T>({move(item)}));
      break;
    } else {
      for (auto & variant : subresult) {
        variant.insert(variant.begin(), item);
        result.push_back(move(variant));
      }
      copy.insert(it++, move(item));
    }
  }
  return result;
}

void test(const vector<int>& input) {
  auto result = permutate(input);
  for (auto v : result) {
    for (auto i : v) {
      cout << " " << i;
    }
    cout << endl;
  }
}

int main() {
  vector<int> input;
  int a;
  while (true) {
    cin >> a;
    if (cin) {
      input.push_back(a);
    } else {
      break;
    }
  }
  test(input);
}
