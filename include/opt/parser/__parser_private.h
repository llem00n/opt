// *************************************************************************
// __parser_private.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/27/2023
// *************************************************************************

#ifndef OPT_PARSER___PARSER_PRIVATE_H
#define OPT_PARSER___PARSER_PRIVATE_H

#include <opt/parser/parser.h>
#include <opt/ast/ast.h>
#include <opt/err.h>
#include <stdbool.h>

/**
 * @brief Allocate memory for node of size `size` in AST bytes array
 * @param ctx Parser context
 * @param size Size of node
 * @return Pointer to allocated memory if success,
 *         NULL if node is outside of AST bytes array
*/
void *__parser_alloc(parser_ctx_t *ctx, const size_t size);

/**
 * @brief Parse tokens into assignment expression
 * @param ctx Parser context
 * @param expr Assignment or rvalue expression node
 * @return ERROR_OK if success,
 *         ERROR_PARSE_UNEXPECTED_TOKEN if unexpected token,
 *         ERORR_AST_TOO_BIG if AST is too big
*/
error_t __parse_expr_assignment(parser_ctx_t *ctx, expr_t **expr);

/**
 * @brief Parse tokens into logical expression
 * @param ctx Parser context
 * @param binary Binary expression node
 * @return ERROR_OK if success,
 *         ERROR_PARSE_UNEXPECTED_TOKEN if unexpected token,
 *         ERORR_AST_TOO_BIG if AST is too big
*/
error_t __parse_expr_logical(parser_ctx_t *ctx, expr_binary_t **binary);

/**
 * @brief Parse tokens into equality expression
 * @param ctx Parser context
 * @param binary Binary expression node
 * @return ERROR_OK if success,
 *         ERROR_PARSE_UNEXPECTED_TOKEN if unexpected token,
 *         ERORR_AST_TOO_BIG if AST is too big
*/
error_t __parse_expr_equality(parser_ctx_t *ctx, expr_binary_t **binary);

/**
 * @brief Parse tokens into comparison expression
 * @param ctx Parser context
 * @param binary Binary expression node
 * @return ERROR_OK if success,
 *         ERROR_PARSE_UNEXPECTED_TOKEN if unexpected token,
 *         ERORR_AST_TOO_BIG if AST is too big
*/
error_t __parse_expr_comparison(parser_ctx_t *ctx, expr_binary_t **binary);

/**
 * @brief Parse tokens into term expression
 * @param ctx Parser context
 * @param binary Binary expression node
 * @return ERROR_OK if success,
 *         ERROR_PARSE_UNEXPECTED_TOKEN if unexpected token,
 *         ERORR_AST_TOO_BIG if AST is too big
*/
error_t __parse_expr_term(parser_ctx_t *ctx, expr_binary_t **binary);

/**
 * @brief Parse tokens into factor expression
 * @param ctx Parser context
 * @param binary Binary expression node
 * @return ERROR_OK if success,
 *         ERROR_PARSE_UNEXPECTED_TOKEN if unexpected token,
 *         ERORR_AST_TOO_BIG if AST is too big
*/
error_t __parse_expr_factor(parser_ctx_t *ctx, expr_binary_t **binary);

/**
 * @brief Parse tokens into unary expression
 * @param ctx Parser context
 * @param unary Unary expression node
 * @return ERROR_OK if success,
 *         ERROR_PARSE_UNEXPECTED_TOKEN if unexpected token,
 *         ERORR_AST_TOO_BIG if AST is too big
*/
error_t __parse_expr_unary(parser_ctx_t *ctx, expr_unary_t **unary);

/**
 * @brief Parse tokens into primary expression
 * @param ctx Parser context
 * @param expr Primary expression node
 * @return ERROR_OK if success,
 *         ERROR_PARSE_UNEXPECTED_TOKEN if unexpected token,
 *         ERORR_AST_TOO_BIG if AST is too big
*/
error_t __parse_expr_primary(parser_ctx_t *ctx, expr_t **expr);

/**
 * @brief Parse tokens into lvalue expression
 * @param ctx Parser context
 * @param expr Expression node
 * @return ERROR_OK if success,
 *         ERORR_AST_TOO_BIG if AST is too big,
 *         ERROR_PARSE_UNEXPECTED_TOKEN if unexpected token
*/
error_t __parse_expr_lvalue(parser_ctx_t *ctx, expr_t **expr);

/**
 * @brief Parse tokens into rvalue expression
 * @param ctx Parser context
 * @param expr Expression node
 * @return ERROR_OK if success,
 *         ERORR_AST_TOO_BIG if AST is too big,
 *         ERROR_PARSE_UNEXPECTED_TOKEN if unexpected token
*/
error_t __parse_expr_rvalue(parser_ctx_t *ctx, expr_t **expr);

/**
 * @brief Parse tokens into application
 * @param ctx Parser context
 * @param root Root application node
 * @return ERROR_OK if success,
 *         ERORR_AST_TOO_BIG if AST is too big,
 *         ERROR_PARSE_UNEXPECTED_TOKEN if unexpected token
*/
error_t __parse_utils_root(parser_ctx_t *ctx, root_t **root);

/**
 * @brief Parse tokens into program statement
 * @param ctx Parser context
 * @param program Program node
 * @return ERROR_OK if success,
 *         ERORR_AST_TOO_BIG if AST is too big,
 *         ERROR_PARSE_UNEXPECTED_TOKEN if unexpected token
*/
error_t __parse_utils_program(parser_ctx_t *ctx, program_t *program);

/**
 * @brief Parse tokens into variables statement
 * @param ctx Parser context
 * @param variables Variables node
 * @return ERROR_OK if success,
 *        ERORR_AST_TOO_BIG if AST is too big,
 *        ERROR_PARSE_UNEXPECTED_TOKEN if unexpected token
*/
error_t __parse_utils_variables(parser_ctx_t *ctx, var_t *variables);

/**
 * @brief Parse tokens into variable statement
 * @param ctx Parser context
 * @param variable Variable node
 * @return ERROR_OK if success,
 *         ERORR_AST_TOO_BIG if AST is too big,
 *         ERROR_PARSE_UNEXPECTED_TOKEN if unexpected token
*/
error_t __parse_utils_variable(parser_ctx_t *ctx, var_def_t *variable);

/**
 * @brief Parse tokens into a statement
 * @param ctx Parser context
 * @param stmt Statement node
 * @return ERROR_OK if success,
 *         ERORR_AST_TOO_BIG if AST is too big,
 *         ERROR_PARSE_UNEXPECTED_TOKEN if unexpected token
*/
error_t __parse_stmt(parser_ctx_t *ctx, stmt_t **stmt);

/**
 * @brief Parse tokens into block statement
 * @param ctx Parser context
 * @param block Block node
 * @return ERROR_OK if success,
 *        ERORR_AST_TOO_BIG if AST is too big,
 *        ERROR_PARSE_UNEXPECTED_TOKEN if unexpected token
*/
error_t __parse_stmt_block(parser_ctx_t *ctx, stmt_block_t **block);

/**
 * @brief Parse tokens into if statement
 * @param ctx Parser context
 * @param stmt_if If node
 * @return ERROR_OK if success,
 *        ERORR_AST_TOO_BIG if AST is too big,
 *        ERROR_PARSE_UNEXPECTED_TOKEN if unexpected token
*/
error_t __parse_stmt_if(parser_ctx_t *ctx, stmt_if_t **stmt_if);

/**
 * @brief Parse tokens into for statement
 * @param ctx Parser context
 * @param stmt_for For node
 * @return ERROR_OK if success,
 *        ERORR_AST_TOO_BIG if AST is too big,
 *        ERROR_PARSE_UNEXPECTED_TOKEN if unexpected token
*/
error_t __parse_stmt_for(parser_ctx_t *ctx, stmt_for_t **stmt_for);

/**
 * @brief Parse tokens into goto statement
 * @param ctx Parser context
 * @param stmt_goto Goto node
 * @return ERROR_OK if success,
 *        ERORR_AST_TOO_BIG if AST is too big,
 *        ERROR_PARSE_UNEXPECTED_TOKEN if unexpected token
*/
error_t __parse_stmt_goto(parser_ctx_t *ctx, stmt_goto_t **stmt_goto);

/**
 * @brief Parse tokens into label statement
 * @param ctx Parser context
 * @param stmt_label Label node
 * @return ERROR_OK if success,
 *        ERORR_AST_TOO_BIG if AST is too big,
 *        ERROR_PARSE_UNEXPECTED_TOKEN if unexpected token
*/
error_t __parse_stmt_label(parser_ctx_t *ctx, stmt_label_t **stmt_label);

/**
 * @brief Parse tokens into expression statement
 * @param ctx Parser context
 * @param stmt_expr Expression node
 * @return ERROR_OK if success,
 *        ERORR_AST_TOO_BIG if AST is too big,
 *        ERROR_PARSE_UNEXPECTED_TOKEN if unexpected token
*/
error_t __parse_stmt_expr(parser_ctx_t *ctx, stmt_expr_t **stmt_expr);

/**
 * @brief Check if variable with name `name` exists in current scope
 * @param ctx Parser context
 * @param name Variable name
 * @return true if exists, false otherwise
*/
bool __parser_variable_exists(parser_ctx_t *ctx, const char *name);

#endif //OPT_PARSER___PARSER_PRIVATE_H