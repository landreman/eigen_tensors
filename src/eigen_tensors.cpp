// For interfacing ND Eigen Tensors with pybind11, see
// See https://github.com/pybind/pybind11/issues/1377

#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

namespace py = pybind11;

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
  double val = 0.0;
  for (int j = 0; j < t.dimension(0); j++) {
    for (int k = 0; k < t.dimension(1); k++) {
      for (int l = 0; l < t.dimension(2); l++) {
	t(j, k, l) = val;
	val += 0.1;
      }
    }
  }

  // To return the tensor to python, we must convert the Eigen::Tensor to py::array_t:
  return py::array_t<double, py::array::f_style>(t.dimensions(), t.data());
}

// See
// https://pybind11.readthedocs.io/en/stable/advanced/pycpp/numpy.html
// "py::array::f_style | py::array::forcecast" ensures the incoming
// data has the same layout as Eigen's default layout.
py::array_t<double> modify_tensor3(py::array_t<double, py::array::f_style | py::array::forcecast> in_array) {
  
  // Check # of dimensions: see https://pybind11.readthedocs.io/en/stable/advanced/pycpp/numpy.html
  py::buffer_info buf = in_array.request();
  if (buf.ndim != 3) {
    throw std::runtime_error("Number of dimensions must be 3.");
  }
  
  // Without copying, represent the incoming numpy array as an Eigen::Tensor:
  Eigen::TensorMap<Eigen::Tensor<double, 3>> t1(static_cast<double*>(buf.ptr),
						buf.shape[0], buf.shape[1], buf.shape[2]);

  // Make a new tensor of the same shape:
  Eigen::Tensor<double, 3> t2(buf.shape[0], buf.shape[1], buf.shape[2]);
  double val = 0.0;
  for (int j = 0; j < t2.dimension(0); j++) {
    for (int k = 0; k < t2.dimension(1); k++) {
      for (int l = 0; l < t2.dimension(2); l++) {
	t2(j, k, l) = t1(j, k, l) + val;
	val += 0.1;
      }
    }
  }

  // To return the tensor to python, we must convert the Eigen::Tensor to py::array_t:
  return py::array_t<double, py::array::f_style>(t2.dimensions(), t2.data());
}

PYBIND11_MODULE(eigen_tensors, m) {
  m.def("increment_vector", &increment_vector, "Add 1 to each element of a vector.");
  m.def("increment_matrix", &increment_matrix, "Add 1 to each element of a matrix.");
  m.def("make_tensor3", &make_tensor3, "Create a rank-3 tensor.");
  m.def("modify_tensor3", &modify_tensor3, "Add 0.1 * index to each element of a rank-3 tensor.");
}
