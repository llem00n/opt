// *************************************************************************
// binary.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/27/2023
// *************************************************************************

#ifndef OPT_AST_EXPR_BINARY_H
#define OPT_AST_EXPR_BINARY_H

#include <opt/ast/expr.h>

/**
 * @brief Binary expression type
 */
typedef enum expr_binary_type {
  EXPR_BINARY_TYPE_ADD,
  EXPR_BINARY_TYPE_SUB,
  EXPR_BINARY_TYPE_MUL,
  EXPR_BINARY_TYPE_DIV,
  EXPR_BINARY_TYPE_MOD,
  EXPR_BINARY_TYPE_EQ,
  EXPR_BINARY_TYPE_NEQ,
  EXPR_BINARY_TYPE_LT,
  EXPR_BINARY_TYPE_GT,
  EXPR_BINARY_TYPE_AND,
  EXPR_BINARY_TYPE_OR,
  EXPR_BINARY_ASSIGN,
} expr_binary_type_t;

/**
 * @brief Binary expression node
 */
typedef struct expr_binary {
  expr_t base;
  expr_binary_type_t type;
  expr_t *left;
  expr_t *right;
} expr_binary_t;

/**
 * @brief Initialize binary expression node
 * @param expr_binary Binary expression node
 * @param type Binary expression type
 * @param left Left expression node
 * @param right Right expression node
 * @param start_token Binary expression start token
 * @return ERROR_BAD_PARAMETER if expr_binary, left, right or start_token is NULL, ERROR_OK otherwise
 */
error_t expr_binary_init(expr_binary_t *expr_binary, expr_binary_type_t type, expr_t *left, expr_t *right, token_t *start_token);

/**
 * @brief Get binary expression type
 * @param expr_binary Binary expression node
 * @return Binary expression type
 */
expr_binary_type_t get_expr_binary_type(const expr_binary_t* expr_binary);

/**
 * @brief Get binary expression left node
 * @param expr_binary Binary expression node
 * @return Binary expression left node
 */
expr_t *get_expr_binary_left(const expr_binary_t *expr_binary);

/**
 * @brief Get binary expression right node
 * @param expr_binary Binary expression node
 * @return Binary expression right node
 */
expr_t *get_expr_binary_right(const expr_binary_t *expr_binary);

#endif //OPT_AST_EXPR_BINARY_H