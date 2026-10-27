# =============================================================================
#  Optional solution: build both projects with a single command.
#  Each project has its own CMakeLists.txt and can also be built separately.
# =============================================================================
cmake_minimum_required(VERSION 3.5)

project(hello_solution)

add_subdirectory(hello_lib)   # project 1 -> static library
add_subdirectory(hello_app)   # project 2 -> executable that uses it
