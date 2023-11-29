// *************************************************************************
// parser.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/03/2023
// *************************************************************************

#ifndef PARSER_PARSER_H
#define PARSER_PARSER_H

#include <opt/token.h>
#include <opt/err.h>
#include <opt/ast/utils.h>
#include <stddef.h>

typedef struct parser_ctx {
  token_t *token_cursor;
  int8_t *ast_start;
  int8_t *ast_cursor;
  size_t max_ast_size;
  root_t *root;
  error_t error;
} parser_ctx_t;

/**
 * @brief Initialize parser context
 * @param ctx Parser context
 * @param start_token Start token
 * @param ast AST bytes
 * @param max_ast_size Max AST size
 * @return ERROR_OK if success,
 *         ERROR_BAD_PARAMETER if ctx, start_token or ast is NULL,
*/
error_t parser_ctx_init(parser_ctx_t *ctx, token_t *start_token, int8_t *ast, size_t max_ast_size);

/**
 * @brief Parse program
 * @param ctx Parser context
 * @return ERROR_OK if success,
 *         ERROR_PARSE_UNEXPECTED_TOKEN if unexpected token,
 *         ERORR_AST_TOO_BIG if AST is too big
*/
error_t parse(parser_ctx_t *ctx);

/**
 * @brief Get root node
 * @param ctx Parser context
 * @return Root node
*/
root_t *get_parser_ctx_root(const parser_ctx_t* ctx);

#endif //PARSER_PARSER_H
