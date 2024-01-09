cmake_minimum_required(VERSION 3.26)
project(opt C)

set(CMAKE_C_STANDARD 17)

add_executable(opt src/main.c
        include/opt/ast/ast.h
        include/opt/ast/stmt.h
        include/opt/ast/stmt/block.h
        include/opt/ast/stmt/expr.h
        include/opt/ast/stmt/for.h
        include/opt/ast/stmt/goto.h
        include/opt/ast/stmt/if.h
        include/opt/ast/stmt/label.h
        include/opt/ast/expr.h
        include/opt/ast/expr/assign.h
        include/opt/ast/expr/binary.h
        include/opt/ast/expr/number.h
        include/opt/ast/expr/print.h
        include/opt/ast/expr/scan.h
        include/opt/ast/expr/unary.h
        include/opt/ast/expr/variable.h
        include/opt/ast/utils.h
        include/opt/err.h
        include/opt/files.h
        include/opt/precompile_config.h
        include/opt/lexer/char_types.h
        include/opt/lexer/lexer.h
        include/opt/lexer/table.h
        include/opt/lexer/terminating_states.h
        include/opt/lexer/utils.h
        include/opt/output/tokens.h
        include/opt/output/utils/token_type_str.h
        include/opt/parser/parser.h
        include/opt/parser/__parser_private.h
        include/opt/token.h
        src/exprstmt.c
        src/files.c
        src/lexer/lexer.c
        src/lexer/lexer_table.c
        src/lexer/utils/char_utils.c
        src/lexer/utils/state_utils.c
        src/lexer/utils/token_utils.c
        src/output/tokens.c
        src/output/utils/token_type_str.c
        src/parser.c
        src/err.c
        include/opt/translator/translator.h
        src/translator/translator.c
        include/opt/translator/platforms/win32.h
        include/opt/translator/platforms/win64.h
        src/translator/platforms/win32.c
        include/opt/translator/platforms/gen.h
        include/opt/translator/__translator_private.h
)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
target_include_directories(opt PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

