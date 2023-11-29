// *************************************************************************
// token_type.c
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 10/23/23
// *************************************************************************

#include "opt/token.h"
#include "opt/lexer/utils.h"
#include "opt/lexer/terminating_states.h"

token_type_t get_token_type(state_t state) {
  token_type_t token_type = TOKEN_LENGTH_;

  switch (state) {
    case TSTATE_BAD_IDENTIFIER:
      token_type = TOKEN_BAD_IDENTIFIER;
      break;
    case TSTATE_VARIABLE:
      token_type = TOKEN_VARIABLE;
      break;
    case TSTATE_DIGIT:
      token_type = TOKEN_NUMBER;
      break;
    case TSTATE_WHITESPACE:
      token_type = TOKEN_WHITESPACE;
      break;
    case TSTATE_OTHER:
      token_type = TOKEN_OTHER;
      break;
    case TSTATE_COMMENT:
      token_type = TOKEN_COMMENT;
      break;
    case TSTATE_PLUSPLUS:
      token_type = TOKEN_PLUS;
      break;
    case TSTATE_MINUSMINUS:
      token_type = TOKEN_MINUS;
      break;
    case TSTATE_ASTERISKASTERISK:
      token_type = TOKEN_MULTIPLY;
      break;
      case TSTATE_EQUALS:
    token_type = TOKEN_EQUALS;
      break;
    case TSTATE_NOT:
      token_type = TOKEN_NOT;
      break;
    case TSTATE_LESS:
      token_type = TOKEN_LESS;
      break;
    case TSTATE_GREATER:
      token_type = TOKEN_GREATER;
      break;
    case TSTATE_AND:
      token_type = TOKEN_AND;
      break;
    case TSTATE_OR:
      token_type = TOKEN_OR;
      break;
    case TSTATE_PAROPEN:
      token_type = TOKEN_PAROPEN;
      break;
    case TSTATE_PARCLOSE:
      token_type = TOKEN_PARCLOSE;
      break;
    case TSTATE_PROGRAM:
      token_type = TOKEN_PROGRAM;
      break;
    case TSTATE_PRINT:
      token_type = TOKEN_PRINT;
      break;
    case TSTATE_VAR:
      token_type = TOKEN_VAR;
      break;
    case TSTATE_START:
      token_type = TOKEN_START;
      break;
    case TSTATE_SCAN:
      token_type = TOKEN_SCAN;
      break;
    case TSTATE_FINISH:
      token_type = TOKEN_FINISH;
      break;
    case TSTATE_FOR:
      token_type = TOKEN_FOR;
      break;
    case TSTATE_TO:
      token_type = TOKEN_TO;
      break;
    case TSTATE_NEXT:
      token_type = TOKEN_NEXT;
      break;
    case TSTATE_IF:
      token_type = TOKEN_IF;
      break;
    case TSTATE_GOTO:
      token_type = TOKEN_GOTO;
      break;
    case TSTATE_DIV:
      token_type = TOKEN_DIV;
      break;
    case TSTATE_MOD:
      token_type = TOKEN_MOD;
      break;
    case TSTATE_COLON:
      token_type = TOKEN_COLON;
      break;
    case TSTATE_ASSIGN:
      token_type = TOKEN_ASSIGN;
      break;
    case TSTATE_NOT_EQUALS:
      token_type = TOKEN_NOT_EQUALS;
      break;
    case TSTATE_SEMICOLON:
      token_type = TOKEN_SEMICOLON;
      break;
    case TSTATE_COMMA:
      token_type = TOKEN_COMMA;
      break;
    default:
      token_type = TOKEN_LENGTH_;
  }

  return token_type;
}