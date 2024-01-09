// *************************************************************************
// files.c
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 10/30/23
// *************************************************************************

#include <opt/files.h>
#include "opt/err.h"

error_t open_files(files_context_t *fctx, char *input_file_name, char *tokens_file_name, char *errors_file_name, char *asm_file_name) {
  error_t result = ERROR_OK;
  if (!fctx || !input_file_name || !tokens_file_name || !errors_file_name || !asm_file_name) {
    result = ERROR_BAD_PARAMETER;
    return result;
  }

  *fctx = (files_context_t) {
    .input = fopen(input_file_name, "r"),
    .tokens = fopen(tokens_file_name, "w"),
    .errors = fopen(errors_file_name, "w"),
    .aasm = fopen(asm_file_name, "w"),
  };

  if (fctx->input == NULL) {
    fprintf(stderr, "Can't open input file: %s\n", input_file_name);
    result = ERROR_CANT_OPEN_FILE;
  }

  if (fctx->tokens == NULL) {
    fprintf(stderr, "Can't open tokens file: %s\n", tokens_file_name);
    result = ERROR_CANT_OPEN_FILE;
  }

  if (fctx->errors == NULL) {
    fprintf(stderr, "Can't open errors file: %s\n", errors_file_name);
    result = ERROR_CANT_OPEN_FILE;
  }

  if (fctx->aasm == NULL) {
    fprintf(stderr, "Can't open asm file: %s\n", asm_file_name);
    result = ERROR_CANT_OPEN_FILE;
  }

  if (result != ERROR_OK) {
    if (fctx->input) fclose(fctx->input);
    if (fctx->tokens) fclose(fctx->tokens);
    if (fctx->errors) fclose(fctx->errors);
    if (fctx->aasm) fclose(fctx->aasm);
  }

  return result;
}

void close_files(const files_context_t *fctx) {
  if (!fctx) return;

  if (fctx->input) fclose(fctx->input);
  if (fctx->tokens) fclose(fctx->tokens);
  if (fctx->errors) fclose(fctx->errors);
}