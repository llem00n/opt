// *************************************************************************
// expr.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/26/2023
// *************************************************************************
#ifndef OPT_AST_EXPR_H
#define OPT_AST_EXPR_H

#include <opt/err.h>
#include <opt/token.h>

/**
 * @brief Expression types
 */
typedef enum expr_type {
  EXPR_LVALUE     = 1 << 0,
  EXPR_RVALUE     = 1 << 1,
  EXPR_BINARY     = 1 << 2,
  EXPR_UNARY      = 1 << 3,
  EXPR_INPUT      = 1 << 4,
  EXPR_OUTPUT     = 1 << 5,
  EXPR_NUMBER     = 1 << 6,
  EXPR_VARIABLE   = 1 << 7,
} expr_type_t;

/**
 * @brief Expression node
 */
typedef struct expr {
  expr_type_t type;
  token_t *start_token;
} expr_t;

/**
 * @brief Initialize expression node
 * @param expr Expression node
 * @param type Expression type
 * @param start_token Expression start token
 * @return ERROR_BAD_PARAMETER if expr is NULL, ERROR_OK otherwise
 */
error_t expr_init(expr_t *expr, expr_type_t type, token_t *start_token);

/**
 * @brief Get expression type
 * @param expr Expression node
 * @return Expression type
 */
expr_type_t get_expr_type(const expr_t* expr);

/**
 * @brief Get expression start token
 * @param expr Expression node
 * @return Expression start token
 */
token_t *get_expr_start_token(const expr_t* expr);

#endif //OPT_AST_EXPR_H