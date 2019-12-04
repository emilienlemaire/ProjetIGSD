cmake_minimum_required(VERSION 3.15)
project(ProjetIGSD)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
set(CCACHE_SLOPPINESS pch_defines,time_macros)
include(cotire)

include_directories(src)
include_directories(libs)
include_directories(includes)
include_directories(/usr/local/include)

#add_subdirectory(libs/42ngine)

add_executable(ProjetIGSD
        src/main.cpp
        includes/debugbreak.h
        includes/utils.h
        includes/constants.h
        src/data/Data.cpp
        src/data/Data.h
        src/data/Cylinder.cpp
        src/data/Cylinder.h)


set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )

find_path(GLEW_INCLUDE_DIR GL/glew.h)
find_package(GLEW 2.1.0 REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(CppLogger REQUIRED)
find_package(42ngine REQUIRED)
#find_package(OpenCV REQUIRED)
#include_directories(${OpenCV_INCLUDE_DIRS})


include_directories(${CPPLOGGER_INCLUDE_DIR})
include_directories(${42NGINE_INCLUDE_DIR})

target_include_directories(ProjetIGSD PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(ProjetIGSD glfw GLEW::GLEW ${OPENGL_gl_LIBRARY} ${OpenCV_LIBS} ${CPPLOGGER_LIBRARY} ${42NGINE_LIBRARY})
cotire(ProjetIGSD)