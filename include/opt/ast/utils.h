// *************************************************************************
// utils.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/27/2023
// *************************************************************************
#ifndef OPT_AST_UTILS_H
#define OPT_AST_UTILS_H

#include <opt/precompile_config.h>
#include <opt/ast/stmt/block.h>
#include <stdint.h>

/**
 * @brief Defines program header statement
*/
typedef struct program {
  char *name;
} program_t;

/**
 * @brief Defines variable definition statement
*/
typedef struct var_def {
  char *name;
  int16_t value;
} var_def_t;

/**
 * @brief Defines variables definition statement
*/
typedef struct var {
  var_def_t def[MAX_VARIABLES_COUNT];
} var_t;

typedef struct root {
  program_t program;
  var_t var;
  stmt_block_t *block;
} root_t;

#endif //OPT_AST_UTILS_H