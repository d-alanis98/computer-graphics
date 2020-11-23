#include "Matrix.hpp"
#include <iostream>

int main(int argc, char **argv) {
  Matrix<double> mat1(4, 4, 1.0);
  Matrix<double> mat2(4, 4, 2.0);

  Matrix<double> mat3 = mat1 * mat2;

  for (int i = 0; i < mat3.getRows(); i++) {
    for (int j=0; j<mat3.getColumns(); j++) {
      std::cout << mat3(i,j) << ", ";
    }
    std::cout << std::endl;
  }

  return 0;
}