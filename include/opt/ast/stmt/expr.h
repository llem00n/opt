// *************************************************************************
// expr.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/27/2023
// *************************************************************************

#ifndef OPT_AST_STMT_EXPR_H
#define OPT_AST_STMT_EXPR_H

#include <opt/ast/stmt.h>
#include <opt/ast/expr.h>

/**
 * @brief Expression statement node
 */
typedef struct stmt_expr {
  stmt_t base;
  expr_t *expr;
} stmt_expr_t;

/**
 * @brief Initialize expression statement node
 * @param stmt_expr Expression statement node
 * @param expr Expression node
 * @param start_token Expression statement start token
 * @return ERROR_BAD_PARAMETER if stmt_expr or expr is NULL, EaRROR_OK otherwise
 */
error_t stmt_expr_init(stmt_expr_t *stmt_expr, expr_t *expr, token_t *start_token);

/**
 * @brief Get expression statement expression node
 * @param stmt_expr Expression statement node
 * @return Expression node
 */
expr_t *get_stmt_expr_expr(const stmt_expr_t *stmt_expr);

#endif //OPT_AST_STMT_EXPR_H