// *************************************************************************
// token_type_str.c
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 10/30/23
// *************************************************************************

#include <opt/output/utils/token_type_str.h>

const char *token_type_str(token_type_t token_type) {
  switch (token_type) {
    case TOKEN_BAD_IDENTIFIER:
      return "BAD_IDENTIFIER";
    case TOKEN_COMMENT:
      return "COMMENT";
    case TOKEN_VARIABLE:
      return "VARIABLE";
    case TOKEN_NUMBER:
      return "NUMBER";
    case TOKEN_OTHER:
      return "OTHER";
    case TOKEN_DIV:
      return "DIV";
    case TOKEN_FOR:
      return "FOR";
    case TOKEN_GOTO:
      return "GOTO";
    case TOKEN_IF:
      return "IF";
    case TOKEN_MOD:
      return "MOD";
    case TOKEN_NEXT:
      return "NEXT";
    case TOKEN_PRINT:
      return "PRINT";
    case TOKEN_SCAN:
      return "SCAN";
    case TOKEN_START:
      return "START";
    case TOKEN_TO:
      return "TO";
    case TOKEN_VAR:
      return "VAR";
    case TOKEN_PLUS:
      return "PLUS";
    case TOKEN_MINUS:
      return "MINUS";
    case TOKEN_MULTIPLY:
      return "MULTIPLY";
    case TOKEN_EQUALS:
      return "EQUALS";
    case TOKEN_ASSIGN:
      return "ASSIGN";
    case TOKEN_NOT_EQUALS:
      return "NOT EQUALS";
    case TOKEN_NOT:
      return "NOT";
    case TOKEN_LESS:
      return "LESS";
    case TOKEN_GREATER:
      return "GREATER";
    case TOKEN_AND:
      return "AND";
    case TOKEN_OR:
      return "OR";
    case TOKEN_PAROPEN:
      return "PAROPEN";
    case TOKEN_PARCLOSE:
      return "PARCLOSE";
    case TOKEN_WHITESPACE:
      return "WHITESPACE";
    case TOKEN_EOF:
      return "EOF";
    case TOKEN_PROGRAM:
      return "PROGRAM";
    case TOKEN_COLON:
      return "COLON";
    case TOKEN_SEMICOLON:
      return "SEMICOLON";
    case TOKEN_COMMA:
      return "COMMA";
    case TOKEN_FINISH:
      return "FINISH";
    default:
      return "UNKNOWN";
  }
}
