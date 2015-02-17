#include<iostream>
#include<cstring>
#include<algorithm>
#include<cassert>
#include<vector>
#include<set>

using namespace std;


void zeroRowColumn(vector<vector<int>>& matrix) {
  set<int> zeroRows;
  set<int> zeroCols;
  for (int irow = 0; irow < matrix.size(); ++irow) {
    auto& row = matrix[irow];
    for (int icol = 0; icol < row.size(); ++icol) {
      if (!row[icol]) {
        zeroRows.insert(irow);
        zeroCols.insert(icol);
      }
    }
  }

  for (auto irow : zeroRows) {
    std::fill(matrix[irow].begin(), matrix[irow].end(), 0);
  }
  for (auto& row : matrix) {
    for (auto icol : zeroCols) {
      row[icol] = 0;
    }
  }
}

int main() {
  vector<vector<int>> input;
  input.resize(4);
  input[0] = { 1, 2, 3, 4 };
  input[1] = { 1, 2, 0, 4 };
  input[2] = { 1, 2, 3, 4 };
  input[3] = { 0, 2, 3, 4 };

  auto expected = input;
  expected[0] = { 0, 2, 0, 4 };
  expected[1] = { 0, 0, 0, 0 };
  expected[2] = { 0, 2, 0, 4 };
  expected[3] = { 0, 0, 0, 0 };

  zeroRowColumn(input);

  assert(input == expected);
  return 0;
}
