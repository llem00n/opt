// *************************************************************************
// terminating_states.c
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 10/23/23
// *************************************************************************

#include "opt/lexer/utils.h"
#include "opt/lexer/terminating_states.h"

bool is_terminating_state(state_t state) {
  bool result = false;
  switch (state) {
    case TSTATE_BAD_IDENTIFIER:
    case TSTATE_VARIABLE:
    case TSTATE_DIGIT:
    case TSTATE_WHITESPACE:
    case TSTATE_OTHER:
    case TSTATE_COMMENT:
    case TSTATE_PLUSPLUS:
    case TSTATE_MINUSMINUS:
    case TSTATE_ASTERISKASTERISK:
    case TSTATE_EQUALS:
    case TSTATE_NOT:
    case TSTATE_LESS:
    case TSTATE_GREATER:
    case TSTATE_AND:
    case TSTATE_OR:
    case TSTATE_PAROPEN:
    case TSTATE_PARCLOSE:
    case TSTATE_PROGRAM:
    case TSTATE_PRINT:
    case TSTATE_VAR:
    case TSTATE_START:
    case TSTATE_SCAN:
    case TSTATE_FINISH:
    case TSTATE_FOR:
    case TSTATE_TO:
    case TSTATE_NEXT:
    case TSTATE_IF:
    case TSTATE_GOTO:
    case TSTATE_DIV:
    case TSTATE_MOD:
    case TSTATE_COLON:
    case TSTATE_ASSIGN:
    case TSTATE_NOT_EQUALS:
    case TSTATE_SEMICOLON:
    case TSTATE_COMMA:
      result = true;
      break;
    default:
      result = false;
  }

  return result;
}