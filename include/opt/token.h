// *************************************************************************
// token.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 9/25/2023
// *************************************************************************

#ifndef SRC_TOKEN_H
#define SRC_TOKEN_H

#include <stdint.h>

/**
 * Defines different types of tokens
 */
typedef enum {
  TOKEN_BAD_IDENTIFIER,
  TOKEN_COMMENT,
  TOKEN_VARIABLE,
  TOKEN_NUMBER,
  TOKEN_OTHER,
  TOKEN_DIV,
  TOKEN_FOR,
  TOKEN_GOTO,
  TOKEN_IF,
  TOKEN_MOD,
  TOKEN_NEXT,
  TOKEN_PRINT,
  TOKEN_SCAN,
  TOKEN_START,
  TOKEN_TO,
  TOKEN_VAR,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_MULTIPLY,
  TOKEN_EQUALS,
  TOKEN_ASSIGN,
  TOKEN_NOT_EQUALS,
  TOKEN_NOT,
  TOKEN_LESS,
  TOKEN_GREATER,
  TOKEN_AND,
  TOKEN_OR,
  TOKEN_PAROPEN,
  TOKEN_PARCLOSE,
  TOKEN_WHITESPACE,
  TOKEN_EOF,
  TOKEN_PROGRAM,
  TOKEN_COLON,
  TOKEN_SEMICOLON,
  TOKEN_COMMA,
  TOKEN_FINISH,
  TOKEN_LENGTH_,
} token_type_t;

#define SELF_CONTAINING_TOKENS_START TOKEN_DIV

/**
 * Defines the type for token, returned by lexer
 */
typedef struct {
  char *value;
  token_type_t type;
  uint32_t line;
} token_t;

#endif //SRC_TOKEN_H
