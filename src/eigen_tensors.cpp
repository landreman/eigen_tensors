#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

namespace py = pybind11;

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

py::array_t<double> make_tensor3() {
  Eigen::Tensor<double, 3> t(2, 3, 4);
  double index = 0.0;
  for (int j = 0; j < t.dimension(0); j++) {
    for (int k = 0; k < t.dimension(1); k++) {
      for (int l = 0; l < t.dimension(2); l++) {
	t(j, k, l) = index;
	index += 0.1;
      }
    }
  }

  // To return the tensor to python, we must convert the Eigen::Tensor to py::array_t:
  return py::array_t<double, py::array::f_style>(t.dimensions(), t.data());
}

PYBIND11_MODULE(eigen_tensors, m) {
  m.def("add", &add, "A function that adds.");
  m.def("increment_vector", &increment_vector, "Add 1 to each element of a vector.");
  m.def("increment_matrix", &increment_matrix, "Add 1 to each element of a matrix.");
  m.def("make_tensor3", &make_tensor3, "Create a rank-3 tensor.");
}
