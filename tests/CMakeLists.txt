include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)

add_executable(raytracer_tests
  test_helpers.cpp
  math/test_vector.cpp
  colour/test_colour.cpp
  material/test_material.cpp
  geometry/test_ray.cpp
  geometry/test_sphere.cpp
  geometry/test_plane.cpp
  scene/test_scene.cpp
  render/test_camera.cpp
  render/test_trace.cpp
  image/test_image.cpp
  output/test_png_saver.cpp
)
target_include_directories(raytracer_tests PRIVATE ${CMAKE_SOURCE_DIR}/tests)
target_link_libraries(raytracer_tests PRIVATE raytracer_core lodepng Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/extras")
include(Catch)
catch_discover_tests(raytracer_tests)
