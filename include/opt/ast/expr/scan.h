// *************************************************************************
// scan.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/27/2023
// *************************************************************************

#ifndef OPT_AST_EXPR_SCAN_H
#define OPT_AST_EXPR_SCAN_H

#include <opt/ast/expr.h>

/**
 * @brief Scan expression node
 */
typedef struct expr_scan {
  expr_t base;
} expr_scan_t;

/**
 * @brief Initialize scan expression node
 * @param expr_scan Scan expression node
 * @param start_token Scan expression start token
 * @return ERROR_BAD_PARAMETER if expr_scan or start_token is NULL, ERROR_OK otherwise
 */
error_t expr_scan_init(expr_scan_t *expr_scan, token_t *start_token);

#endif //OPT_AST_EXPR_SCAN_H