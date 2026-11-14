cmake_minimum_required(VERSION 3.5)

project(tema5 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Demo: copierea unui unique_ptr (Item 13) și a unui LockNecopiabil (Item 14)
#       => erori de compilare
option(DEMO_COPIERE_INTERZISA "Incearca sa copieze obiecte necopiabile" OFF)

set(myfiles
    include/investitie.h
    include/mutex.h
    include/lock.h
    include/text.h
    src/investitie.cpp
    src/mutex.cpp
    src/lock.cpp
    src/text.cpp
    src/main.cpp)

add_executable(${PROJECT_NAME} ${myfiles})

target_include_directories(${PROJECT_NAME} PRIVATE include)

if(DEMO_COPIERE_INTERZISA)
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEMO_COPIERE_INTERZISA)
endif()