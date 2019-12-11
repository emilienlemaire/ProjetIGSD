cmake_minimum_required(VERSION 3.15)
project(ProjetIGSD)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
set(CCACHE_SLOPPINESS pch_defines,time_macros)
include(cotire)

add_subdirectory(libs/42ngine)

set(INCLUDE_DIRECTORIES src includes libs)

add_executable(ProjetIGSD
        src/main.cpp
        includes/debugbreak.h
        includes/utils.h
        includes/constants.h
        src/data/Data.cpp
        src/data/Data.h
        src/data/Cylinder.cpp
        src/data/Cylinder.h)

find_package(CppLogger REQUIRED)
#find_package(OpenCV REQUIRED)

target_include_directories(ProjetIGSD PUBLIC ${CPPLOGGER_INCLUDE_DIR} ${INCLUDE_DIRECTORIES})
target_link_libraries(ProjetIGSD ${CPPLOGGER_LIBRARY} 42ngine imgui)

add_executable(ProjetIGSDApp MACOSX_BUNDLE
        src/main.cpp
        src/data/Data.cpp
        src/data/Data.h
        src/data/Cylinder.cpp
        src/data/Cylinder.h
        resources/data/rankspts.csv)

set_source_files_properties(
  resources/data/rankspts.csv
  PROPERTIES
  MACOSX_PACKAGE_LOCATION Resources
  )


target_include_directories(ProjetIGSDApp PUBLIC ${CPPLOGGER_INCLUDE_DIR} ${INCLUDE_DIRECTORIES})
target_link_libraries(ProjetIGSDApp ${CPPLOGGER_LIBRARY} 42ngine imgui)
include(CPack)
cotire(ProjetIGSD)