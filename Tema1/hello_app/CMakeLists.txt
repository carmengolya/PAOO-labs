# =============================================================================
#  Project 2: hello_app
#  Executable that uses the static library exported by hello_lib
# =============================================================================

# CMake version
cmake_minimum_required(VERSION 3.5)

# Project name
project(hello_app VERSION 0.3 LANGUAGES CXX)

# Specify the required C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Finding the library:
#  - if the project is built from the top-level CMakeLists.txt (add_subdirectory),
#    the hello::hello_lib target already exists;
#  - otherwise, find it in the folder where hello_lib was installed
#    (use -DCMAKE_PREFIX_PATH=<installation_folder>)
if(NOT TARGET hello::hello_lib)
    find_package(hello_lib 0.3 REQUIRED)
endif()

# Define the executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Link with the static library.
# The target automatically provides the path to hello/hello.h (PUBLIC include dir),
# so include_directories() is no longer needed.
target_link_libraries(${PROJECT_NAME} PRIVATE hello::hello_lib)
