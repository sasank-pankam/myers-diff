

add_library(myers_core
        src/quadratic_diff.cpp
        include/myers/internal_utils.h
        src/myers_linear.cpp
        include/myers/linear_diff.h
        include/myers/types.h
        include/myers/differ.h
        include/myers/quadratic_diff.h
)

target_include_directories(myers_core
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
