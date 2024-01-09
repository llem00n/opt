// *************************************************************************
// win32.c
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/30/23
// *************************************************************************
#include <opt/translator/translator.h>
#include <opt/translator/platforms/win32.h>

error_t __translator_win32_write_head(const translator_ctx_t *ctx) {
  fprintf(ctx->fctx->aasm, ".686\n.model flat, stdcall\noption casemap :none\n\n");
  return ERROR_OK;
}

error_t __translator_win32_write_proto(const translator_ctx_t *ctx) {
  fprintf(ctx->fctx->aasm,
    "ExitProcess PROTO :DWORD\n"
    "scanf PROTO C, :DWORD, :VARARG\n"
    "printf PROTO C, :DWORD, :VARARG\n"
  );
  return ERROR_OK;
}

error_t __translator_win32_write_code_start(const translator_ctx_t *ctx) {
  fprintf(ctx->fctx->aasm, ""
    ".code\n"
    "__op_scan PROC\n"
    "  push ebp\n"
    "  mov ebp, esp\n"
    "  invoke scanf, offset _op_scan_format, offset _op_scan_value\n"
    "  mov ax, _op_scan_value\n"
    "  cwde\n"
    "  pop ebp\n"
    "  ret\n"
    "__op_scan ENDP\n"

    "__op_print PROC\n"
    "  push ebp\n"
    "  mov ebp, esp\n"
    "  invoke printf, offset _op_print_format, eax\n"
    "  pop ebp\n"
    "  ret\n"
    "__op_print ENDP\n"

    "start:\n"
  );
  return ERROR_OK;
}

error_t __translator_win32_write_code_end(const translator_ctx_t *ctx) {
  fprintf(ctx->fctx->aasm, ""
    "__exit:\n"
    "  invoke ExitProcess, 0\n"
    "end start\n"
  );
  return ERROR_OK;
}

error_t __translate_win32_program(translator_ctx_t *ctx, const program_t *program) {
  if (ctx == NULL || program == NULL) {
    return ERROR_BAD_PARAMETER;
  }

  fprintf(ctx->fctx->aasm, ";;;; Program %s\n\n", program->name);
  return ERROR_OK;
}

error_t __translate_win32_variables(translator_ctx_t *ctx, const var_t *variables) {
  if (ctx == NULL || variables == NULL) {
    return ERROR_BAD_PARAMETER;
  }

  fprintf(ctx->fctx->aasm, ""
    ".data\n"
    "  _op_scan_format db \"%%hd\", 0\n"
    "  _op_scan_value dw 0\n"
    "  _op_print_format db \"%%d \", 0\n"
  );

  for (const var_def_t *var = variables->def; var->name; var++) {
    char line[256];
    sprintf(line, "  _Var_%s dw %d\n", var->name, var->value);
    fprintf(ctx->fctx->aasm, "%s", line);
  }

  return ERROR_OK;
}

error_t __translate_win32_stmt_if(translator_ctx_t *ctx, const stmt_if_t *stmt) {
  if (ctx == NULL || stmt == NULL) {
    return ERROR_BAD_PARAMETER;
  }

  const uint16_t c = ++ctx->label_counter;
  error_t error = ctx->methods[ctx->platform].translate_expr(ctx, stmt->cond_expr);
  if (error) {
    return error;
  }

  char code[1024];
  sprintf(code, ""
    "  pop eax\n"
    "  cmp eax, 0\n"
    "  jne __if_true_%d\n"
    "  jmp __if_false_%d\n"
    "__if_true_%d:\n",
    c, c, c
  );
  fprintf(ctx->fctx->aasm, code);
  ctx->bp_offset--;

  error = ctx->methods[ctx->platform].translate_stmt_goto(ctx, stmt->goto_stmt);
  if (error) {
    return error;
  }

  sprintf(code, ""
    "__if_false_%d:\n",
    c
  );
  fprintf(ctx->fctx->aasm, code);

  return ERROR_OK;
}

error_t __translate_win32_stmt_for(translator_ctx_t *ctx, const stmt_for_t *stmt) {
  if (ctx == NULL || stmt == NULL) {
    return ERROR_BAD_PARAMETER;
  }

  const uint16_t c = ++ctx->label_counter;
  error_t error = ctx->methods[ctx->platform].translate_expr(ctx, stmt->init_expr);
  if (error) {
    return error;
  }

  char code[1024];
  sprintf(code, ""
    "  pop eax\n"
    "  mov _Var_%s, ax\n"
    "__for_start_%d:\n",
    stmt->variable, c
  );
  fprintf(ctx->fctx->aasm, code);
  ctx->bp_offset--;

  error = ctx->methods[ctx->platform].translate_expr(ctx, stmt->to_expr);
  if (error) {
    return error;
  }

  sprintf(code, ""
    "  pop ebx\n"
    "  mov ax, _Var_%s\n"
    "  cwde\n"
    "  cmp eax, ebx\n"
    "  jg __for_end_%d\n",
    stmt->variable, c
  );
  fprintf(ctx->fctx->aasm, code);
  ctx->bp_offset--;

  error = ctx->methods[ctx->platform].translate_stmt_block(ctx, stmt->body_stmt);
  if (error) {
    return error;
  }

  sprintf(code, ""
    "  mov ax, _Var_%s\n"
    "  cwde\n"
    "  inc eax\n"
    "  mov _Var_%s, ax\n"
    "  jmp __for_start_%d\n"
    "__for_end_%d:\n",
    stmt->variable, stmt->variable, c, c
  );
  fprintf(ctx->fctx->aasm, code);

  return ERROR_OK;
}

error_t __translate_win32_stmt_goto(translator_ctx_t *ctx, const stmt_goto_t *stmt) {
  if (ctx == NULL || stmt == NULL) {
    return ERROR_BAD_PARAMETER;
  }

  char code[1024];
  sprintf(code, ""
    "  jmp __label_%s\n",
    stmt->label
  );
  fprintf(ctx->fctx->aasm, code);

  return ERROR_OK;
}

error_t __translate_win32_stmt_label(translator_ctx_t *ctx, const stmt_label_t *stmt) {
  if (ctx == NULL || stmt == NULL) {
    return ERROR_BAD_PARAMETER;
  }

  char code[1024];
  sprintf(code, ""
    "__label_%s:\n",
    stmt->name
  );
  fprintf(ctx->fctx->aasm, code);

  return ERROR_OK;
}

error_t __translate_win32_stmt_block(translator_ctx_t *ctx, const stmt_block_t *stmt) {
  if (ctx == NULL || stmt == NULL) {
    return ERROR_BAD_PARAMETER;
  }

  for (const stmt_t *s = stmt->first; s; s = s->next) {
    const error_t error = ctx->methods[ctx->platform].translate_stmt(ctx, s);
    if (error) {
      return error;
    }

    while (ctx->bp_offset < 0) {
      fprintf(ctx->fctx->aasm, "  push eax\n");
      ctx->bp_offset++;
    }

    while (ctx->bp_offset > 0) {
      fprintf(ctx->fctx->aasm, "  pop eax\n");
      ctx->bp_offset--;
    }
  }

  return ERROR_OK;
}

error_t __translate_win32_stmt(translator_ctx_t *ctx, const stmt_t *stmt) {
  if (ctx == NULL || stmt == NULL) {
    return ERROR_BAD_PARAMETER;
  }

  switch (stmt->type) {
    case STMT_EXPR:
      return ctx->methods[ctx->platform].translate_stmt_expr(ctx, (stmt_expr_t *)&stmt);
    case STMT_IF:
      return ctx->methods[ctx->platform].translate_stmt_if(ctx, (stmt_if_t *)&stmt);
    case STMT_FOR:
      return ctx->methods[ctx->platform].translate_stmt_for(ctx, (stmt_for_t *)&stmt);
    case STMT_GOTO:
      return ctx->methods[ctx->platform].translate_stmt_goto(ctx, (stmt_goto_t *)&stmt);
    case STMT_LABEL:
      return ctx->methods[ctx->platform].translate_stmt_label(ctx, (stmt_label_t *)&stmt);
    case STMT_BLOCK:
      return ctx->methods[ctx->platform].translate_stmt_block(ctx, (stmt_block_t *)&stmt);
    default:
      return ERROR_TRANSLATOR_UNEXPECTED_NODE;
  }
}

error_t __translate_win32_stmt_expr(translator_ctx_t *ctx, const stmt_expr_t *stmt) {
  return ctx->methods[ctx->platform].translate_expr(ctx, stmt->expr);
}

error_t __translate_win32_expr_assignment(translator_ctx_t *ctx, const expr_assign_t *expr) {
  if (ctx == NULL || expr == NULL) {
    return ERROR_BAD_PARAMETER;
  }

  const error_t error = ctx->methods[ctx->platform].translate_expr(ctx, expr->base.right);
  if (error) {
    return error;
  }

  char code[1024];
  if (expr->base.left->type & EXPR_OUTPUT) {
    sprintf(code, ""
      "  pop eax\n"
      "  push eax\n"
      "  call __op_print\n"
    );
  } else if (expr->base.left->type & EXPR_VARIABLE) {
    sprintf(code, ""
      "  pop eax\n"
      "  push eax\n"
      "  mov _Var_%s, ax\n",
      ((expr_variable_t  *)expr->base.left)->name
    );
  } else {
    return ERROR_TRANSLATOR_UNEXPECTED_NODE;
  }
  fprintf(ctx->fctx->aasm, code);

  return ERROR_OK;
}

error_t __translate_win32_expr_binary(translator_ctx_t *ctx, const expr_binary_t *expr) {
  if (ctx == NULL || expr == NULL) {
    return ERROR_BAD_PARAMETER;
  }

  if (expr->type == EXPR_BINARY_TYPE_ASSIGN) {
    return ctx->methods[ctx->platform].translate_expr_assignment(ctx, (expr_assign_t *)expr);
  }

  error_t error = ctx->methods[ctx->platform].translate_expr(ctx, expr->left);
  if (error) {
    return error;
  }

  error = ctx->methods[ctx->platform].translate_expr(ctx, expr->right);
  if (error) {
    return error;
  }

  switch (expr->type) {
    case EXPR_BINARY_TYPE_ADD:
      fprintf(ctx->fctx->aasm, ""
        "  pop ebx\n"
        "  pop eax\n"
        "  add eax, ebx\n"
        "  push eax\n"
      );
      ctx->bp_offset--;
    break;
    case EXPR_BINARY_TYPE_SUB:
      fprintf(ctx->fctx->aasm, ""
        "  pop ebx\n"
        "  pop eax\n"
        "  sub eax, ebx\n"
        "  push eax\n"
      );
      ctx->bp_offset--;
      break;
    case EXPR_BINARY_TYPE_MUL:
      fprintf(ctx->fctx->aasm, ""
        "  pop ebx\n"
        "  pop eax\n"
        "  imul bx\n"
        "  push eax\n"
      );
      ctx->bp_offset--;
      break;
    case EXPR_BINARY_TYPE_DIV:
      fprintf(ctx->fctx->aasm, ""
        "  pop ebx\n"
        "  pop eax\n"
        "  xor edx, edx\n"
        "  idiv bx\n"
        "  cwde\n"
        "  push eax\n"
      );
      ctx->bp_offset--;
      break;
    case EXPR_BINARY_TYPE_MOD:
      fprintf(ctx->fctx->aasm, ""
        "  pop ebx\n"
        "  pop eax\n"
        "  xor edx, edx\n"
        "  idiv bx\n"
        "  mov ax, dx\n"
        "  cwde\n"
        "  push eax\n"
      );
      ctx->bp_offset--;
      break;
    case EXPR_BINARY_TYPE_EQ:
      fprintf(ctx->fctx->aasm, ""
        "  pop ebx\n"
        "  pop eax\n"
        "  cmp eax, ebx\n"
        "  mov eax, 0\n"
        "  sete al\n"
        "  cbw\n"
        "  cwde\n"
        "  push eax\n"
      );
      ctx->bp_offset--;
      break;
    case EXPR_BINARY_TYPE_NEQ:
      fprintf(ctx->fctx->aasm, ""
        "  pop ebx\n"
        "  pop eax\n"
        "  cmp eax, ebx\n"
        "  mov eax, 0\n"
        "  setne al\n"
        "  cbw\n"
        "  cwde\n"
        "  push eax\n"
      );
      ctx->bp_offset--;
      break;
    case EXPR_BINARY_TYPE_LT:
      fprintf(ctx->fctx->aasm, ""
        "  pop ebx\n"
        "  pop eax\n"
        "  cmp eax, ebx\n"
        "  mov eax, 0\n"
        "  setl al\n"
        "  cbw\n"
        "  cwde\n"
        "  push eax\n"
      );
      ctx->bp_offset--;
      break;
    case EXPR_BINARY_TYPE_GT:
      fprintf(ctx->fctx->aasm, ""
        "  pop ebx\n"
        "  pop eax\n"
        "  cmp eax, ebx\n"
        "  mov eax, 0\n"
        "  setg al\n"
        "  cbw\n"
        "  cwde\n"
        "  push eax\n"
      );
      ctx->bp_offset--;
      break;
    case EXPR_BINARY_TYPE_AND: {
      char code[1024];
      const uint16_t c = ++ctx->label_counter;
      sprintf(code, ""
        "  pop ebx\n"
        "  pop eax\n"
        "  cmp eax, 0\n"
        "  je __and_false_%d\n"
        "  cmp ebx, 0\n"
        "  je __and_false_%d\n"
        "  mov eax, 1\n"
        "  jmp __and_end_%d\n"
        "__and_false_%d:\n"
        "  mov eax, 0\n"
        "__and_end_%d:\n"
        "  push eax\n",
        c, c, c, c, c
      );
      fprintf(ctx->fctx->aasm, code);
      ctx->bp_offset--;
      break;
    }
    case EXPR_BINARY_TYPE_OR: {
      char code[1024];
      const uint16_t c = ++ctx->label_counter;
      sprintf(code, ""
        "  pop ebx\n"
        "  pop eax\n"
        "  cmp eax, 0\n"
        "  jne __or_true_%d\n"
        "  cmp ebx, 0\n"
        "  jne __or_true_%d\n"
        "  mov eax, 0\n"
        "  jmp __or_end_%d\n"
        "__or_true_%d:\n"
        "  mov eax, 1\n"
        "__or_end_%d:\n"
        "  push eax\n",
        c, c, c, c, c
      );
      fprintf(ctx->fctx->aasm, code);
      ctx->bp_offset--;
      break;
    }
    default:
      error = ERROR_TRANSLATOR_UNEXPECTED_NODE;
  }

  return error;
}

error_t __translate_win32_expr_unary(translator_ctx_t *ctx, const expr_unary_t *expr) {
  if (ctx == NULL || expr == NULL) {
    return ERROR_BAD_PARAMETER;
  }

  const error_t error = ctx->methods[ctx->platform].translate_expr(ctx, expr->expr);
  if (error) {
    return error;
  }

  switch (expr->type) {
    case EXPR_UNARY_TYPE_MINUS:
      fprintf(ctx->fctx->aasm, ""
        "  pop eax\n"
        "  neg eax\n"
        "  push eax\n"
      );
      break;
    case EXPR_UNARY_TYPE_NOT:
      fprintf(ctx->fctx->aasm, ""
        "  pop eax\n"
        "  cmp eax, 0\n"
        "  mov eax, 0\n"
        "  sete al\n"
        "  cbw\n"
        "  cwde\n"
        "  push eax\n"
      );
      break;
    default:
      return ERROR_TRANSLATOR_UNEXPECTED_NODE;
  }

  return ERROR_OK;
}

error_t __translate_win32_expr_number(translator_ctx_t *ctx, const expr_number_t *expr) {
  if (ctx == NULL || expr == NULL) {
    return ERROR_BAD_PARAMETER;
  }

  char code[1024];
  sprintf(code, ""
    "  push %d\n",
    expr->value
  );
  fprintf(ctx->fctx->aasm, code);
  ctx->bp_offset++;

  return ERROR_OK;
}

error_t __translate_win32_expr_print(translator_ctx_t *ctx, const expr_print_t *expr) {
  if (ctx == NULL || expr == NULL) {
    return ERROR_BAD_PARAMETER;
  }

  fprintf(ctx->fctx->aasm, ""
    "  pop eax\n"
    "  push eax\n"
    "  call __op_print\n"
  );

  return ERROR_OK;
}

error_t __translate_win32_expr_scan(translator_ctx_t *ctx, const expr_scan_t *expr) {
  if (ctx == NULL || expr == NULL) {
    return ERROR_BAD_PARAMETER;
  }

  fprintf(ctx->fctx->aasm, ""
    "  invoke __op_scan\n"
    "  push eax\n"
  );
  ctx->bp_offset++;

  return ERROR_OK;
}

error_t __translate_win32_expr_variable(translator_ctx_t *ctx, const expr_variable_t *expr) {
  if (ctx == NULL || expr == NULL) {
    return ERROR_BAD_PARAMETER;
  }

  char code[1024];
  sprintf(code, ""
    "  mov ax, _Var_%s\n"
    "  cwde\n"
    "  push eax\n",
    expr->name
  );
  fprintf(ctx->fctx->aasm, code);
  ctx->bp_offset++;

  return ERROR_OK;
}