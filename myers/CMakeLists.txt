

add_library(myers
        src/diff.cpp
        include/myers/utils.h
        include/myers/interfaces.h
        include/myers/internal_utils.h
        src/myers_linear.cpp
        include/myers/diff_linear.h
        include/myers/common.h
)

target_include_directories(myers
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
