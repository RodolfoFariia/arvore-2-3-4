add_library(arvrb STATIC
    arvRB.c
)
target_include_directories(arvrb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
