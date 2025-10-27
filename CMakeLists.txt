cmake_minimum_required(VERSION 4.0)
project(myers_diff)

set(CMAKE_CXX_STANDARD 23)


add_subdirectory(myers)

add_executable(myapp apps/main.cpp)
target_link_libraries(myapp  PRIVATE myers)
