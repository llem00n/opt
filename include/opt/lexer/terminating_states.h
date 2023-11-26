// *************************************************************************
// terminating_states.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 10/23/23
// *************************************************************************

#ifndef OPT_TERMINATING_STATES_H
#define OPT_TERMINATING_STATES_H

/**
 * @brief Defines an enumeration of terminating states for lexical analyzation
 */
typedef enum {
  TSTATE_BAD_IDENTIFIER = 2,
  TSTATE_VARIABLE = 9,
  TSTATE_DIGIT = 11,
  TSTATE_WHITESPACE = 13,
  TSTATE_OTHER = 15,
  TSTATE_COMMENT = 18,
  TSTATE_PLUSPLUS = 21,
  TSTATE_MINUSMINUS = 24,
  TSTATE_ASTERISKASTERISK = 27,
  TSTATE_EQUALS = 29,
  TSTATE_NOT = 31,
  TSTATE_LESS = 33,
  TSTATE_GREATER = 35,
  TSTATE_AND = 37,
  TSTATE_OR = 39,
  TSTATE_PAROPEN = 41,
  TSTATE_PARCLOSE = 43,
  TSTATE_PROGRAM = 51,
  TSTATE_PRINT = 55,
  TSTATE_VAR = 59,
  TSTATE_START = 65,
  TSTATE_SCAN = 69,
  TSTATE_FINISH = 76,
  TSTATE_FOR = 79,
  TSTATE_TO = 82,
  TSTATE_NEXT = 87,
  TSTATE_IF = 90,
  TSTATE_GOTO = 95,
  TSTATE_DIV = 99,
  TSTATE_MOD = 103,
  TSTATE_COLON = 105,
  TSTATE_ASSIGN = 108,
  TSTATE_NOT_EQUALS = 110,
  TSTATE_SEMICOLON = 112,
  TSTATE_COMMA = 114,
} terminating_states_t;

#endif //OPT_TERMINATING_STATES_H
