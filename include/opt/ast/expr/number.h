// *************************************************************************
// number.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/27/2023
// *************************************************************************

#ifndef OPT_AST_EXPR_NUMBER_H
#define OPT_AST_EXPR_NUMBER_H

#include <opt/ast/expr.h>

/**
 * @brief Number expression node
 */
typedef struct expr_number {
  expr_t base;
  int16_t value;
} expr_number_t;

/**
 * @brief Initialize number expression node
 * @param expr_number Number expression node
 * @param value Number value
 * @param start_token Number expression start token
 * @return ERROR_BAD_PARAMETER if expr_number, ERROR_OK otherwise
 */
error_t expr_number_init(expr_number_t *expr_number, int16_t value, token_t *start_token);

/**
 * @brief Get number expression value
 * @param expr_number Number expression node
 * @return Number value
 */
int16_t get_expr_number_value(const expr_number_t *expr_number);

#endif //OPT_AST_EXPR_NUMBER_H