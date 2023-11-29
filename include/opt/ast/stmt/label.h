// *************************************************************************
// label.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/27/2023
// *************************************************************************

#ifndef OPT_AST_STMT_LABEL_H
#define OPT_AST_STMT_LABEL_H

#include <opt/ast/stmt.h>
#include <opt/ast/expr.h>

/**
 * @brief Label statement node
 */
typedef struct stmt_label {
  stmt_t base;
  char *name;
} stmt_label_t;

/**
 * @brief Initialize label statement node
 * @param stmt_label Label statement node
 * @param name Label name
 * @param start_token Label statement start token
 * @return ERROR_BAD_PARAMETER if stmt_label, name or start_token is NULL, ERROR_OK otherwise
 */
error_t stmt_label_init(stmt_label_t *stmt_label, char *name, token_t *start_token);

/**
 * @brief Get label statement name
 * @param stmt_label Label statement node
 * @return Label name
 */
const char *get_stmt_label_name(stmt_label_t *stmt_label);

#endif //OPT_AST_STMT_LABEL_H