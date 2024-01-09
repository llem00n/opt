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
#include <opt/translator/translator.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  files_context_t fctx;
  token_t tokens[MAX_TOKENS_LENGTH];
  int8_t ast_bytes[MAX_AST_BYTES_LENGTH];
  parser_ctx_t pctx;
  translator_ctx_t tctx;

  error_t error = open_files(&fctx, "program.p17", "tokens.txt", "errors.txt", "program.asm");
  if (error != ERROR_OK) {
    fprintf(fctx.errors, "There was a problem opening files...\n");
    close_files(&fctx);
    return 1;
  }

  error = get_tokens(fctx.input, tokens, MAX_TOKENS_LENGTH);
  if (error == ERROR_TOO_MUCH_TOKENS) {
    fprintf(fctx.errors, "The input file is too big\n");
    close_files(&fctx);
    return 1;
  } else if (error == ERROR_TOKEN_TOO_LONG) {
    fprintf(fctx.errors, "The input file contains a token that is too long\n");
    close_files(&fctx);
    return 1;
  }

  print_tokens(tokens, fctx.tokens);

  uint8_t has_errors = 0;
  for (const token_t *cursor = tokens; cursor->type != TOKEN_EOF; cursor++) {
    if (cursor->type == TOKEN_OTHER) {
      fprintf(fctx.errors, "Unexpected token \"%s\" at line %d\n", cursor->value, cursor->line);
      has_errors = 1;
    }
  }
  if (has_errors) {
    close_files(&fctx);
    return 1;
  }

  error = parser_ctx_init(&pctx, tokens, ast_bytes, MAX_AST_BYTES_LENGTH, &fctx);
  if (error != ERROR_OK) {
    fprintf(fctx.errors, "There was a problem initializing parser context...\n");
    close_files(&fctx);
    return 1;
  }

  error = parse(&pctx);
  if (error != ERROR_OK) {
    fprintf(fctx.errors, "There was a problem parsing ast... [%s] at line %d\n", get_error_message(error), pctx.token_cursor->line);
    close_files(&fctx);
    return 1;
  }  else if (pctx.error_count > 0) {
    fprintf(stderr, "There were %d errors while parsing ast...\n", pctx.error_count);
    close_files(&fctx);
    return 1;
  }

  error = translator_ctx_init(&tctx, (root_t *) pctx.root, &fctx, PLATFORM_WIN32);
  if (error != ERROR_OK) {
    fprintf(fctx.errors, "There was a problem initializing translator context...\n");
    close_files(&fctx);
    return 1;
  }

  error = translate(&tctx);
  if (error != ERROR_OK) {
    fprintf(fctx.errors, "There was a problem translating ast... [%s] at line %d\n", get_error_message(error), pctx.token_cursor->line);
    close_files(&fctx);
    return 1;
  }

  for (token_t *cursor = tokens; cursor->type != TOKEN_EOF; cursor++) {
    if (cursor->value) {
      free(cursor->value);
      cursor->value = NULL;
    }
  }

  close_files(&fctx);
  return 0;
}