// *************************************************************************
// token.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 9/25/2023
// *************************************************************************

#ifndef SRC_TOKEN_H
#define SRC_TOKEN_H


/**
 * Defines different types of tokens
 */
typedef enum {
  TOKEN_IDENTIFIER,
  TOKEN_NUMBER,
  TOKEN_STRING,
  TOKEN_DO,
  TOKEN_ELSE,
  TOKEN_GOTO,
  TOKEN_IF,
  TOKEN_THEN,
  TOKEN_REPEAT,
  TOKEN_TO,
  TOKEN_UNTIL,
  TOKEN_NEXT,
  TOKEN_WHILE,
  TOKEN_PARENTHESES_OPEN,
  TOKEN_PARENTHESES_CLOSED,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_MULTIPLY,
  TOKEN_DIVIDE,
  TOKEN_NOT,
  TOKEN_MOD,
  TOKEN_ASSIGN,
  TOKEN_EQUALS,
  TOKEN_LESS,
  TOKEN_LESS_OR_EQUAL,
  TOKEN_GREATER,
  TOKEN_GREATER_OR_EQUAL,
  TOKEN_NOT_EQUALS,
  TOKEN_SEMICOLON,
  TOKEN_EOF,
  TOKEN_ERROR,
  __TOKEN_LENGTH,
} token_type_t;

#define SELF_CONTAINING_TOKENS_START TOKEN_IF

/**
 * Defines the type for token, returned by lexer
 */
typedef struct {
  char *value;
  token_type_t type;
  uint32_t line;
} token_t;

#endif //SRC_TOKEN_H
