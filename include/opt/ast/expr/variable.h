// *************************************************************************
// variable.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/27/2023
// *************************************************************************

#ifndef OPT_AST_EXPR_VARIABLE_H
#define OPT_AST_EXPR_VARIABLE_H

#include <opt/ast/expr.h>

/**
 * @brief Variable expression node
 */
typedef struct expr_variable {
  expr_t base;
  char *name;
} expr_variable_t;

/**
 * @brief Initialize variable expression node
 * @param expr_variable Variable expression node
 * @param name Variable name
 * @param start_token Variable expression start token
 * @return ERROR_BAD_PARAMETER if expr_variable, name or start_token is NULL, ERROR_OK otherwise
 */
error_t expr_variable_init(expr_variable_t *expr_variable, char *name, token_t *start_token);

/**
 * @brief Get variable expression name token
 * @param expr_variable Variable expression node
 * @return Variable expression name
 */
char *get_expr_variable_name(const expr_variable_t *expr_variable);

#endif //OPT_AST_EXPR_VARIABLE_H