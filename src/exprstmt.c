// *************************************************************************
// exprstmt.c
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/29/23
// *************************************************************************

#include <opt/ast/ast.h>

error_t expr_init(expr_t *expr, expr_type_t type, token_t *start_token) {
  if (expr == NULL) {
    return ERROR_BAD_PARAMETER;
  }
  expr->type = type;
  expr->start_token = start_token;
  return ERROR_OK;
}

expr_type_t get_expr_type(const expr_t* expr) {
  return expr->type;
}

token_t *get_expr_start_token(const expr_t* expr) {
  return expr->start_token;
}

error_t expr_assign_init(expr_assign_t *expr_assign, expr_t *left, expr_t *right, token_t *start_token) {
  if (expr_assign == NULL) {
    return ERROR_BAD_PARAMETER;
  }
  expr_binary_init((expr_binary_t *) expr_assign, EXPR_BINARY_TYPE_ASSIGN, left, right, start_token);
  return ERROR_OK;
}

error_t expr_binary_init(expr_binary_t *expr_binary, expr_binary_type_t type, expr_t *left, expr_t *right, token_t *start_token) {
  if (expr_binary == NULL) {
    return ERROR_BAD_PARAMETER;
  }
  expr_init((expr_t *) expr_binary, EXPR_RVALUE | EXPR_BINARY, start_token);
  expr_binary->type = type;
  expr_binary->left = left;
  expr_binary->right = right;
  return ERROR_OK;
}

expr_binary_type_t get_expr_binary_type(const expr_binary_t* expr_binary) {
  return expr_binary->type;
}

expr_t *get_expr_binary_left(const expr_binary_t *expr_binary) {
  return expr_binary->left;
}

expr_t *get_expr_binary_right(const expr_binary_t *expr_binary) {
  return expr_binary->right;
}

error_t expr_number_init(expr_number_t *expr_number, const int16_t value, token_t *start_token) {
  if (expr_number == NULL) {
    return ERROR_BAD_PARAMETER;
  }
  expr_init((expr_t *) expr_number, EXPR_RVALUE | EXPR_NUMBER, start_token);
  expr_number->value = value;
  return ERROR_OK;
}

int16_t get_expr_number_value(const expr_number_t *expr_number) {
  return expr_number->value;
}

error_t expr_print_init(expr_print_t *expr_print, token_t *start_token) {
  if (expr_print == NULL) {
    return ERROR_BAD_PARAMETER;
  }
  expr_init((expr_t *) expr_print, EXPR_OUTPUT | EXPR_LVALUE | EXPR_RVALUE, start_token);
  return ERROR_OK;
}

error_t expr_scan_init(expr_scan_t *expr_scan, token_t *start_token) {
  if (expr_scan == NULL) {
    return ERROR_BAD_PARAMETER;
  }
  expr_init((expr_t *) expr_scan, EXPR_INPUT | EXPR_RVALUE, start_token);
  return ERROR_OK;
}

error_t expr_unary_init(expr_unary_t *expr_unary, const expr_unary_type_t type, expr_t *expr, token_t *start_token) {
  if (expr_unary == NULL) {
    return ERROR_BAD_PARAMETER;
  }
  expr_init((expr_t *) expr_unary, EXPR_RVALUE | EXPR_UNARY, start_token);
  expr_unary->type = type;
  expr_unary->expr = expr;
  return ERROR_OK;
}

expr_unary_type_t get_expr_unary_type(const expr_unary_t *expr_unary) {
  return expr_unary->type;
}

expr_t *get_expr_unary_expr(const expr_unary_t *expr_unary) {
  return expr_unary->expr;
}

error_t expr_variable_init(expr_variable_t *expr_variable, char *name, token_t *start_token) {
  if (expr_variable == NULL) {
    return ERROR_BAD_PARAMETER;
  }
  expr_init((expr_t *) expr_variable, EXPR_LVALUE | EXPR_RVALUE | EXPR_VARIABLE, start_token);
  expr_variable->name = name;
  return ERROR_OK;
}

char *get_expr_variable_name(const expr_variable_t *expr_variable) {
  return expr_variable->name;
}

error_t stmt_init(stmt_t *stmt, const stmt_type_t type, token_t *start_token, stmt_t *next) {
  if (stmt == NULL) {
    return ERROR_BAD_PARAMETER;
  }
  stmt->type = type;
  stmt->start_token = start_token;
  stmt->next = next;
  return ERROR_OK;
}

stmt_type_t get_stmt_type(const stmt_t *stmt) {
  return stmt->type;
}

token_t *get_stmt_start_token(const stmt_t *stmt) {
  return stmt->start_token;
}

stmt_t *get_stmt_next(const stmt_t *stmt) {
  return stmt->next;
}

error_t stmt_block_init(stmt_block_t *stmt_block, stmt_t *first, token_t *start_token) {
  if (stmt_block == NULL) {
    return ERROR_BAD_PARAMETER;
  }
  stmt_init((stmt_t *) stmt_block, STMT_BLOCK, start_token, NULL);
  stmt_block->first = first;
  return ERROR_OK;
}

stmt_t **get_stmt_block_first(stmt_block_t *stmt_block) {
  return &stmt_block->first;
}

error_t stmt_expr_init(stmt_expr_t *stmt_expr, expr_t *expr, token_t *start_token) {
  if (stmt_expr == NULL) {
    return ERROR_BAD_PARAMETER;
  }
  stmt_init((stmt_t *) stmt_expr, STMT_EXPR, start_token, NULL);
  stmt_expr->expr = expr;
  return ERROR_OK;
}

expr_t *get_stmt_expr_expr(const stmt_expr_t *stmt_expr) {
  return stmt_expr->expr;
}

error_t stmt_for_init(stmt_for_t *stmt_for, char *variable, expr_t *init_expr, expr_t *to_expr, stmt_block_t *body_stmt, token_t *start_token) {
  if (stmt_for == NULL) {
    return ERROR_BAD_PARAMETER;
  }
  stmt_init((stmt_t *) stmt_for, STMT_FOR, start_token, NULL);
  stmt_for->variable = variable;
  stmt_for->init_expr = init_expr;
  stmt_for->to_expr = to_expr;
  stmt_for->body_stmt = body_stmt;
  return ERROR_OK;
}

char *get_stmt_for_variable(const stmt_for_t *stmt_for) {
  return stmt_for->variable;
}

expr_t *get_stmt_for_init_expr(const stmt_for_t *stmt_for) {
  return stmt_for->init_expr;
}

expr_t *get_stmt_for_to_expr(const stmt_for_t *stmt_for) {
  return stmt_for->to_expr;
}

stmt_block_t *get_stmt_for_body_stmt(const stmt_for_t *stmt_for) {
  return stmt_for->body_stmt;
}

error_t stmt_goto_init(stmt_goto_t *stmt_goto, char *label, token_t *start_token) {
  if (stmt_goto == NULL) {
    return ERROR_BAD_PARAMETER;
  }
  stmt_init((stmt_t *) stmt_goto, STMT_GOTO, start_token, NULL);
  stmt_goto->label = label;
  return ERROR_OK;
}

char *get_stmt_goto_label(const stmt_goto_t *stmt_goto) {
  return stmt_goto->label;
}

error_t stmt_if_init(stmt_if_t *stmt_if, expr_t *cond_expr, stmt_goto_t *goto_stmt, token_t *start_token) {
  if (stmt_if == NULL) {
    return ERROR_BAD_PARAMETER;
  }
  stmt_init((stmt_t *) stmt_if, STMT_IF, start_token, NULL);
  stmt_if->cond_expr = cond_expr;
  stmt_if->goto_stmt = goto_stmt;
  return ERROR_OK;
}

expr_t *get_stmt_if_cond_expr(const stmt_if_t *stmt_if) {
  return stmt_if->cond_expr;
}

stmt_goto_t *get_stmt_if_goto_stmt(const stmt_if_t *stmt_if) {
  return stmt_if->goto_stmt;
}

error_t stmt_label_init(stmt_label_t *stmt_label, char *name, token_t *start_token) {
  if (stmt_label == NULL) {
    return ERROR_BAD_PARAMETER;
  }
  stmt_init((stmt_t *) stmt_label, STMT_LABEL, start_token, NULL);
  stmt_label->name = name;
  return ERROR_OK;
}