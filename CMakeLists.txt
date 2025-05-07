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
set(SOURCES
    src/main.cpp
    src/core/File.cpp
    src/core/Directory.cpp
    src/ui/NcursesManager.cpp
    src/ui/NcursesWrapper.cpp
    src/ui/NcursesApp.cpp
)

# Include dirs
include_directories(include)

# Executable
add_executable(fman ${SOURCES})

# Link libraries
find_package(Curses REQUIRED)
if (Curses_FOUND)
    target_link_libraries(fman ${CURSES_LIBRARIES})
else()
    message(FATAL_ERROR "Curses library not found")
endif()
