// *************************************************************************
// main.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 9/25/2023
// *************************************************************************

#include <opt/lexer/lexer.h>
#include <opt/files.h>
#include <opt/output/tokens.h>
#include <stdio.h>

#define MAX_TOKENS_LENGTH 500

int main() {
  files_context_t fctx;
  token_t tokens[MAX_TOKENS_LENGTH];
  error_t error;

  error = open_files(&fctx, "input.txt", "tokens.txt", "errors.txt");
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

  close_files(&fctx);
  return 0;
}
