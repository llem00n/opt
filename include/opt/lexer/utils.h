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

bool is_terminating_state(state_t state);
token_type_t get_token_type(state_t state);
lexer_characters_t get_character_type(int32_t c);
token_t create_token(char *token_value, state_t state, uint32_t line);

#ifdef _WIN32
#define strncpy(dest, src, size) strncpy_s(dest, size, src)
#endif //_WIN32

#endif //OPT_UTILS_H
