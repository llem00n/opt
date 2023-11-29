// *************************************************************************
// if.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/27/2023
// *************************************************************************

#ifndef OPT_AST_STMT_IF_H
#define OPT_AST_STMT_IF_H

#include <opt/ast/stmt.h>
#include <opt/ast/expr.h>
#include <opt/ast/stmt/goto.h>

/**
 * @brief If statement node
 */
typedef struct stmt_if {
  stmt_t base;
  expr_t *cond_expr;
  stmt_goto_t *goto_stmt;
} stmt_if_t;

/**
 * @brief Initialize if statement node
 * @param stmt_if If statement node
 * @param cond_expr Condition expression node
 * @param goto_stmt Goto statement node
 * @param start_token If statement start token
 * @return ERROR_BAD_PARAMETER if stmt_if, cond_expr, goto_stmt or start_token is NULL, ERROR_OK otherwise
 */
error_t stmt_if_init(stmt_if_t *stmt_if, expr_t *cond_expr, stmt_goto_t *goto_stmt, token_t *start_token);

/**
 * @brief Get if statement condition expression node
 * @param stmt_if If statement node
 * @return Condition expression node
 */
expr_t *get_stmt_if_cond_expr(const stmt_if_t *stmt_if);

/**
 * @brief Get if statement goto statement node
 * @param stmt_if If statement node
 * @return Goto statement node
 */
stmt_goto_t *get_stmt_if_goto_stmt(const stmt_if_t *stmt_if);

#endif //OPT_AST_STMT_IF_H