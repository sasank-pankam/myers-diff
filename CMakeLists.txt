cmake_minimum_required(VERSION 4.0)
project(myers_diff)

set(CMAKE_CXX_STANDARD 23)


add_subdirectory(myers)

add_executable(test_app apps/main.cpp)
target_link_libraries(test_app  PRIVATE myers)