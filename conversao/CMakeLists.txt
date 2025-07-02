add_library(conversao STATIC
    conversao.c
)
target_include_directories(conversao PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
