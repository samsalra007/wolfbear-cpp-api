# Propiedades del proyecto
cmake_minimum_required(VERSION 3.15)
project(wolfbear_cpp_api)

set(CMAKE_CXX_STANDARD 17)

# Ruta de headers
include_directories(include)

# Archivos fuente
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Ejecutable principal
add_executable(wolfbear main.cpp ${SOURCES})