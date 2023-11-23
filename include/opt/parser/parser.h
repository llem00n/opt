// *************************************************************************
// parser.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/03/2023
// *************************************************************************

#ifndef PARSER_PARSER_H
#define PARSER_PARSER_H

#include <opt/syntax_tree/expr.h>

stmt_t *parse_stmt(token_t **cursor);
expr_t *parse_expr(token_t **cursor);
expr_t *parse_expr_assignment(token_t **cursor);
expr_t *parse_expr_logical(token_t **cursor);
expr_t *parse_expr_equality(token_t **cursor);
expr_t *parse_expr_comparison(token_t **cursor);
expr_t *parse_expr_term(token_t **cursor);
expr_t *parse_expr_factor(token_t **cursor);
expr_t *parse_expr_unary(token_t **cursor);
expr_t *parse_expr_primary(token_t **cursor);

#endif //PARSER_PARSER_H
