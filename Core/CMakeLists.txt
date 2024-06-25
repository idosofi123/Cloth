cmake_minimum_required(VERSION 3.16)

project(ClothCore LANGUAGES CXX)

set(SOURCE_FILE_LIST
"src/Simulation.cpp"
"src/Stick.cpp"
"src/Point.cpp"
)

add_library(ClothCore ${SOURCE_FILE_LIST})

target_include_directories(ClothCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Set C++ dialect version
target_compile_features(ClothCore PRIVATE cxx_std_20)