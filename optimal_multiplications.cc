#include "matrix.h"
#include <climits>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


/**
  * Code for finding optimal matrix given in slides:
  * c is a vector containing the number of columns for each of the n matrices
  * c[0] is num of rows in matrix 1
  * min multiplications is left in m[1][n] (which gets printed at the end)
  * m and lastChange are indexed starting at 1, not 0
*/
void optMatrix(const vector<int> &c, matrix<long> &m, matrix<int> &lastChange) {
  int n = c.size() - 1;

  for (int left = 1; left <= n; left++)
    m[left][left] = 0;
  for (int k = 1; k < n; k++) { // k is right - left
    for (int left = 1; left <= n - k; left++) {
      int right = left + k;
      m[left][right] = LONG_MAX;
      for (int i = left; i < right; i++) {
        long thisCost =
            m[left][i] + m[i + 1][right] + c[left - 1] * c[i] * c[right];
        if (thisCost < m[left][right]) {
          m[left][right] = thisCost;
          lastChange[left][right] = i;
        }
      }
    }
  }
  std::cout << "\n" << "Minimum multiplications: "<<  m[1][n] << '\n';
}

/** Prints dimensions of each of the n vectors
  * v should contain the number of columns for each of the n matrices
*/
void printInputMatrices(const vector<int> &v){
  std::cout << "Input Matrices:" << '\n';
  for (size_t i = 1; i < v.size(); i++) {
    std::cout << "Matrix " << i << ": " << v[i-1] << " x " << v[i] << '\n';
  }
}


void readMatrixDimensions(vector<int> &v, const string &matrix_filename){
  string db_line;
  ifstream db_file(matrix_filename);
  if (db_file.is_open()) {
    while (getline(db_file, db_line)) {
      v.push_back(stoi(db_line));
    }
  }
}

void printPrimaryMatrix(matrix<long> &m){
  int a = m.numrows();
  int b = m.numcols();
  for (size_t i = 1; i < a; i++) {
    for (size_t j = 1; j < b; j++) {
      cout << m[i][j] << '\t';
    }
    cout << endl;
  }
}

void printChangeMatrix(matrix<int> &m){
  int a = m.numrows();
  int b = m.numcols();
  vector<int> list;
  std::cout << "\nBest order: (Broken)" << '\n';
  for (size_t i = 1; i < m.numrows(); i++) {
    list.push_back(m[i-1][i]);
  }
  for (size_t i = list.size(); i > 1 ; i--) {
    std::cout << list[i-1] << " then ";
  }
  std::cout << list[0] << '\n';
  cout << endl;
  // for (size_t i = 0; i < m.numrows(); i++) {
  //   for (size_t j = 0; j < m.numcols(); j++) {
  //     cout << m[i][j];
  //   }
  //   cout << endl;
  // }
  // cout << '\n';
}

int main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Something's wrong." << endl;
    return 0;
  }

  const string matrix_filename(argv[1]);

  vector<int> v; // stores number of matrix column

  readMatrixDimensions(v, matrix_filename);
  printInputMatrices(v);

  int n = v.size()-1; // n is number of matrices
  matrix<long> m(n+1, n+1); // create m, used in optMatrix, n+1 since row and column with index 0 aren't used
  matrix<int> lastChange(n+1, n+1); // create matrix to store change order
  optMatrix(v, m, lastChange);
  printChangeMatrix(lastChange);

  // TODO MATRIX ORDER FOR EXTRA CREDIT
  return 0;
}
