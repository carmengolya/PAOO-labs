# =============================================================================
#  Soluția (opțională): construiește ambele proiecte dintr-o singură comandă.
#  Fiecare proiect are însă CMakeLists.txt propriu și poate fi construit separat.
# =============================================================================
cmake_minimum_required(VERSION 3.5)

project(hello_solution)

add_subdirectory(hello_lib)   # proiectul 1 -> biblioteca statică
add_subdirectory(hello_app)   # proiectul 2 -> executabilul care o folosește
