// *************************************************************************
// print.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/27/2023
// *************************************************************************

#ifndef OPT_AST_EXPR_PRINT_H
#define OPT_AST_EXPR_PRINT_H

#include <opt/ast/expr.h>

/**
 * @brief Print expression node
 */
typedef struct expr_print {
  expr_t base;
} expr_print_t;

/**
 * @brief Initialize print expression node
 * @param expr_print Print expression node
 * @param start_token Print expression start token
 * @return ERROR_BAD_PARAMETER if expr_print or start_token is NULL, ERROR_OK otherwise
 */
error_t expr_print_init(expr_print_t *expr_print, token_t *start_token);

#endif //OPT_AST_EXPR_PRINT_H