#include<iostream>
#include<map>
using namespace std;

typedef char Payload;
struct Node {
  const Payload payload;
  Node * next;

  Node(char payload) : payload(payload), next(nullptr) {}
};

static Node * readList(istream& in);
static Node * findFirstRepeat(Node * head);

int main() {
  Node * const head = readList(cin);
  Node * const cycle = findFirstRepeat(head);
  if (cycle) {
    cout << cycle->payload << endl;
  } else {
    cout << "no" << endl;
  }
  return 0;
}

static Node * readList(istream& in) {
  map<Payload,Node*> payload2Addr;
  Node * tail = nullptr;
  Node * head = nullptr;
  while (true) {
    Payload payload;
    cin >> payload;
    if (!cin) {
      break;
    } else {
      if (tail) {
        auto iter = payload2Addr.find(payload);
        if (payload2Addr.end() == iter) {
          payload2Addr[payload] = tail = tail->next = new Node(payload);
        } else { // cycle
          tail->next = iter->second;
          break;
        }
      } else {
        payload2Addr[payload] = head = tail = new Node(payload);
      }
    }
  }
  return head;
}

static Node * findFirstRepeat(Node * head) {
  while (true) {
    const auto next = head->next;
    if (next) {
      auto aligned = reinterpret_cast<long>(next);
      if (aligned % 2) {
        return head;
      } else {
        head->next = reinterpret_cast<Node*>(reinterpret_cast<char*>(next) + 1);
        head = next;
      }
    } else {
      return nullptr;
    }
  }
}
