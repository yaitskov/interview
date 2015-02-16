#include<cstring>
#include<cassert>
#include<iostream>
#include<algorithm>

using namespace std;

void flip(int pixels[][3], int size) {
  for (int row = 0; row < size; ++row) {
    int lcol = 0;
    int rcol = size - 1;
    while (lcol < rcol) {
      swap(pixels[row][lcol++], pixels[row][rcol--]);
    }
  }
}

void transpose(int pixels[][3], int size) {
  for (int i = 0; i < size; ++i) {
    for (int j = i + 1; j < size; ++j) {
      swap(pixels[i][j], pixels[j][i]);
    }
  }
}

void print(int pixels[][3], int size) {
  for (int row = 0; row < size; ++row) {
    for (int col = 0; col < size; ++col) {
      cout << " " << pixels[row][col];
    }
    cout << endl;
  }
}

int main() {
  int pixels[][3] = {
    {1, 1, 1},
    {2, 2, 2},
    {3, 3, 3},
  };
  cout << "Before ---------------------------------" << endl;
  print(pixels, 3);
  transpose(pixels, 3);
  flip(pixels, 3);
  cout << "After ---------------------------------" << endl;
  print(pixels, 3);
  return 0;
}
