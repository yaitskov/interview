#include<cstring>
#include<cassert>
#include<iostream>
#include<algorithm>

using namespace std;

template <typename Item>
struct Image {
  Item* const pixels;
  const int   size;

  Image(int size) : pixels(new Item[size * size]), size(size) {}
  ~Image() { delete[] pixels; }

  Image& setRow(const Item* rowData, int rowNumber) {
    for (int col = 0; col < size; ++col) {
      at(rowNumber, col) = rowData[col];
    }
    return *this;
  }

  Item& at(int row, int col) {
    return pixels[row * size + col];
  }

  void flip() {
    for (int row = 0; row < size; ++row) {
      int lcol = 0;
      int rcol = size - 1;
      while (lcol < rcol) {
        swap(at(row, lcol++), at(row,rcol--));
      }
    }
  }

  void transpose() {
    for (int i = 0; i < size; ++i) {
      for (int j = i + 1; j < size; ++j) {
        swap(at(i, j), at(j, i));
      }
    }
  }

  void print() {
    for (int row = 0; row < size; ++row) {
      for (int col = 0; col < size; ++col) {
        cout << " " << at(row, col);
      }
      cout << endl;
    }
  }
};

int main() {
  Image<int> img(3);
  img.setRow((const int[]) {1, 1, 1}, 0)
    .setRow((const int[]) {2, 2, 2}, 1)
    .setRow((const int[]) {3, 3, 3}, 2);
  cout << "Before ---------------------------------" << endl;
  img.print();
  img.transpose();
  img.flip();
  cout << "After ---------------------------------" << endl;
  img.print();
  return 0;
}
