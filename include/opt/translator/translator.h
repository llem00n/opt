// *************************************************************************
// translator.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/29/23
// *************************************************************************

#ifndef OPT_TRANSLATOR_TRANSLATOR_H
#define OPT_TRANSLATOR_TRANSLATOR_H

#include <opt/ast/ast.h>
#include <opt/files.h>

#include "opt/err.h"

typedef enum platform {
  PLATFORM_WIN32,
  PLATFORM_WIN64,
  PLATFORM_LENGTH,
} platform_t;

typedef struct translator_ctx translator_ctx_t;

/**
 * @brief Defines a methods structure for translating
 */
typedef struct translator_methods {
#define __METHOD_TRANSLATE(type, name) error_t (*translate_##name)(translator_ctx_t *ctx, const type *item)
#define __METHOD_WRITE(type, name) error_t (*write_##name)(const translator_ctx_t *ctx)

  __METHOD_TRANSLATE(root_t, root);
  __METHOD_TRANSLATE(program_t, program);
  __METHOD_TRANSLATE(var_t, variables);
  __METHOD_TRANSLATE(stmt_t, stmt);
  __METHOD_TRANSLATE(stmt_expr_t, stmt_expr);
  __METHOD_TRANSLATE(stmt_if_t, stmt_if);
  __METHOD_TRANSLATE(stmt_for_t, stmt_for);
  __METHOD_TRANSLATE(stmt_goto_t, stmt_goto);
  __METHOD_TRANSLATE(stmt_label_t, stmt_label);
  __METHOD_TRANSLATE(stmt_block_t, stmt_block);
  __METHOD_TRANSLATE(expr_t, expr);
  __METHOD_TRANSLATE(expr_assign_t, expr_assignment);
  __METHOD_TRANSLATE(expr_binary_t, expr_binary);
  __METHOD_TRANSLATE(expr_unary_t, expr_unary);
  __METHOD_TRANSLATE(expr_number_t, expr_number);
  __METHOD_TRANSLATE(expr_print_t, expr_print);
  __METHOD_TRANSLATE(expr_scan_t, expr_scan);
  __METHOD_TRANSLATE(expr_variable_t, expr_variable);
  __METHOD_WRITE(void, head);
  __METHOD_WRITE(void, proto);
  __METHOD_WRITE(void, code_start);
  __METHOD_WRITE(void, code_end);

#undef __METHOD_WRITE
#undef __METHOD_TRANSLATE
} translator_methods_t;

/**
 * @brief Defines a context for translator
 */
struct translator_ctx {
  root_t *root;
  files_context_t *fctx;
  platform_t platform;
  translator_methods_t methods[PLATFORM_LENGTH];
  uint16_t label_counter;
  int8_t bp_offset;
};

/**
 * @brief Initialize translator context
 * @param ctx Translator context
 * @param root Root node
 * @param fctx Files context
 * @return ERROR_OK if success,
 *         ERROR_BAD_PARAMETER if ctx, root or fctx is NULL
*/
error_t translator_ctx_init(translator_ctx_t *ctx, root_t *root, files_context_t *fctx, platform_t platform);

/**
 * @brief Translate program
 * @param ctx Translator context
 * @return ERROR_OK if success,
 *         ERROR_TRANSLATOR_UNEXPECTED_NODE if unexpected node
*/
error_t translate(translator_ctx_t *ctx);

#endif //OPT_TRANSLATOR_TRANSLATOR_H
