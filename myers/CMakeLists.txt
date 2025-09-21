

add_library(myers
        src/diff.cpp
        include/myers/utils.h
)

target_include_directories(myers
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
