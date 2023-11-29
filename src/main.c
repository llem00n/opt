// *************************************************************************
// main.c
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 9/25/2023
// *************************************************************************

#include <opt/lexer/lexer.h>
#include <opt/files.h>
#include <opt/output/tokens.h>
#include <opt/precompile_config.h>
#include <opt/parser/parser.h>
#include <stdio.h>

int main() {
  files_context_t fctx;
  token_t tokens[MAX_TOKENS_LENGTH];
  int8_t ast_bytes[MAX_AST_BYTES_LENGTH];
  parser_ctx_t pctx;

  error_t error = open_files(&fctx, "input.txt", "tokens.txt", "errors.txt");
  if (error != ERROR_OK) {
    fprintf(stderr, "There was a problem opening files...\n");
    close_files(&fctx);
    return 1;
  }

  error = get_tokens(fctx.input, tokens, MAX_TOKENS_LENGTH);
  if (error == ERROR_TOO_MUCH_TOKENS) {
    fprintf(stderr, "The input file is too big\n");
    close_files(&fctx);
    return 1;
  } else if (error == ERROR_TOKEN_TOO_LONG) {
    fprintf(stderr, "The input file contains a token that is too long\n");
    close_files(&fctx);
    return 1;
  }

  print_tokens(tokens, fctx.tokens);

  error = parser_ctx_init(&pctx, tokens, ast_bytes, MAX_AST_BYTES_LENGTH);
  if (error != ERROR_OK) {
    fprintf(stderr, "There was a problem initializing parser context...\n");
    close_files(&fctx);
    return 1;
  }

  error = parse(&pctx);
  if (error != ERROR_OK) {
    fprintf(stderr, "There was a problem parsing ast... [%s] at line %d\n", get_error_message(error), pctx.token_cursor->line);
    close_files(&fctx);
    return 1;
  }

  close_files(&fctx);
  return 0;
}