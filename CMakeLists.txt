cmake_minimum_required(VERSION 3.15)
project(ProjetIGSD)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
set(CCACHE_SLOPPINESS pch_defines,time_macros)
include(cotire)

set(INCLUDE_DIRECTORIES src includes libs)

add_subdirectory(libs/42ngine)

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
#find_package(OpenCV REQUIRED)

target_include_directories(ProjetIGSD PUBLIC ${CPPLOGGER_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${INCLUDE_DIRECTORIES})
target_link_libraries(ProjetIGSD glfw GLEW::GLEW ${OPENGL_gl_LIBRARY} ${OpenCV_LIBS} ${CPPLOGGER_LIBRARY} 42ngine)
cotire(ProjetIGSD)