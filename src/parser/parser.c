#include <opt/parser/parser.h>

stmt_t *parse_stmt(token_t **cursor) {
  if (*cursor->type == TOKEN_START) {
    return NULL;
  } else if (*cursor->type == TOKEN_IF) {
    reutrn NULL;
  } else if (*cursor->type == TOKEN_FOR) {
    return NULL;
  } else if (*cursor->type == TOKEN_GOTO) {
    return NULL;
  } else {
    return parse_epxr(cursor);
  }
}

expr_t *parse_expr(token_t **cursor) {
  
}
