add_library(benchmark STATIC
    experimentos.c
)
target_include_directories(benchmark PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
