cmake_minimum_required(VERSION 3.16)
project(Raytracing CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(raytracer_core
    src/math/vector.cpp
    src/colour/colour.cpp
    src/geometry/ray.cpp
    src/geometry/sphere.cpp
    src/render/camera.cpp
    src/render/trace.cpp
)
target_include_directories(raytracer_core PUBLIC ${CMAKE_SOURCE_DIR}/src)

add_executable(raytracer src/main.cpp)
target_link_libraries(raytracer PRIVATE raytracer_core)

enable_testing()
add_subdirectory(tests)
