# =============================================================================
#  Proiectul 2: hello_app
#  Executabil care folosește biblioteca statică exportată de hello_lib
# =============================================================================

# CMake version
cmake_minimum_required(VERSION 3.5)

# Project name
project(hello_app VERSION 0.3 LANGUAGES CXX)

# Specify the required C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Găsirea bibliotecii:
#  - dacă proiectul e construit din CMakeLists.txt-ul de top (add_subdirectory),
#    target-ul hello::hello_lib există deja;
#  - altfel îl căutăm în folderul unde a fost instalat hello_lib
#    (se dă cu -DCMAKE_PREFIX_PATH=<folder_instalare>)
if(NOT TARGET hello::hello_lib)
    find_package(hello_lib 0.3 REQUIRED)
endif()

# Define the executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Link cu biblioteca statică.
# Target-ul aduce automat și calea către hello/hello.h (PUBLIC include dir),
# deci nu mai e nevoie de include_directories().
target_link_libraries(${PROJECT_NAME} PRIVATE hello::hello_lib)
