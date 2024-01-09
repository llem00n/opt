// *************************************************************************
// translator.c
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/30/23
// *************************************************************************
#include <opt/translator/translator.h>
#include <opt/translator/__translator_private.h>
#include <opt/translator/platforms/win32.h>
#include <opt/translator/platforms/win64.h>

error_t translator_ctx_init(translator_ctx_t *ctx, root_t *root, files_context_t *fctx, const platform_t platform) {
  if (ctx == NULL || root == NULL || fctx == NULL || platform >= PLATFORM_LENGTH) {
    return ERROR_BAD_PARAMETER;
  }

  ctx->root = root;
  ctx->fctx = fctx;
  ctx->platform = platform;
  ctx->label_counter = 0;
  ctx->bp_offset = 0;

  ctx->methods[PLATFORM_WIN32] = (translator_methods_t) {
    .translate_root = __translate_root,
    .translate_program = __translate_win32_program,
    .translate_stmt = __translate_stmt,
    .translate_stmt_expr  = __translate_stmt_expr,
    .translate_stmt_if = __translate_win32_stmt_if,
    .translate_stmt_for = __translate_win32_stmt_for,
    .translate_stmt_goto = __translate_win32_stmt_goto,
    .translate_stmt_label = __translate_win32_stmt_label,
    .translate_stmt_block = __translate_win32_stmt_block,
    .translate_expr = __translate_expr,
    .translate_expr_assignment = __translate_win32_expr_assignment,
    .translate_expr_binary = __translate_win32_expr_binary,
    .translate_expr_unary = __translate_win32_expr_unary,
    .translate_expr_number = __translate_win32_expr_number,
    .translate_expr_print = __translate_win32_expr_print,
    .translate_expr_scan = __translate_win32_expr_scan,
    .translate_variables = __translate_win32_variables,
    .translate_expr_variable = __translate_win32_expr_variable,
    .write_head = __translator_win32_write_head,
    .write_proto = __translator_win32_write_proto,
    .write_code_start = __translator_win32_write_code_start,
    .write_code_end = __translator_win32_write_code_end,
  };

  // ctx->methods[PLATFORM_WIN64] = (translator_methods_t) {
  //   .translate_root = __translate_root,
  //   .translate_program = __translate_win64_program,
  //   .translate_stmt = __translate_stmt,
  //   .translate_stmt_expr  = __translate_stmt_expr,
  //   .translate_stmt_if = __translate_win64_stmt_if,
  //   .translate_stmt_for = __translate_win64_stmt_for,
  //   .translate_stmt_goto = __translate_win64_stmt_goto,
  //   .translate_stmt_label = __translate_win64_stmt_label,
  //   .translate_stmt_block = __translate_win64_stmt_block,
  //   .translate_expr = __translate_expr,
  //   .translate_expr_assignment = __translate_win64_expr_assignment,
  //   .translate_expr_binary = __translate_win64_expr_binary,
  //   .translate_expr_unary = __translate_win64_expr_unary,
  //   .translate_expr_number = __translate_win64_expr_number,
  //   .translate_expr_print = __translate_win64_expr_print,
  //   .translate_expr_scan = __translate_win64_expr_scan,
  //   .translate_expr_variable = __translate_win64_expr_variable,
  //   .write_head = __translator_win64_write_head,
  //   .write_proto = __translator_win64_write_proto,
  //   .write_code_start = __translator_win64_write_code_start,
  //   .write_code_end = __translator_win64_write_code_end,
  // };

  return ERROR_OK;
}

error_t translate(translator_ctx_t *ctx) {
  if (ctx == NULL) {
    return ERROR_BAD_PARAMETER;
  }

  return ctx->methods[ctx->platform].translate_root(ctx, ctx->root);
}

error_t __translate_root(translator_ctx_t *ctx, const root_t *root) {
  error_t error;
  if (ctx == NULL || root == NULL) {
    return ERROR_BAD_PARAMETER;
  }

  if (
    (error = ctx->methods[ctx->platform].translate_program(ctx, &root->program), error != ERROR_OK) ||
    (error = ctx->methods[ctx->platform].write_head(ctx), error != ERROR_OK) ||
    (error = ctx->methods[ctx->platform].write_proto(ctx), error != ERROR_OK) ||
    (error = ctx->methods[ctx->platform].translate_variables(ctx, &root->var), error != ERROR_OK) ||
    (error = ctx->methods[ctx->platform].write_code_start(ctx), error != ERROR_OK) ||
    (error = ctx->methods[ctx->platform].translate_stmt_block(ctx, root->block), error != ERROR_OK) ||
    (error = ctx->methods[ctx->platform].write_code_end(ctx), error != ERROR_OK)) {
    return error;
  }

  return ERROR_OK;
}

error_t __translate_stmt(translator_ctx_t *ctx, const stmt_t *stmt) {
  switch (stmt->type) {
    case STMT_IF:
      return ctx->methods[ctx->platform].translate_stmt_if(ctx, (stmt_if_t *)stmt);
    case STMT_FOR:
      return ctx->methods[ctx->platform].translate_stmt_for(ctx, (stmt_for_t *)stmt);
    case STMT_EXPR:
      return ctx->methods[ctx->platform].translate_stmt_expr(ctx, (stmt_expr_t *)stmt);
    case STMT_GOTO:
      return ctx->methods[ctx->platform].translate_stmt_goto(ctx, (stmt_goto_t *)stmt);
    case STMT_BLOCK:
      return ctx->methods[ctx->platform].translate_stmt_block(ctx, (stmt_block_t *)stmt);
    case STMT_LABEL:
      return ctx->methods[ctx->platform].translate_stmt_label(ctx, (stmt_label_t *)stmt);
    default:
      return ERROR_TRANSLATOR_UNEXPECTED_NODE;
  }

  return ERROR_TRANSLATOR_UNEXPECTED_NODE;
}

error_t __translate_stmt_expr(translator_ctx_t *ctx, const stmt_expr_t *stmt) {
  return ctx->methods[ctx->platform].translate_expr(ctx, stmt->expr);
}

error_t __translate_expr(translator_ctx_t *ctx, const expr_t *expr) {
  if (expr->type & EXPR_BINARY) {
    return ctx->methods[ctx->platform].translate_expr_binary(ctx, (expr_binary_t *)expr);
  } else if (expr->type & EXPR_UNARY) {
    return ctx->methods[ctx->platform].translate_expr_unary(ctx, (expr_unary_t *)expr);
  } else if (expr->type & EXPR_NUMBER) {
    return ctx->methods[ctx->platform].translate_expr_number(ctx, (expr_number_t *)expr);
  } else if (expr->type & EXPR_OUTPUT) {
    return ctx->methods[ctx->platform].translate_expr_print(ctx, (expr_print_t *)expr);
  } else if (expr->type & EXPR_INPUT) {
    return ctx->methods[ctx->platform].translate_expr_scan(ctx, (expr_scan_t *)expr);
  } else if (expr->type & EXPR_VARIABLE) {
    return ctx->methods[ctx->platform].translate_expr_variable(ctx, (expr_variable_t *)expr);
  } else {
    return ERROR_TRANSLATOR_UNEXPECTED_NODE;
  }

  return ERROR_TRANSLATOR_UNEXPECTED_NODE;
}