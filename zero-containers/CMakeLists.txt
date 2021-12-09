project(zero-containers)
cmake_minimum_required(VERSION 3.8)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

add_compile_options(
  -Wall
  -Wextra
  -Werror
  -Wnull-dereference
  -Wold-style-cast
  -Wdouble-promotion
  -Wshadow)

include_directories(include)
add_executable(zero-containers main.cpp)
