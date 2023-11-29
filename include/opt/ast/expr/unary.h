// *************************************************************************
// unary.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/27/2023
// *************************************************************************

#ifndef OPT_AST_EXPR_UNARY_H
#define OPT_AST_EXPR_UNARY_H

#include <opt/ast/expr.h>

/**
 * @brief Unary expression type
 */
typedef enum expr_unary_type {
  EXPR_UNARY_TYPE_MINUS,
  EXPR_UNARY_TYPE_NOT,
} expr_unary_type_t;

/**
 * @brief Unary expression node
 */
typedef struct expr_unary {
  expr_t base;
  expr_unary_type_t type;
  expr_t *expr;
} expr_unary_t;

/**
 * @brief Initialize unary expression node
 * @param expr_unary Unary expression node
 * @param type Unary expression type
 * @param expr Unary expression node
 * @param start_token Unary expression start token
 * @return ERROR_BAD_PARAMETER if expr_unary, ERROR_OK otherwise
 */
error_t expr_unary_init(expr_unary_t *expr_unary, expr_unary_type_t type, expr_t *expr, token_t *start_token);

/**
 * @brief Get unary expression type
 * @param expr_unary Unary expression node
 * @return Unary expression type
 */
expr_unary_type_t get_expr_unary_type(const expr_unary_t *expr_unary);

/**
 * @brief Get unary expression node
 * @param expr_unary Unary expression node
 * @return Unary expression node
 */
expr_t *get_expr_unary_expr(const expr_unary_t *expr_unary);

#endif //OPT_AST_EXPR_UNARY_H