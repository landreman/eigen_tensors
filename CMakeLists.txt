# Versions >= 3.9 have improved support for MPI: https://cliutils.gitlab.io/modern-cmake/chapters/packages/MPI.html
# The command add_compile_definitions, used in this file, was new in CMake version 3.12.
cmake_minimum_required(VERSION 3.12)

# Comment out the next line when speed is needed
set(CMAKE_BUILD_TYPE Debug)
#add_definitions(-O2)

#include(cmake/knownHosts.cmake)

project(eigen_tensors LANGUAGES CXX)

# Tell "make" to print out the commands used for compiling and linking:
set(CMAKE_VERBOSE_MAKEFILE on)

set(SOURCE_DIR "src")

# Get a list of all sources:
file(GLOB SOURCES "${SOURCE_DIR}/*.cpp")
message("Sources: ${SOURCES}")

# Locate pybind11
execute_process(COMMAND python -m pybind11 --cmakedir
                OUTPUT_VARIABLE pybind11_DIR
                OUTPUT_STRIP_TRAILING_WHITESPACE)
message("Result of python -m pybind11 --cmakedir: ${pybind11_DIR}")

find_package(pybind11 REQUIRED PATHS pybind11_DIR)
pybind11_add_module(eigen_tensors ${SOURCES})

include_directories(externalPackages/eigen)
