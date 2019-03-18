cmake_minimum_required(VERSION 3.8)
project(untitled4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Cube.hpp Cube.cpp)

include_directories(${PROJECT_SOURCE_DIR}/GLFW/include)
link_directories(${PROJECT_SOURCE_DIR}/GLFW/lib-mingw)


add_executable(untitled4 ${SOURCE_FILES})
target_link_libraries(untitled4 glfw3 opengl32)