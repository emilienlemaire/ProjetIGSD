set(FIND_42NGINE_PATHS /usr/local)

find_path(42NGINE_INCLUDE_DIR 42ngine.h
        PATH_SUFFICES include/42nigne
        PATHS ${FIND_42NGINE_PATHS})

find_library(42NGINE_LIBRARY
        NAMES 42ngine
        PATH_SUFFIXES lib
        PATHS ${FIND_42NGINE_PATHS})