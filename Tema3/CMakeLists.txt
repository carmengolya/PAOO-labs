# =============================================================================
#  Tema 4 - Effective C++, Item 4, 5, 6
# =============================================================================

# CMake version
cmake_minimum_required(VERSION 3.5)

# Project name
project(tema4 VERSION 1.0 LANGUAGES CXX)

# Specify the required C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Opțiuni pentru demonstrații (implicit OFF -> programul compilează și rulează curat)
#   -DDEMO_COPIERE_INTERZISA=ON  -> Item 6: copierea unui obiect necopiabil => eroare de compilare
#   -DDEMO_ATRIBUIRE_REFERINTA=ON -> Item 5: atribuire la o clasă cu membru referință => eroare
option(DEMO_COPIERE_INTERZISA  "Item 6: incearca sa copieze un obiect necopiabil" OFF)
option(DEMO_ATRIBUIRE_REFERINTA "Item 5: incearca operator= pe clasa cu referinta" OFF)

# File list
set(myfiles
    include/nume.h
    include/item4.h
    include/item5.h
    include/item6.h
    src/nume.cpp
    src/item4.cpp
    src/item5.cpp
    src/item6.cpp
    src/main.cpp)

# Define the executable
add_executable(${PROJECT_NAME} ${myfiles})

# Define the search path for header files (#include <... .hpp>)
target_include_directories(${PROJECT_NAME} PRIVATE include)

if(DEMO_COPIERE_INTERZISA)
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEMO_COPIERE_INTERZISA)
endif()
if(DEMO_ATRIBUIRE_REFERINTA)
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEMO_ATRIBUIRE_REFERINTA)
endif()
