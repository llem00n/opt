// *************************************************************************
// gen.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/30/23
// *************************************************************************

#ifndef OPT_TRANSLATOR_PLATFORMS_GEN_H
#define OPT_TRANSLATOR_PLATFORMS_GEN_H

#define __GEN_TRANSLATOR_METHODS(platform) \
  error_t __translator_##platform##_write_head(const translator_ctx_t *ctx); \
  error_t __translator_##platform##_write_proto(const translator_ctx_t *ctx); \
  error_t __translator_##platform##_write_code_start(const translator_ctx_t *ctx); \
  error_t __translator_##platform##_write_code_end(const translator_ctx_t *ctx); \
  error_t __translate_##platform##_program(translator_ctx_t *ctx, const program_t *program); \
  error_t __translate_##platform##_variables(translator_ctx_t *ctx, const var_t *variables); \
  error_t __translate_##platform##_stmt_if(translator_ctx_t *ctx, const stmt_if_t *stmt); \
  error_t __translate_##platform##_stmt_for(translator_ctx_t *ctx, const stmt_for_t *stmt); \
  error_t __translate_##platform##_stmt_goto(translator_ctx_t *ctx, const stmt_goto_t *stmt); \
  error_t __translate_##platform##_stmt_label(translator_ctx_t *ctx, const stmt_label_t *stmt); \
  error_t __translate_##platform##_stmt_block(translator_ctx_t *ctx, const stmt_block_t *stmt); \
  error_t __translate_##platform##_expr_assignment(translator_ctx_t *ctx, const expr_assign_t *expr); \
  error_t __translate_##platform##_expr_binary(translator_ctx_t *ctx, const expr_binary_t *expr); \
  error_t __translate_##platform##_expr_unary(translator_ctx_t *ctx, const expr_unary_t *expr); \
  error_t __translate_##platform##_expr_number(translator_ctx_t *ctx, const expr_number_t *expr); \
  error_t __translate_##platform##_expr_print(translator_ctx_t *ctx, const expr_print_t *expr); \
  error_t __translate_##platform##_expr_scan(translator_ctx_t *ctx, const expr_scan_t *expr); \
  error_t __translate_##platform##_expr_variable(translator_ctx_t *ctx, const expr_variable_t *expr); \

#endif //OPT_TRANSLATOR_PLATFORMS_GEN_H
