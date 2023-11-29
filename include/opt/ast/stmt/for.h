// *************************************************************************
// for.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/27/2023
// *************************************************************************

#ifndef OPT_AST_STMT_FOR_H
#define OPT_AST_STMT_FOR_H

#include <opt/ast/stmt.h>
#include <opt/ast/expr.h>
#include <opt/token.h>
#include <opt/ast/stmt/block.h>

/**
 * @brief For statement node
 */
typedef struct stmt_for {
  stmt_t base;
  char *variable;
  expr_t *init_expr;
  expr_t *to_expr;
  stmt_block_t *body_stmt;
} stmt_for_t;

/**
 * @brief Initialize for statement node
 * @param stmt_for For statement node
 * @param variable For statement variable
 * @param init_expr For statement init expression
 * @param to_expr For statement to expression
 * @param body_stmt For statement body statement
 * @param start_token For statement start token
 * @return ERROR_BAD_PARAMETER if stmt_for, variable, init_expr, to_expr, body_stmt or start_token is NULL, ERROR_OK otherwise
 */
error_t stmt_for_init(stmt_for_t *stmt_for, char *variable, expr_t *init_expr, expr_t *to_expr, stmt_block_t *body_stmt, token_t *start_token);

/**
 * @brief Get for statement variable
 * @param stmt_for For statement node
 * @return For statement variable
 */
char *get_stmt_for_variable(const stmt_for_t *stmt_for);

/**
 * @brief Get for statement init expression
 * @param stmt_for For statement node
 * @return For statement init expression
 */
expr_t *get_stmt_for_init_expr(const stmt_for_t *stmt_for);

/**
 * @brief Get for statement to expression
 * @param stmt_for For statement node
 * @return For statement to expression
 */
expr_t *get_stmt_for_to_expr(const stmt_for_t *stmt_for);

/**
 * @brief Get for statement body statement
 * @param stmt_for For statement node
 * @return For statement body statement
 */
stmt_block_t *get_stmt_for_body_stmt(const stmt_for_t *stmt_for);

#endif //OPT_AST_STMT_FOR_H