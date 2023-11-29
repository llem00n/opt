// *************************************************************************
// parser.c
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/28/23
// *************************************************************************

#include <opt/parser/parser.h>
#include <opt/parser/__parser_private.h>
#include <opt/token.h>
#include <stdlib.h>

error_t parser_ctx_init(parser_ctx_t *ctx, token_t *start_token, int8_t *ast, size_t max_ast_size) {
  if (ctx == NULL || start_token == NULL || ast == NULL) {
    return ERROR_BAD_PARAMETER;
  }
  ctx->ast_start = ctx->ast_cursor = ast;
  ctx->max_ast_size = max_ast_size;
  ctx->token_cursor = start_token;
  ctx->error = ERROR_OK;
  return ERROR_OK;
}

error_t parse(parser_ctx_t *ctx) {
  return __parse_utils_root(ctx, &ctx->root);
}

root_t *get_parser_ctx_root(const parser_ctx_t* ctx) {
  return ctx->root;
}

void *__parser_alloc(parser_ctx_t *ctx, const size_t size) {
  if (ctx->ast_cursor + size > ctx->ast_start + ctx->max_ast_size) {
    ctx->error = ERROR_AST_TOO_BIG;
    return NULL;
  }

  void *ptr = ctx->ast_cursor;
  ctx->ast_cursor += size;
  return ptr;
}

error_t __parse_expr_assignment(parser_ctx_t *ctx, expr_t **expr) {
  token_t *start_token = NULL;
  int8_t *ast_cursor = NULL;
  expr_t *left = NULL, *right = NULL, *tmp = NULL, *last = NULL;
  error_t error = ERROR_OK;
  *expr = NULL;

  while (ctx->token_cursor->type != TOKEN_EOF) {
    start_token = ctx->token_cursor;
    ast_cursor = ctx->ast_cursor;

    error = __parse_expr_lvalue(ctx, &left);
    if (error == ERROR_PARSE_UNEXPECTED_TOKEN) {
      break;
    } else if (error != ERROR_OK) {
      return error;
    } else {
      if ((ctx->token_cursor++)->type != TOKEN_ASSIGN) {
        error = ERROR_PARSE_UNEXPECTED_TOKEN;
        ctx->token_cursor = start_token;
        ctx->ast_cursor = ast_cursor;
        break;
      }

      last = tmp;
      tmp = __parser_alloc(ctx, sizeof(expr_assign_t));
      if (tmp == NULL) {
        return ERROR_AST_TOO_BIG;
      }

      if (last) {
        ((expr_binary_t *) last)->right = tmp;
      }

      error = expr_assign_init((expr_assign_t *) tmp, left, NULL, start_token);
      if (error != ERROR_OK) {
        return error;
      }
    }
  }

  if (ctx->token_cursor->type == TOKEN_EOF) {
    return ERROR_PARSE_UNEXCPECTED_END_OF_FILE;
  }

  if (error != ERROR_PARSE_UNEXPECTED_TOKEN) {
    return error;
  }

  error = __parse_expr_logical(ctx, (expr_binary_t**) &right);
  if (error != ERROR_OK) {
    return error;
  }

  if (tmp) {
    ((expr_binary_t *) tmp)->right = right;
    *expr = (expr_t *) tmp;
  } else {
    *expr = right;
  }

  return error;
}

error_t __parse_expr_logical(parser_ctx_t *ctx, expr_binary_t **binary) {
  token_t *start_token = ctx->token_cursor;
  expr_t *left = NULL, *right = NULL, *tmp = NULL;

  error_t error = __parse_expr_equality(ctx, (expr_binary_t **) &left);
  if (error != ERROR_OK) {
    return error;
  }

  while (ctx->token_cursor->type != TOKEN_EOF) {
    if (ctx->token_cursor->type != TOKEN_AND && ctx->token_cursor->type != TOKEN_OR) {
      break;
    }
    const expr_binary_type_t type = ctx->token_cursor->type == TOKEN_AND ? EXPR_BINARY_TYPE_AND : EXPR_BINARY_TYPE_OR;
    ctx->token_cursor++;
    
    error = __parse_expr_equality(ctx, (expr_binary_t **) &right);
    if (error != ERROR_OK) {
      return error;
    }

    tmp = __parser_alloc(ctx, sizeof(expr_binary_t));
    if (tmp == NULL) {
      return ERROR_AST_TOO_BIG;
    }

    expr_binary_init((expr_binary_t *) tmp, type, left, right, start_token);
    left = tmp;
    if (!*binary) {
      *binary = (expr_binary_t *) tmp;
    }
  }

  if (ctx->token_cursor->type == TOKEN_EOF) {
    return ERROR_PARSE_UNEXCPECTED_END_OF_FILE;
  }

  if (!*binary) {
    *binary = (expr_binary_t *) left;
  }

  return ERROR_OK;
}

error_t __parse_expr_equality(parser_ctx_t *ctx, expr_binary_t **binary) {
  token_t *start_token = ctx->token_cursor;
  expr_t *left = NULL, *right = NULL, *tmp = NULL;

  error_t error = __parse_expr_comparison(ctx, (expr_binary_t **) &left);
  if (error != ERROR_OK) {
    return error;
  }

  while (ctx->token_cursor->type != TOKEN_EOF) {
    if (ctx->token_cursor->type != TOKEN_EQUALS && ctx->token_cursor->type != TOKEN_NOT_EQUALS) {
      break;
    }
    const expr_binary_type_t type = ctx->token_cursor->type == TOKEN_EQUALS ? EXPR_BINARY_TYPE_EQ : EXPR_BINARY_TYPE_NEQ;
    ctx->token_cursor++;
    
    error = __parse_expr_comparison(ctx, (expr_binary_t **) &right);
    if (error != ERROR_OK) {
      return error;
    }

    tmp = __parser_alloc(ctx, sizeof(expr_binary_t));
    if (tmp == NULL) {
      return ERROR_AST_TOO_BIG;
    }

    expr_binary_init((expr_binary_t *) tmp, type, left, right, start_token);
    left = tmp;
    if (!*binary) {
      *binary = (expr_binary_t *) tmp;
    }
  }

  if (ctx->token_cursor->type == TOKEN_EOF) {
    return ERROR_PARSE_UNEXCPECTED_END_OF_FILE;
  }

  if (!*binary) {
    *binary = (expr_binary_t *) left;
  }

  return ERROR_OK;
}

error_t __parse_expr_comparison(parser_ctx_t *ctx, expr_binary_t **binary) {
  token_t *start_token = ctx->token_cursor;
  expr_t *left = NULL, *right = NULL, *tmp = NULL;

  error_t error = __parse_expr_term(ctx, (expr_binary_t **) &left);
  if (error != ERROR_OK) {
    return error;
  }

  while (ctx->token_cursor->type != TOKEN_EOF) {
    if (ctx->token_cursor->type != TOKEN_LESS && ctx->token_cursor->type != TOKEN_GREATER) {
      break;
    }
    const expr_binary_type_t type = ctx->token_cursor->type == TOKEN_LESS ? EXPR_BINARY_TYPE_LT : EXPR_BINARY_TYPE_GT;
    ctx->token_cursor++;
    
    error = __parse_expr_term(ctx, (expr_binary_t **) &right);
    if (error != ERROR_OK) {
      return error;
    }

    tmp = __parser_alloc(ctx, sizeof(expr_binary_t));
    if (tmp == NULL) {
      return ERROR_AST_TOO_BIG;
    }

    expr_binary_init((expr_binary_t *) tmp, type, left, right, start_token);
    left = tmp;
    if (!*binary) {
      *binary = (expr_binary_t *) tmp;
    }
  }

  if (ctx->token_cursor->type == TOKEN_EOF) {
    return ERROR_PARSE_UNEXCPECTED_END_OF_FILE;
  }

  if (!*binary) {
    *binary = (expr_binary_t *) left;
  }

  return ERROR_OK;
}

error_t __parse_expr_term(parser_ctx_t *ctx, expr_binary_t **binary) {
  token_t *start_token = ctx->token_cursor;
  expr_t *left = NULL, *right = NULL, *tmp = NULL;

  error_t error = __parse_expr_factor(ctx, (expr_binary_t **) &left);
  if (error != ERROR_OK) {
    return error;
  }

  while (ctx->token_cursor->type != TOKEN_EOF) {
    if (ctx->token_cursor->type != TOKEN_PLUS && ctx->token_cursor->type != TOKEN_MINUS) {
      break;
    }
    const expr_binary_type_t type = ctx->token_cursor->type == TOKEN_PLUS ? EXPR_BINARY_TYPE_ADD : EXPR_BINARY_TYPE_SUB;
    ctx->token_cursor++;
    
    error = __parse_expr_factor(ctx, (expr_binary_t **) &right);
    if (error != ERROR_OK) {
      return error;
    }

    tmp = __parser_alloc(ctx, sizeof(expr_binary_t));
    if (tmp == NULL) {
      return ERROR_AST_TOO_BIG;
    }

    expr_binary_init((expr_binary_t *) tmp, type, left, right, start_token);
    left = tmp;
    if (!*binary) {
      *binary = (expr_binary_t *) tmp;
    }
  }

  if (ctx->token_cursor->type == TOKEN_EOF) {
    return ERROR_PARSE_UNEXCPECTED_END_OF_FILE;
  }

  if (!*binary) {
    *binary = (expr_binary_t *) left;
  }

  return ERROR_OK;
}

error_t __parse_expr_factor(parser_ctx_t *ctx, expr_binary_t **binary) {
  token_t *start_token = ctx->token_cursor;
  expr_t *left = NULL, *right = NULL, *tmp = NULL;

  error_t error = __parse_expr_unary(ctx, (expr_unary_t **) &left);
  if (error != ERROR_OK) {
    return error;
  }

  while (ctx->token_cursor->type != TOKEN_EOF) {
    if (ctx->token_cursor->type != TOKEN_MULTIPLY && ctx->token_cursor->type != TOKEN_DIV && ctx->token_cursor->type != TOKEN_MOD) {
      break;
    }
    const expr_binary_type_t type = ctx->token_cursor->type == TOKEN_MULTIPLY
                                      ? EXPR_BINARY_TYPE_MUL
                                      : ctx->token_cursor->type == TOKEN_DIV
                                          ? EXPR_BINARY_TYPE_DIV
                                          : EXPR_BINARY_TYPE_MOD;
    ctx->token_cursor++;
    
    error = __parse_expr_unary(ctx, (expr_unary_t **) &right);
    if (error != ERROR_OK) {
      return error;
    }

    tmp = __parser_alloc(ctx, sizeof(expr_binary_t));
    if (tmp == NULL) {
      return ERROR_AST_TOO_BIG;
    }

    expr_binary_init((expr_binary_t *) tmp, type, left, right, start_token);
    left = tmp;
    if (!*binary) {
      *binary = (expr_binary_t *) tmp;
    }
  }

  if (ctx->token_cursor->type == TOKEN_EOF) {
    return ERROR_PARSE_UNEXCPECTED_END_OF_FILE;
  }

  if (!*binary) {
    *binary = (expr_binary_t *) left;
  }

  return ERROR_OK;
}

error_t __parse_expr_unary(parser_ctx_t *ctx, expr_unary_t **unary) {
  token_t *start_token = ctx->token_cursor;
  expr_t *tmp = NULL;
  error_t error
  ;

  if (ctx->token_cursor->type == TOKEN_MINUS || ctx->token_cursor->type == TOKEN_NOT) {
    const expr_unary_type_t type = ctx->token_cursor->type == TOKEN_MINUS ? EXPR_UNARY_TYPE_MINUS : EXPR_UNARY_TYPE_NOT;
    ctx->token_cursor++;
    error = __parse_expr_unary(ctx, unary);
    if (error != ERROR_OK) {
      return error;
    }

    *unary = __parser_alloc(ctx, sizeof(expr_unary_t));
    if (*unary == NULL) {
      return ERROR_AST_TOO_BIG;
    }

    expr_unary_init(*unary, type, tmp, start_token);
  } else {
    error = __parse_expr_primary(ctx, (expr_t **) unary);
    if (error != ERROR_OK) {
      return error;
    }
  }

  return ERROR_OK;
}

error_t __parse_expr_primary(parser_ctx_t *ctx, expr_t **expr) {
  token_t *start_token = ctx->token_cursor;
  error_t error;

  if (ctx->token_cursor->type == TOKEN_VARIABLE) {
    *expr = __parser_alloc(ctx, sizeof(expr_variable_t));
    if (*expr == NULL) {
      return ERROR_AST_TOO_BIG;
    }

    error = expr_variable_init((expr_variable_t *) *expr, ctx->token_cursor->value, start_token);
    if (error != ERROR_OK) {
      return error;
    }

    ctx->token_cursor++;
  } else if (ctx->token_cursor->type == TOKEN_NUMBER) {
    *expr = __parser_alloc(ctx, sizeof(expr_number_t));
    if (*expr == NULL) {
      return ERROR_AST_TOO_BIG;
    }

    const int16_t value = atoi(ctx->token_cursor->value);
    error = expr_number_init((expr_number_t *) *expr, value, start_token);
    if (error != ERROR_OK) {
      return error;
    }

    ctx->token_cursor++;
  } else if (ctx->token_cursor->type == TOKEN_PAROPEN) {
    ctx->token_cursor++;
    error = __parse_expr_assignment(ctx, expr);
    if (error != ERROR_OK) {
      return error;
    }

    if (ctx->token_cursor->type != TOKEN_PARCLOSE) {
      return ERROR_PARSE_UNEXPECTED_TOKEN;
    }

    ctx->token_cursor++;
  } else if (ctx->token_cursor->type == TOKEN_SCAN) {
    *expr = __parser_alloc(ctx, sizeof(expr_scan_t));
    if (*expr == NULL) {
      return ERROR_AST_TOO_BIG;
    }

    error = expr_scan_init((expr_scan_t *) *expr, start_token);
    if (error != ERROR_OK) {
      return error;
    }

    ctx->token_cursor++;
  } else if (ctx->token_cursor->type == TOKEN_PRINT) {
    *expr = __parser_alloc(ctx, sizeof(expr_print_t));
    if (*expr == NULL) {
      return ERROR_AST_TOO_BIG;
    }

    error = expr_print_init((expr_print_t *) *expr, start_token);
    if (error != ERROR_OK) {
      return error;
    }

    ctx->token_cursor++;
  } else {
    return ERROR_PARSE_UNEXPECTED_TOKEN;
  }

  return ERROR_OK;
}

error_t __parse_expr_lvalue(parser_ctx_t *ctx, expr_t **expr) {
  token_t *start_token = ctx->token_cursor;
  error_t error;

  if (ctx->token_cursor->type == TOKEN_VARIABLE) {
    *expr = __parser_alloc(ctx, sizeof(expr_variable_t));
    if (*expr == NULL) {
      return ERROR_AST_TOO_BIG;
    }

    error = expr_variable_init((expr_variable_t *) *expr, ctx->token_cursor->value, start_token);
    if (error != ERROR_OK) {
      return error;
    }

    ctx->token_cursor++;
  } else if (ctx->token_cursor->type == TOKEN_PRINT) {
    *expr = __parser_alloc(ctx, sizeof(expr_print_t));
    if (*expr == NULL) {
      return ERROR_AST_TOO_BIG;
    }

    error = expr_print_init((expr_print_t *) *expr, start_token);
    if (error != ERROR_OK) {
      return error;
    }

    ctx->token_cursor++;
  } else {
    return ERROR_PARSE_UNEXPECTED_TOKEN;
  }

  return ERROR_OK;
}

error_t __parse_expr_rvalue(parser_ctx_t *ctx, expr_t **expr) {
  return __parse_expr_assignment(ctx, expr);
}

error_t __parse_utils_root(parser_ctx_t *ctx, root_t **root) {
  *root = __parser_alloc(ctx, sizeof(root_t));
  if (*root == NULL) {
    return ERROR_AST_TOO_BIG;
  }

  error_t error = __parse_utils_program(ctx, &(*root)->program);
  if (error != ERROR_OK) {
    return error;
  }

  for (; ctx->token_cursor->type == TOKEN_SEMICOLON; ctx->token_cursor++) { }

  error = __parse_utils_variables(ctx, &(*root)->var);
  if (error != ERROR_OK) {
    return error;
  }

  for (; ctx->token_cursor->type == TOKEN_SEMICOLON; ctx->token_cursor++) { }

  error = __parse_stmt_block(ctx, &(*root)->block);
  if (error != ERROR_OK) {
    return error;
  }

  return ERROR_OK;
}

error_t __parse_utils_program(parser_ctx_t *ctx, program_t *program) {
  if (ctx->token_cursor->type != TOKEN_PROGRAM) {
    return ERROR_PARSE_UNEXPECTED_TOKEN;
  }
  ctx->token_cursor++;

  if (ctx->token_cursor->type != TOKEN_BAD_IDENTIFIER) {
    return ERROR_PARSE_UNEXPECTED_TOKEN;
  }

  program->name = ctx->token_cursor->value;
  ctx->token_cursor++;

  if (ctx->token_cursor->type != TOKEN_SEMICOLON) {
    return ERROR_PARSE_UNEXPECTED_TOKEN;
  }
  ctx->token_cursor++;

  return ERROR_OK;
}

error_t __parse_utils_variables(parser_ctx_t *ctx, var_t *variables) {
  size_t count;

  if (ctx->token_cursor->type != TOKEN_VAR) {
    return ERROR_PARSE_UNEXPECTED_TOKEN;
  }
  ctx->token_cursor++;

  for (count = 0; count < MAX_VARIABLES_COUNT; count++) {
    if (ctx->token_cursor->type == TOKEN_SEMICOLON) break;
    const error_t error = __parse_utils_variable(ctx, &variables->def[count]);
    if ((ctx->token_cursor++)->type == TOKEN_SEMICOLON) break;
    if (error != ERROR_OK) {
      return error;
    }
  }

  if (count == MAX_VARIABLES_COUNT) {
    return ERROR_PARSE_TOO_MUCH_VARIABLES;
  }

  return ERROR_OK;
}

error_t __parse_utils_variable(parser_ctx_t *ctx, var_def_t *variable) {
  variable->value = 0;
  variable->name = NULL;

  if (ctx->token_cursor->type != TOKEN_VARIABLE) {
    return ERROR_PARSE_UNEXPECTED_TOKEN;
  }

  variable->name = ctx->token_cursor->value;
  ctx->token_cursor++;

  if (ctx->token_cursor->type == TOKEN_COMMA || ctx->token_cursor->type == TOKEN_SEMICOLON) {
    return ERROR_OK;
  }

  if (ctx->token_cursor->type != TOKEN_ASSIGN) {
    return ERROR_PARSE_UNEXPECTED_TOKEN;
  }
  ctx->token_cursor++;

  if (ctx->token_cursor->type != TOKEN_NUMBER) {
    return ERROR_PARSE_UNEXPECTED_TOKEN;
  }

  variable->value = atoi(ctx->token_cursor->value);
  ctx->token_cursor++;

  if (ctx->token_cursor->type != TOKEN_COMMA && ctx->token_cursor->type != TOKEN_SEMICOLON) {
    return ERROR_PARSE_UNEXPECTED_TOKEN;
  }

  return ERROR_OK;
}

error_t __parse_stmt(parser_ctx_t *ctx, stmt_t **stmt) {
  error_t error;

  if (ctx->token_cursor->type == TOKEN_IF) {
    error = __parse_stmt_if(ctx, (stmt_if_t **) stmt);
  } else if (ctx->token_cursor->type == TOKEN_FOR) {
    error = __parse_stmt_for(ctx, (stmt_for_t **) stmt);
  } else if (ctx->token_cursor->type == TOKEN_GOTO) {
    error = __parse_stmt_goto(ctx, (stmt_goto_t **) stmt);
  } else if (ctx->token_cursor->type == TOKEN_BAD_IDENTIFIER) {
    error = __parse_stmt_label(ctx, (stmt_label_t **) stmt);
  } else {
    error = __parse_stmt_expr(ctx, (stmt_expr_t **) stmt);
  }

  return error;
}

error_t __parse_stmt_block(parser_ctx_t *ctx, stmt_block_t **block) {
  token_t *start_token = ctx->token_cursor;
  stmt_t *stmt = NULL, *prev = NULL;

  *block = __parser_alloc(ctx, sizeof(stmt_block_t));
  error_t error = stmt_block_init(*block, NULL, start_token);
  if (error != ERROR_OK) {
    return error;
  }

  if (ctx->token_cursor->type != TOKEN_START) {
    return ERROR_PARSE_UNEXPECTED_TOKEN;
  }
  ctx->token_cursor++;

  while (ctx->token_cursor->type != TOKEN_EOF) {
    if (ctx->token_cursor->type == TOKEN_FINISH) {
      break;
    }

    if (ctx->token_cursor->type == TOKEN_SEMICOLON) {
      ctx->token_cursor++;
      continue;
    }

    prev = stmt;
    error = __parse_stmt(ctx, &stmt);
    if (error != ERROR_OK) {
      return error;
    }

    if (prev) {
      prev->next = stmt;
    } else {
      (*block)->first = stmt;
    }
  }
  if (ctx->token_cursor->type == TOKEN_EOF) {
    return ERROR_PARSE_UNEXCPECTED_END_OF_FILE;
  }
  ctx->token_cursor++;

  return ERROR_OK;
}

error_t __parse_stmt_if(parser_ctx_t *ctx, stmt_if_t **stmt_if) {
  token_t *start_token = ctx->token_cursor;
  expr_t *condition_expression = NULL;
  stmt_goto_t *goto_statement = NULL;

  if (ctx->token_cursor->type != TOKEN_IF) {
    return ERROR_PARSE_UNEXPECTED_TOKEN;
  }
  ctx->token_cursor++;

  error_t error = __parse_expr_assignment(ctx, &condition_expression);
  if (error != ERROR_OK) {
    return error;
  }
  
  error = __parse_stmt_goto(ctx, &goto_statement);
  if (error != ERROR_OK) {
    return error;
  }

  *stmt_if = __parser_alloc(ctx, sizeof(stmt_if_t));
  if (*stmt_if == NULL) {
    return ERROR_AST_TOO_BIG;
  }
  stmt_if_init(*stmt_if, condition_expression, goto_statement, start_token);

  return ERROR_OK;
}

error_t __parse_stmt_for(parser_ctx_t *ctx, stmt_for_t **stmt_for) {
  token_t *start_token = ctx->token_cursor;
  char *variable = NULL;
  expr_t *init_expr = NULL;
  expr_t *to_expr = NULL;
  stmt_block_t *body_stmt = NULL;

  if (ctx->token_cursor->type != TOKEN_FOR) {
    return ERROR_PARSE_UNEXPECTED_TOKEN;
  }
  ctx->token_cursor++;

  if (ctx->token_cursor->type != TOKEN_VARIABLE) {
    return ERROR_PARSE_UNEXPECTED_TOKEN;
  }
  variable = (ctx->token_cursor++)->value;

  if (ctx->token_cursor->type != TOKEN_ASSIGN) {
    return ERROR_PARSE_UNEXPECTED_TOKEN;
  }
  ctx->token_cursor++;

  error_t error = __parse_expr_assignment(ctx, &init_expr);
  if (error != ERROR_OK) {
    return error;
  }

  if (ctx->token_cursor->type != TOKEN_TO) {
    return ERROR_PARSE_UNEXPECTED_TOKEN;
  }
  ctx->token_cursor++;

  error = __parse_expr_assignment(ctx, &to_expr);
  if (error != ERROR_OK) {
    return error;
  }
  
  error = __parse_stmt_block(ctx, &body_stmt);
  if (error != ERROR_OK) {
    return error;
  }

  if (ctx->token_cursor->type != TOKEN_NEXT) {
    return ERROR_PARSE_UNEXPECTED_TOKEN;
  }
  ctx->token_cursor++;

  *stmt_for = __parser_alloc(ctx, sizeof(stmt_for_t));
  if (*stmt_for == NULL) {
    return ERROR_AST_TOO_BIG;
  }
  stmt_for_init(*stmt_for, variable, init_expr, to_expr, body_stmt, start_token);

  return ERROR_OK;
}

error_t __parse_stmt_goto(parser_ctx_t *ctx, stmt_goto_t **stmt_goto) {
  token_t *start_token = ctx->token_cursor;

  if (ctx->token_cursor->type != TOKEN_GOTO) {
    return ERROR_PARSE_UNEXPECTED_TOKEN;
  }
  ctx->token_cursor++;

  if (ctx->token_cursor->type != TOKEN_BAD_IDENTIFIER) {
    return ERROR_PARSE_UNEXPECTED_TOKEN;
  }

  *stmt_goto = __parser_alloc(ctx, sizeof(stmt_goto_t));
  if (*stmt_goto == NULL) {
    return ERROR_AST_TOO_BIG;
  }
  stmt_goto_init(*stmt_goto, ctx->token_cursor->value, start_token);
  ctx->token_cursor++;

  return ERROR_OK;
}

error_t __parse_stmt_label(parser_ctx_t *ctx, stmt_label_t **stmt_label) {
  token_t *start_token = ctx->token_cursor;
  char *label = NULL;

  if (ctx->token_cursor->type != TOKEN_BAD_IDENTIFIER) {
    return ERROR_PARSE_UNEXPECTED_TOKEN;
  }
  label = (ctx->token_cursor++)->value;

  if (ctx->token_cursor->type != TOKEN_COLON) {
    return ERROR_PARSE_UNEXPECTED_TOKEN;
  }
  ctx->token_cursor++;

  *stmt_label = __parser_alloc(ctx, sizeof(stmt_label_t));
  if (*stmt_label == NULL) {
    return ERROR_AST_TOO_BIG;
  }
  stmt_label_init(*stmt_label, label, start_token);

  return ERROR_OK;
}

error_t __parse_stmt_expr(parser_ctx_t *ctx, stmt_expr_t **stmt_expr) {
  token_t *start_token = ctx->token_cursor;
  expr_t *expr = NULL;

  const error_t error = __parse_expr_assignment(ctx, &expr);
  if (error != ERROR_OK) {
    return error;
  }

  if (ctx->token_cursor->type != TOKEN_SEMICOLON) {
    return ERROR_PARSE_UNEXPECTED_TOKEN;
  }
  ctx->token_cursor++;

  *stmt_expr = __parser_alloc(ctx, sizeof(stmt_expr_t));
  if (*stmt_expr == NULL) {
    return ERROR_AST_TOO_BIG;
  }
  stmt_expr_init(*stmt_expr, expr, start_token);

  return ERROR_OK;
}