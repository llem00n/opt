// *************************************************************************
// err.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 9/26/2023
// *************************************************************************

#ifndef OPT_ERR_H
#define OPT_ERR_H

/**
 * @brief Defines error codes
 */
typedef enum {
  ERROR_OK,
  ERROR_TOKEN_TOO_LONG,
  ERROR_TOO_MUCH_TOKENS,
  ERROR_CANT_OPEN_FILE,
  ERROR_BAD_PARAMETER,
  ERROR_AST_TOO_BIG,
  ERROR_PARSE_UNEXPECTED_TOKEN,
  ERROR_PARSE_UNKNOWN_ERROR,
  ERROR_PARSE_TOO_MUCH_VARIABLES,
  ERROR_PARSE_UNEXCPECTED_END_OF_FILE,
  ERROR_PARSE_UNDECLARED_VARIABLE,
  ERROR_TRANSLATOR_UNEXPECTED_NODE,
  ERROR_TRANSLATOR_BAD_PLATFORM,
} error_t;

/**
 * @brief Returns error message by error code
 * @param error_code Error code
 * @return Error message
 */
const char *get_error_message(const error_t error_code);

#endif //OPT_ERR_H
