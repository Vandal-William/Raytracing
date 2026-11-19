cmake_minimum_required(VERSION 3.16)
project(Raytracing CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# LodePNG writes our PNG files. It has no CMake project of its own, so we build it here.
include(FetchContent)
FetchContent_Declare(
  lodepng
  GIT_REPOSITORY https://github.com/lvandeve/lodepng.git
  GIT_TAG        7b2893e35891c0c85bee5595caafaf3c2044b409
)
FetchContent_MakeAvailable(lodepng)
add_library(lodepng STATIC ${lodepng_SOURCE_DIR}/lodepng.cpp)
target_include_directories(lodepng PUBLIC ${lodepng_SOURCE_DIR})

add_library(raytracer_core
    src/math/vector.cpp
    src/colour/colour.cpp
    src/material/material.cpp
    src/geometry/ray.cpp
    src/geometry/sphere.cpp
    src/geometry/plane.cpp
    src/scene/scene.cpp
    src/render/camera.cpp
    src/render/trace.cpp
    src/image/image.cpp
    src/output/png_saver.cpp
)
target_include_directories(raytracer_core PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(raytracer_core PRIVATE lodepng)

add_executable(raytracer src/main.cpp)
target_link_libraries(raytracer PRIVATE raytracer_core)

enable_testing()
add_subdirectory(tests)
