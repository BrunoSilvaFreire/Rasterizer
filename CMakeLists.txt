cmake_minimum_required(VERSION 3.13)
project(Rasterizer)

set(CMAKE_CXX_STANDARD 17)
set(GFLAGS_BUILD_gflags_LIB On CACHE DESC "Hello")
set(GFLAGS_BUILD_STATIC_LIBS On CACHE DESC "We want static linking")
set(GFLAGS_BUILD_SHARED_LIBS Off CACHE DESC "Disable dynamic linking")
add_subdirectory(thirdparty/gflags)

set(PNG_FRAMEWORK Off CACHE DESC "Disable PNG Framework")
set(PNG_TESTS Off CACHE DESC "Disable PNG Tests")
set(PNG_SHARED Off CACHE DESC "Disable dynamic linking")

add_subdirectory(thirdparty/libpng)

add_subdirectory(thirdparty/tinyobjloader)

add_executable(rasterizer src/main.cpp include/texture.h src/texture.cpp)
target_link_libraries(rasterizer gflags png tinyobjloader)
target_include_directories(rasterizer
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)