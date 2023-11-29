// *************************************************************************
// stmt.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/26/2023
// *************************************************************************
#ifndef OPT_AST_STMT_H
#define OPT_AST_STMT_H

#include <opt/err.h>
#include <opt/token.h>

/**
 * @brief Statement types
 */
typedef enum stmt_type {
  STMT_IF    = 1 << 0,
  STMT_FOR   = 1 << 1,
  STMT_EXPR  = 1 << 2,
  STMT_BLOCK = 1 << 3,
  STMT_GOTO  = 1 << 4,
  STMT_LABEL = 1 << 5,
} stmt_type_t;

/**
 * @brief Statement node
*/
typedef struct stmt {
  stmt_type_t type;
  token_t *start_token;
  struct stmt *next;
} stmt_t;

/**
 * @brief Initialize statement node
 * @param stmt Statement node
 * @param type Statement type
 * @param start_token Statement start token
 * @param next Next statement node
 * @return ERROR_BAD_PARAMETER if stmt is NULL, ERROR_OK otherwise
*/
error_t stmt_init(stmt_t *stmt, stmt_type_t type, token_t *start_token, stmt_t *next);

/**
 * @brief Get statement type
 * @param stmt Statement node
 * @return Statement type
 */
stmt_type_t get_stmt_type(const stmt_t *stmt);

/**
 * @brief Get statement start token
 * @param stmt Statement node
 * @return Statement start token
*/
token_t *get_stmt_start_token(const stmt_t *stmt);

/**
 * @brief Get next statement node
 * @param stmt Statement node
 * @return Next statement node
*/
stmt_t *get_stmt_next(const stmt_t *stmt);

#endif //OPT_AST_STMT_H