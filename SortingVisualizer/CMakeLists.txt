cmake_minimum_required(VERSION 3.16)
project(SortingVisualizer CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Where raylib was installed manually
set(RAYLIB_DIR "C:/Users/alexa/raylib" CACHE PATH "Root of the raylib install")

add_library(raylib STATIC IMPORTED)
set_target_properties(raylib PROPERTIES
    IMPORTED_LOCATION "${RAYLIB_DIR}/lib/libraylib.a"
    INTERFACE_INCLUDE_DIRECTORIES "${RAYLIB_DIR}/include"
)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE raylib opengl32 gdi32 winmm)

target_compile_options(main PRIVATE -Wall -Wextra)