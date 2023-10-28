// *************************************************************************
// table.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 9/25/2023
// *************************************************************************

#ifndef OPT_LEXER_TABLE_H
#define OPT_LEXER_TABLE_H

#include <stdint.h>
#include "char_types.h"


typedef uint16_t state_t;

/**
 * Defines a transition table for lexical analyzer
 */
extern uint16_t LEXER_TABLE[][CHAR_LENGTH_];

#endif //OPT_LEXER_TABLE_H
