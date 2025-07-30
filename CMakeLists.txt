cmake_minimum_required(VERSION 3.16)
project(fman LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable compile commands export
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable colored diagnostic output for Clang or GCC
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
    src/ui/views/ExplorerView.cpp
    src/ui/views/FileInfoView.cpp
    src/ui/views/SidebarView.cpp
    src/ui/views/FileActionHandler.cpp
)

# Include directories
set(INCLUDE_DIRS
    include
)

# Add executable
add_executable(fman ${SOURCES})

# Include directories for the target
target_include_directories(fman PRIVATE ${INCLUDE_DIRS})

# Find and link Curses library
find_package(Curses REQUIRED)
target_link_libraries(fman PRIVATE ${CURSES_LIBRARIES})

# Add compile definitions for Curses if needed
if(CURSES_USE_NCURSES)
    target_compile_definitions(fman PRIVATE USE_NCURSES)
endif()

# Group source files in IDEs
source_group(TREE ${CMAKE_SOURCE_DIR}/src PREFIX "Source Files" FILES ${SOURCES})
source_group(TREE ${CMAKE_SOURCE_DIR}/include PREFIX "Header Files" FILES ${INCLUDE_DIRS})
