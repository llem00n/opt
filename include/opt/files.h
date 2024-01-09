// *************************************************************************
// files.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 10/30/23
// *************************************************************************

#ifndef OPT_FILES_H
#define OPT_FILES_H

#include <stdio.h>
#include <opt/err.h>

/**
 * @brief Defines a context for files
 */
typedef struct {
  FILE *input;
  FILE *tokens;
  FILE *errors;
  FILE *aasm;
} files_context_t;

/**
 * @brief Opens files
 * @param fctx - context for files
 * @param input_file_name - name of input file
 * @param tokens_file_name - name of tokens file
 * @param errors_file_name - name of errors file
 * @param asm_file_name - name of asm file
 * @return error code
 */
error_t open_files(files_context_t *fctx, char *input_file_name, char *tokens_file_name, char *errors_file_name, char *asm_file_name);

/**
 * @brief Closes files
 * @param fctx - context for files
 */
void close_files(const files_context_t *fctx);

#endif //OPT_FILES_H
