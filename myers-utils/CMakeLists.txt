

#add_library(myers_utils
#        include/myers-utils/compressor.h
#        include/myers-utils/file_input.h
#        include/myers-utils/vector_input.h
#        include/myers-utils/formatters/string.h
#)

add_library(myers_utils INTERFACE
        include/myers-utils/input.h)

target_include_directories(myers_utils
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)
