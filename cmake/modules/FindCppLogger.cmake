set(FIND_CPPLOGGER_PATHS /usr/local)

find_path(CPPLOGGER_INCLUDE_DIR Log.h
        PATH_SUFFICES include
        PATHS ${FIND_CPPLOGGER_PATHS})

find_library(CPPLOGGER_LIBRARY
        NAMES CppLogger
        PATH_SUFFIXES lib
        PATHS ${FIND_CPPLOGGER_PATHS})