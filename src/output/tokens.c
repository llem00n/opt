// *************************************************************************
// tokens.c
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 10/30/23
// *************************************************************************

#include <opt/output/tokens.h>
#include <opt/output/utils/token_type_str.h>


void print_tokens(token_t tokens[], FILE *file) {
  token_t *token = tokens;

  fprintf(file, "|------|--------------------|------------------------------|\n");
  fprintf(file, "| %-4s | %-18s | %-28s |\n", "Line", "Value", "Type");
  fprintf(file, "|------|--------------------|------------------------------|\n");
  for (; token->type != TOKEN_EOF; token++) {
    fprintf(file, "| %-4d | %-18s | %-28s |\n", token->line, token->value, token_type_str(token->type));
  }
  fprintf(file, "|------|--------------------|------------------------------|\n");
}