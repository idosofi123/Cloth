cmake_minimum_required(VERSION 3.16)
project(Cloth LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(Core)
add_subdirectory(App)