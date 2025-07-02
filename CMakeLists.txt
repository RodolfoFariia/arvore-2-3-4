cmake_minimum_required(VERSION 3.10)
project(Trabalho02 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall")

# adiciona cada subdiretório como biblioteca
add_subdirectory(arv234)
add_subdirectory(arvrb)
add_subdirectory(benchmark)
add_subdirectory(conversao)

# executável principal
add_executable(trabalho02
    main.c
    testes.c
)

# inclui todos os headers
target_include_directories(trabalho02 PRIVATE
    ${PROJECT_SOURCE_DIR}/arv234
    ${PROJECT_SOURCE_DIR}/arvrb
    ${PROJECT_SOURCE_DIR}/benchmark
    ${PROJECT_SOURCE_DIR}/conversao
)

# liga as bibliotecas
target_link_libraries(trabalho02
    arv234
    arvrb
    benchmark
    conversao
)
