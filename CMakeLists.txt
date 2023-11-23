cmake_minimum_required(VERSION 3.26)
project(opt C)

set(CMAKE_C_STANDARD 17)

add_executable(opt src/main.c
        include/opt/lexer/lexer.h
        include/opt/token.h
        include/opt/lexer/table.h
        include/opt/err.h
        src/lexer/lexer.c
        include/opt/lexer/utils.h
        src/lexer/utils/token_utils.c
        src/lexer/utils/state_utils.c
        src/lexer/utils/char_utils.c
        include/opt/lexer/char_types.h
        include/opt/lexer/terminating_states.h
        src/lexer/lexer_table.c
        include/opt/output/tokens.h
        src/output/tokens.c
        include/opt/output/utils/token_type_str.h
        src/output/utils/token_type_str.c
        include/opt/files.h
        include/opt/syntax_tree/expr.h
        include/opt/parser/parser.h
        src/parser/parser.c
        src/files.c
)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
target_include_directories(opt PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

