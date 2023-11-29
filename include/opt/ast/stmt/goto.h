// *************************************************************************
// goto.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/27/2023
// *************************************************************************

#ifndef OPT_AST_STMT_GOTO_H
#define OPT_AST_STMT_GOTO_H

#include <opt/ast/stmt.h>
#include <opt/ast/expr.h>

/**
 * @brief Goto statement node
 */
typedef struct stmt_goto {
  stmt_t base;
  char *label;
} stmt_goto_t;

/**
 * @brief Initialize goto statement node
 * @param stmt_goto Goto statement node
 * @param label Goto statement label
 * @param start_token Goto statement start token
 * @return ERROR_BAD_PARAMETER if stmt_goto, label or start_token is NULL, ERROR_OK otherwise
 */
error_t stmt_goto_init(stmt_goto_t *stmt_goto, char *label, token_t *start_token);

/**
 * @brief Get goto statement label
 * @param stmt_goto Goto statement node
 * @return Goto statement label
 */
char *get_stmt_goto_label(const stmt_goto_t *stmt_goto);

#endif //OPT_AST_STMT_GOTO_H