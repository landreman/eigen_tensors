cmake_minimum_required(VERSION 3.12)

# Comment out the next line when speed is needed
set(CMAKE_BUILD_TYPE Debug)

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
