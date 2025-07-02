# arv234/CMakeLists.txt
add_library(arv234 STATIC
    arv234.c
)

target_include_directories(arv234 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
