// *************************************************************************
// assign.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/27/2023
// *************************************************************************

#ifndef OPT_AST_EXPR_ASSIGN_H
#define OPT_AST_EXPR_ASSIGN_H

#include <opt/ast/expr.h>
#include <opt/ast/expr/binary.h>

/**
 * @brief Assignment expression node
 */
typedef struct expr_assign {
  expr_binary_t base;
} expr_assign_t;

/**
 * @brief Initialize assignment expression node
 * @param expr_assign Assignment expression node
 * @param left Left expression node
 * @param right Right expression node
 * @param start_token Assignment expression start token
 * @return ERROR_BAD_PARAMETER if expr_assign, ERROR_OK otherwise
 */
error_t expr_assign_init(expr_assign_t *expr_assign, expr_t *left, expr_t *right, token_t *start_token);

#endif //OPT_AST_EXPR_ASSIGN_H