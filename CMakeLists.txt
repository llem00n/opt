cmake_minimum_required(VERSION 3.26)
project(opt C)

set(CMAKE_C_STANDARD 17)

add_executable(opt src/main.c
        include/opt/ast.h
        include/opt/err.h
        include/opt/files.h
        include/opt/lexer/char_types.h
        include/opt/lexer/lexer.h
        include/opt/lexer/table.h
        include/opt/lexer/terminating_states.h
        include/opt/lexer/utils.h
        include/opt/output/tokens.h
        include/opt/output/utils/token_type_str.h
        include/opt/parser/parser.h
        include/opt/token.h

        src/ast.c
        src/files.c
        src/lexer/lexer.c
        src/lexer/lexer_table.c
        src/lexer/utils/char_utils.c
        src/lexer/utils/state_utils.c
        src/lexer/utils/token_utils.c
        src/output/tokens.c
        src/output/utils/token_type_str.c
        src/parser/parser.c
)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
target_include_directories(opt PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

