cmake_minimum_required(VERSION 3.10)

# Project name and version
project(IA-Perceptron VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(perceptron src/main.cpp src/perceptron.cpp)

# Include directories
include_directories(src)
