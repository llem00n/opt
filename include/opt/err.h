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
} error_t;

#endif //OPT_ERR_H
