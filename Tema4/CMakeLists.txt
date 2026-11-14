cmake_minimum_required(VERSION 3.5)

project(tema VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Demo Item 10: operator= care returnează void -> a = b = c nu compilează
option(DEMO_ITEM10_VOID "Item 10: operator= returneaza void" OFF)
# Demo Item 11: dezactivează detectorul și pornește AddressSanitizer
option(DEMO_ASAN "Item 11: arata use-after-free cu AddressSanitizer" OFF)

set(myfiles
    include/punct.h
    include/imagine.h
    include/fereastra.h
    include/client.h
    src/punct.cpp
    src/imagine.cpp
    src/fereastra.cpp
    src/client.cpp
    src/main.cpp)

add_executable(${PROJECT_NAME} ${myfiles})

target_include_directories(${PROJECT_NAME} PRIVATE include)

if(DEMO_ITEM10_VOID)
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEMO_ITEM10_VOID)
endif()

if(DEMO_ASAN)
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEMO_ASAN)
    target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address -g)
    target_link_libraries(${PROJECT_NAME} PRIVATE -fsanitize=address)
endif()