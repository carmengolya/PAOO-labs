# =============================================================================
#  Project 1: hello_lib
#  Build a STATIC library (libhello_lib.a / hello_lib.lib)
#  and export it together with the public header inc/hello/hello.h
# =============================================================================

# CMake version (3.5 = minimum supported by CMake 4.x)
cmake_minimum_required(VERSION 3.5)

# Project name + version
project(hello_lib VERSION 0.3 LANGUAGES CXX)

# Specify the required C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# File list: public header + private header + source
set(myfiles
    include/hello/hello.h          # PUBLIC header  (exported)
    src/hello_config.h             # PRIVATE header (kept in the library)
    src/hello.cpp)

# Define the STATIC library
add_library(${PROJECT_NAME} STATIC ${myfiles})

# Namespace alias -> consumers always write hello::hello_lib,
# regardless of whether the library comes from add_subdirectory or find_package
add_library(hello::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Include paths:
#   PRIVATE src  -> only for compiling the library (hello_config.h)
#   PUBLIC  inc  -> for the library AND anyone who uses it
#     BUILD_INTERFACE   = path in the source tree (at build time)
#     INSTALL_INTERFACE = relative path in the installation folder
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
        $<INSTALL_INTERFACE:include>)

# Macro passed to the compiler (only for library sources)
target_compile_definitions(${PROJECT_NAME}
    PRIVATE HELLO_LIB_VERSION="${PROJECT_VERSION}")

# =============================================================================
#  EXPORT: static library + header + CMake configuration files
#  Result after "cmake --install":
#     <prefix>/lib/libhello_lib.a
#     <prefix>/include/hello/hello.h
#     <prefix>/lib/cmake/hello_lib/hello_libConfig.cmake  (+ Targets, Version)
# =============================================================================
include(CMakePackageConfigHelpers)

# 1) Static library (.a / .lib)
install(TARGETS ${PROJECT_NAME}
        EXPORT  ${PROJECT_NAME}Targets
        ARCHIVE DESTINATION lib)

# 2) Public header (.h)
install(FILES include/hello/hello.h
        DESTINATION include/hello)

# 3) File containing the imported hello::hello_lib target
install(EXPORT ${PROJECT_NAME}Targets
        FILE        ${PROJECT_NAME}Targets.cmake
        NAMESPACE   hello::
        DESTINATION lib/cmake/${PROJECT_NAME})

# 4) hello_libConfig.cmake + hello_libConfigVersion.cmake -> for find_package()
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
