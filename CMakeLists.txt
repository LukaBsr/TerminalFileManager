cmake_minimum_required(VERSION 3.10)

# Set the project name
project(fman)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the include directory
include_directories(include)

# Add the executable with additional source files
add_executable(fman src/main.cpp src/core/File.cpp)
