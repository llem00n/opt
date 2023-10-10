cmake_minimum_required(VERSION 3.26)
project(opt C)

set(CMAKE_C_STANDARD 17)

add_executable(opt src/main.c
        include/opt/lexer.h
        include/opt/token.h
        include/opt/config/lexer_config.h
        include/opt/err.h
        src/lexer.c
)

target_include_directories(opt PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

