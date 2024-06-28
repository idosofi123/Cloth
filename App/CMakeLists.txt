cmake_minimum_required(VERSION 3.16)

project(ClothApp LANGUAGES CXX)

set(SOURCE_FILE_LIST 
"src/Main.cpp"
)

add_executable(ClothApp ${SOURCE_FILE_LIST})

# Set C++ dialect version
target_compile_features(ClothApp PRIVATE cxx_std_20)

# Linking core library
target_link_libraries(ClothApp PRIVATE ClothCore)

# Fetching raylib from the official git repository
include(FetchContent)

FetchContent_Declare(raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.0)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples

FetchContent_MakeAvailable(raylib)

# Linking raylib
target_link_libraries(ClothApp PRIVATE raylib)

# Copy assets folder to build
add_custom_command(
    TARGET ClothApp
    POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:ClothApp>/assets
    VERBATIM)

