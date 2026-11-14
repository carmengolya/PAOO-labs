cmake_minimum_required(VERSION 3.5)

project(tema VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Demo Item 10: operator= care returnează void -> a = b = c nu compilează
option(DEMO_ITEM10_VOID "Item 10: operator= returneaza void" OFF)

set(myfiles
    include/punct.h
    src/punct.cpp
    src/main.cpp)

add_executable(${PROJECT_NAME} ${myfiles})

target_include_directories(${PROJECT_NAME} PRIVATE include)

if(DEMO_ITEM10_VOID)
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEMO_ITEM10_VOID)
endif()