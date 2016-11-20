#include<map>
#include<iostream>
#include<string>

using namespace std;

template<class K, class V> class Entry {
public:
  Entry* next;
  Entry* prev;
  K key;
  V* value;
  Entry(Entry* next, Entry* prev, const K& key, V* value)
    : next(next), prev(prev), key(key), value(value) {}

  ~Entry() {
    if (next) {
      next->prev = prev;
    }
    if (prev) {
      prev->next = next;
    }
    prev = next = nullptr;
    if (value) {
      value = nullptr;
      delete value;
    }
  }
};

template<class K, class T> class Cache {
public:
  const unsigned int maxSize;
  Entry<K, T>* head;
  Entry<K, T>* tail;
  map<K, Entry<K, T>*> dictionary;
  Cache(unsigned int maxSize) : maxSize(maxSize),
                                head(nullptr),
                                tail(nullptr) {}
  T* get(const K& key) {
    auto iter = dictionary.find(key);
    if (dictionary.end() == iter) {
      return nullptr;
    }
    auto entry = iter->second;
    if (entry->prev) {
      entry->prev->next = entry->next;
      if (!entry->next) {
        tail = entry->prev;
        tail->next = nullptr;
      } else {
        entry->next->prev = entry->prev;
      }
      entry->prev = nullptr;
      entry->next = head;
      head->prev = entry;
      head = entry;
    }
    return entry->value;
  }

  void set(const K& key, T* value) {
    if (!maxSize) {
      delete value;
      return;
    }
    auto entry = new Entry<K, T>(head, nullptr, key, value);
    if (head) {
      head->prev = entry;
    }
    head = entry;
    if (!tail) {
      tail = entry;
    } else if (maxSize <= dictionary.size()) {
      auto iter = dictionary.find(tail->key);
      dictionary.erase(iter);
      tail = tail->prev;
      delete tail->next;
    }
    dictionary[key] = entry;
  }
};

int main(int argc, char** argv) {
  int commands;
  unsigned int cacheSize;
  string command, key, value;
  cin >> commands >> cacheSize;
  Cache<string, string> cache(cacheSize);
  for (auto i = 0; i < commands; ++i) {
    cin >> command >> key;
    if (command == "get") {
      auto gotValue = cache.get(key);
      cout << key << ":";
      if (gotValue) {
        cout << *gotValue << endl;
      } else {
        cout << endl;
      }
    } else if (command == "set") {
      cin >> value;
      cache.set(key, new string(value));
    } else {
      cerr << "command [" << command << "] is not supported" << endl;
      return -1;
    }
  }
}
