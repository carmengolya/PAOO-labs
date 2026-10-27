# =============================================================================
#  Proiectul 1: hello_lib
#  Construiește o bibliotecă STATICĂ (libhello_lib.a / hello_lib.lib)
#  și o exportă împreună cu header-ul public inc/hello/hello.h
# =============================================================================

# CMake version (3.5 = minimul acceptat de CMake 4.x)
cmake_minimum_required(VERSION 3.5)

# Project name + version
project(hello_lib VERSION 0.3 LANGUAGES CXX)

# Specify the required C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Lista de fișiere: header public + header privat + sursă
set(myfiles
    inc/hello/hello.h          # header PUBLIC  (se exportă)
    src/hello_config.h         # header PRIVAT  (rămâne în bibliotecă)
    src/hello.cpp)

# Define the STATIC library
add_library(${PROJECT_NAME} STATIC ${myfiles})

# Alias cu namespace -> consumatorul scrie mereu hello::hello_lib,
# indiferent dacă biblioteca vine din add_subdirectory sau din find_package
add_library(hello::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Căile de include:
#   PRIVATE src  -> doar pentru compilarea bibliotecii (hello_config.h)
#   PUBLIC  inc  -> pentru bibliotecă ȘI pentru oricine o folosește
#     BUILD_INTERFACE   = calea din arborele sursă (la build)
#     INSTALL_INTERFACE = calea relativă din folderul de instalare
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
        $<INSTALL_INTERFACE:include>)

# Macro transmis compilatorului (doar pentru sursele bibliotecii)
target_compile_definitions(${PROJECT_NAME}
    PRIVATE HELLO_LIB_VERSION="${PROJECT_VERSION}")

# =============================================================================
#  EXPORT: biblioteca statică + header-ul + fișierele de configurare CMake
#  Rezultatul după "cmake --install":
#     <prefix>/lib/libhello_lib.a
#     <prefix>/include/hello/hello.h
#     <prefix>/lib/cmake/hello_lib/hello_libConfig.cmake  (+ Targets, Version)
# =============================================================================
include(CMakePackageConfigHelpers)

# 1) Biblioteca statică (.a / .lib)
install(TARGETS ${PROJECT_NAME}
        EXPORT  ${PROJECT_NAME}Targets
        ARCHIVE DESTINATION lib)

# 2) Header-ul public (.h)
install(FILES inc/hello/hello.h
        DESTINATION include/hello)

# 3) Fișierul cu target-ul importat hello::hello_lib
install(EXPORT ${PROJECT_NAME}Targets
        FILE        ${PROJECT_NAME}Targets.cmake
        NAMESPACE   hello::
        DESTINATION lib/cmake/${PROJECT_NAME})

# 4) hello_libConfig.cmake + hello_libConfigVersion.cmake -> pentru find_package()
configure_package_config_file(
    cmake/${PROJECT_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION lib/cmake/${PROJECT_NAME})

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    VERSION       ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION lib/cmake/${PROJECT_NAME})
