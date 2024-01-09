// *************************************************************************
// __translator_private.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/30/23
// *************************************************************************

#ifndef OPT_TRANSLATOR__TRANSLATOR_PRIVATE_H
#define OPT_TRANSLATOR__TRANSLATOR_PRIVATE_H

#include <opt/translator/translator.h>

/**
 * @brief Translate root node
 * @param ctx Translator context
 * @param root Root node
 * @return ERROR_OK if success,
 *         ERROR_TRANSLATOR_UNEXPECTED_NODE if unexpected node
*/
error_t __translate_root(translator_ctx_t *ctx, const root_t *root);

/**
 * @brieft Translate statement node
 * @param ctx Translator context
 * @param stmt Statement node
 * @return ERROR_OK if success,
 *         ERROR_TRANSLATOR_UNEXPECTED_NODE if unexpected node
 */
error_t __translate_stmt(translator_ctx_t *ctx, const stmt_t *stmt);

/**
 * @brief Translate expression node
 * @param ctx Translator context
 * @param expr Expression node
 * @return ERROR_OK if success,
 *         ERROR_TRANSLATOR_UNEXPECTED_NODE if unexpected node
 */
error_t __translate_expr(translator_ctx_t *ctx, const expr_t *expr);

/**
 * @brief Translate expression statement node
 * @param ctx Translator context
 * @param stmt Expression statement node
 * @return ERROR_OK if success,
 *         ERROR_TRANSLATOR_UNEXPECTED_NODE if unexpected node
 */
error_t __translate_stmt_expr(translator_ctx_t *ctx, const stmt_expr_t *stmt);

#endif //OPT_TRANSLATOR__TRANSLATOR_PRIVATE_H
