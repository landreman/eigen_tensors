# eigen_tensors

This repository is a demonstration of passing arbitrary-dimension tensors back and forth between python and C++,
using [pybind11](https://pybind11.readthedocs.io).
On the python side, numpy arrays are used. On the C++ side,
[Eigen tensors](https://eigen.tuxfamily.org/dox/unsupported/eigen_tensors.html)
are used.

Note that Eigen is included as a git submodule. Therefore when you clone this repository, use the `--recursive` flag:

    git clone --recursive https://github.com/landreman/eigen_tensors.git

This repository provides a python extension named `eigen_tensors`. To build and install the extension, you can run

    pip install -v .

from the root directory of the repository. (The `-v` flag provides verbose output). Note that CMake is required
to build the extension. After the extension is built and installed, tests can be run using

    python -m unittest

from the repository's root directory.

Some resources I used to get this working:
* [pybind11 documentation for numpy arrays](https://pybind11.readthedocs.io/en/stable/advanced/pycpp/numpy.html)
* [pybind11 issue #1377](https://github.com/pybind/pybind11/issues/1377)
* [Documentation of Eigen Tensors](https://eigen.tuxfamily.org/dox/unsupported/eigen_tensors.html)