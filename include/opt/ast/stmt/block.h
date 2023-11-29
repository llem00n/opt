// *************************************************************************
// block.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/27/2023
// *************************************************************************

#ifndef OPT_AST_STMT_BLOCK_H
#define OPT_AST_STMT_BLOCK_H

#include <opt/ast/stmt.h>
#include <opt/ast/expr.h>
#include <stddef.h>

/**
 * @brief Block statement node
 */
typedef struct stmt_block {
  stmt_t base;
  stmt_t *first;
} stmt_block_t;

/**
 * @brief Initialize block statement node
 * @param stmt_block Block statement node
 * @param first Pointer to the first statement in the block
 * @param start_token Block statement start token
 * @return ERROR_BAD_PARAMETER if stmt_block or stmts is NULL, ERROR_OK otherwise
 */
error_t stmt_block_init(stmt_block_t *stmt_block, stmt_t *first, token_t *start_token);

/**
 * @brief Get first statement in the block
 * @param stmt_block Block statement node
 * @return First statement in the block
 */
stmt_t **get_stmt_block_first(stmt_block_t *stmt_block);

#endif //OPT_AST_STMT_BLOCK_H