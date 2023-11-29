// *************************************************************************
// utils.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 10/23/2023
// *************************************************************************

#ifndef OPT_UTILS_H
#define OPT_UTILS_H

#include <stdbool.h>
#include "opt/lexer/table.h"
#include "opt/token.h"

/**
 * @brief Defines the state is terminating or not
 * @param state - state to check
 * @return true if state is terminating, false otherwise
 */
bool is_terminating_state(state_t state);

/**
 * @brief Returns the token type by state
 * @param state - state to check
 * @return token type
 */
token_type_t get_token_type(state_t state);

/**
 * @brief Returns the character type
 * @param c - character to check
 * @return character type
 */
lexer_characters_t get_character_type(int32_t c);

/**
 * @brief Creates a token
 * @param token_value - token value
 * @param state - token state
 * @param line - token line
 * @return token
 */
token_t create_token(const char *token_value, state_t state, uint32_t line);

#ifdef _WIN32
#define strncpy(dest, src, size) strncpy_s(dest, size, src)
#endif //_WIN32

#endif //OPT_UTILS_H
