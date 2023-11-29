// *************************************************************************
// err.c
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/29/23
// *************************************************************************
#include <opt/err.h>

const char *get_error_message(const error_t error_code) {
  switch (error_code) {
    case ERROR_OK:
      return "ERROR_OK";
    case ERROR_AST_TOO_BIG:
      return "ERROR_AST_TOO_BIG";
    case ERROR_BAD_PARAMETER:
      return "ERROR_BAD_PARAMETER";
    case ERROR_CANT_OPEN_FILE:
      return "ERROR_CANT_OPEN_FILE";
    case ERROR_PARSE_TOO_MUCH_VARIABLES:
      return "ERROR_PARSE_TOO_MUCH_VARIABLES";
    case ERROR_PARSE_UNEXPECTED_TOKEN:
      return "ERROR_PARSE_UNEXPECTED_TOKEN";
    case ERROR_PARSE_UNEXCPECTED_END_OF_FILE:
      return "ERROR_PARSE_UNEXCPECTED_END_OF_FILE";
    case ERROR_PARSE_UNKNOWN_ERROR:
      return "ERROR_PARSE_UNKNOWN_ERROR";
    case ERROR_TOKEN_TOO_LONG:
      return "ERROR_TOKEN_TOO_LONG";
    case ERROR_TOO_MUCH_TOKENS:
      return "ERROR_TOO_MUCH_TOKENS";
    default:
      return "UNKNOWN_ERROR";
  }
}
