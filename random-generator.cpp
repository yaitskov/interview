#include<iostream>
#include<vector>
#include<map>

using namespace std;

template <class T>
struct Input {
  const T a, b, x1, k, m, n;
  Input(T a, T b, T x1, T k, T m, T n) : a(a), b(b), x1(x1), k(k), m(m), n(n) {}

  inline T f(T x) const {
    return (a * x + b) % m;
  }

  inline void printFoundUncached(T x) const {
    for (int i = 0; i <= n; ++i) {
      cout << (x = f(x)) << endl;
    }
  }

  inline void printFoundCached(const vector<T>& series, typename map<T,T>::const_iterator it, T ik) const {
    const int period = (ik - it->second);
    T cachedK = (k - it->second - 1) % period;
    for (T i = 0; i <= n; ++i) {
      cout << series[cachedK++ % period + it->second] << endl;
    }
  }

  inline void printFromKtoKn() const {
    map<T, T> exist;
    vector<T> series;
    T x = x1;
    series.push_back(x);
    T ik = 1;
    exist[x] = ik;
    for (; ik < k; ++ik) {
      x = f(x);
      auto it = exist.find(x);
      if (it != exist.end()) {
        printFoundCached(series, it, ik);
        return;
      } else {
        series.push_back(x);
        exist[x] = ik;
      }
    }
    printFoundUncached(x);
  }
};


int main() {
  int a, b, x, k, m;
  cin >> a >> b >> x >> k >> m;
  Input<int>(a, b, x, k, m, 4).printFromKtoKn();
  return 0;
}
