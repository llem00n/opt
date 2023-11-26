// *************************************************************************
// ast.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/03/2023
// *************************************************************************

#ifndef SYNTAX_TREE_AST_H
#define SYNTAX_TREE_AST_H

#include <opt/token.h>
#include <stdint.h>

/**
 * @brief Statement types
 */
typedef enum stmt_type {
  STMT_IF,
  STMT_FOR,
  STMT_EXPR,
  STMT_BLOCK,
  STMT_GOTO,
} stmt_type_t;

/**
 * @brief Expression types
 */
typedef enum expr_type {
  EXPR_LVALUE,
  EXPR_RVALUE,
  EXPR_ASSIGNMENT,
  EXPR_LOGICAL,
  EXPR_EQUALITY,
  EXPR_COMPARISON,
  EXPR_TERM,
  EXPR_FACTOR,
  EXPR_UNARY,
  EXPR_PRIMARY,
} expr_type_t;

typedef struct expr {
  expr_type_t type;
} expr_t;

typedef struct expr_number {
  expr_type_t type;
  int16_t value;
} expr_number_t;

typedef struct expr_unary {
  expr_type_t type;
  token_t *op;
  expr_t *expr;
} expr_unary_t;

typedef struct expr_binary {
  expr_type_t type;
  token_t *op;
  expr_t *left;
  expr_t *right;
} expr_binary_t;

typedef struct expr_variable {
  expr_type_t type;
  char *name;
} expr_variable_t;

typedef struct stmt {
  stmt_type_t type;
} stmt_t;

typedef struct stmt_if {
  stmt_type_t type;
  expr_t *cond;
  stmt_t *goto;
} stmt_if_t;

typedef struct stmt_for {
  stmt_type_t type;
  expr_t *init;
  expr_t *to;
} stmt_for_t;

typedef struct stmt_goto {
  stmt_type_t type;
  char *label;
} stmt_goto_t;

#endif //SYNTAX_TREE_AST_H
