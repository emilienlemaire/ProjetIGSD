cmake_minimum_required(VERSION 3.15)
project(ProjetIGSD)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
set(CCACHE_SLOPPINESS pch_defines,time_macros)
include(cotire)

add_subdirectory(libs/42ngine)

set(INCLUDE_DIRECTORIES src includes libs /usr/local/Cellar/opencv@2/2.4.13.7_5/include)
set(OPENCV_LIBS /usr/local/Cellar/opencv@2/2.4.13.7_5/lib/libopencv_core.dylib
        /usr/local/Cellar/opencv@2/2.4.13.7_5/lib/libopencv_imgproc.dylib
        /usr/local/Cellar/opencv@2/2.4.13.7_5/lib/libopencv_highgui.dylib)

file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})

add_executable(ProjetIGSD
        src/main.cpp
        includes/debugbreak.h
        includes/utils.h
        includes/constants.h
        src/data/Data.cpp
        src/data/Data.h
        src/data/Cylinder.cpp
        src/data/Cylinder.h)

target_include_directories(ProjetIGSD PUBLIC ${INCLUDE_DIRECTORIES})
target_link_libraries(ProjetIGSD ${OPENCV_LIBS} 42ngine imgui)