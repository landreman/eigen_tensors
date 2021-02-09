#include <Eigen/Core>
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

int add(int j, int k) {
  return j + k;
}

typedef Eigen::ArrayXd Vector;
typedef Eigen::MatrixXd Matrix;

Vector increment_vector(Vector& m1) {
  Vector m2(m1.size());
  for (int j = 0; j < m1.size(); j++) {
      m2(j) = m1(j) + 1.0;
  }
  return m2;
}

Matrix increment_matrix(Matrix& m1) {
  Matrix m2(m1.rows(), m1.rows());
  for (int j = 0; j < m1.cols(); j++) {
    for (int k = 0; k < m2.rows(); k++) {
      m2(k, j) = m1(k, j) + 1.0;
    }
  }
  return m2;
}

namespace py = pybind11;

PYBIND11_MODULE(eigen_tensors, m) {
  m.def("add", &add, "A function that adds.");
  m.def("increment_vector", &increment_vector, "Add 1 to each element of a vector.");
  m.def("increment_matrix", &increment_matrix, "Add 1 to each element of a matrix.");
}
