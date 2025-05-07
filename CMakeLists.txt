cmake_minimum_required(VERSION 3.16)
project(fman)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable colored diagnostic output if using Clang or GCC
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-Wall -Wextra -pedantic -fdiagnostics-color=always)
endif()

# Sources
file(GLOB_RECURSE SOURCES
    src/*.cpp
)

# Include dirs
include_directories(include)

# Executable
add_executable(fman ${SOURCES})
