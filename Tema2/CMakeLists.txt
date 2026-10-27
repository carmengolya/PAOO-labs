# =============================================================================
#  Topic 3 - Student: encapsulation, constructors, destructor, copy & move
# =============================================================================

# CMake version
cmake_minimum_required(VERSION 3.5)

# Project name
project(tema3 VERSION 1.0 LANGUAGES CXX)

# Specify the required C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Demonstration options (OFF by default -> the program runs cleanly)
#   -DDEMO_DOUBLE_FREE=ON  -> StudentGresit gets a destructor => the program crashes
#   -DDEMO_EROARE_INIT=ON  -> const is "initialized" in the body => compilation error
option(DEMO_DOUBLE_FREE "Arata double free fara copy constructor" OFF)
option(DEMO_EROARE_INIT "Arata eroarea fara lista de initializare" OFF)

# File list
set(myfiles
    include/student/student.h
    include/student/student_gresit.h
    include/student/heap_contor.h
    src/student.cpp
    src/student_gresit.cpp
    src/heap_contor.cpp
    src/main.cpp)

# Define the executable
add_executable(${PROJECT_NAME} ${myfiles})

# Define the search path for header files (#include <student/student.h>)
target_include_directories(${PROJECT_NAME} PRIVATE include)

if(DEMO_DOUBLE_FREE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEMO_DOUBLE_FREE)
endif()
if(DEMO_EROARE_INIT)
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEMO_EROARE_INIT)
endif()
