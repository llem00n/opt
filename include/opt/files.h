// *************************************************************************
// files.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 10/30/23
// *************************************************************************

#ifndef OPT_FILES_H
#define OPT_FILES_H

#include <stdio.h>
#include <opt/err.h>

typedef struct {
  FILE *input;
  FILE *tokens;
  FILE *errors;
} files_context_t;

error_t open_files(files_context_t *fctx, char *input_file_name, char *tokens_file_name, char *errors_file_name);
void close_files(files_context_t *fctx);

#endif //OPT_FILES_H
