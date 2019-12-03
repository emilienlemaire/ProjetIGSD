cmake_minimum_required(VERSION 3.15)
project(ProjetIGSD)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(libs)
include_directories(includes)

add_executable(ProjetIGSD
        src/main.cpp
        includes/debugbreak.h
        includes/utils.h
        includes/constants.h
        libs/Log/Log.h
        libs/Log/Log.cpp
        src/data/Data.cpp
        src/data/Data.h)

set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )

find_path(GLEW_INCLUDE_DIR GL/glew.h)
find_package(GLEW 2.1.0 REQUIRED)
find_package(glfw3 3.3 REQUIRED)
#find_package(OpenCV REQUIRED)
#include_directories(${OpenCV_INCLUDE_DIRS})

target_include_directories(ProjetIGSD PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(ProjetIGSD glfw GLEW::GLEW ${OPENGL_gl_LIBRARY} ${OpenCV_LIBS})