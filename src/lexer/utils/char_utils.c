// *************************************************************************
// character_type.c
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 10/23/23
// *************************************************************************

#include "opt/lexer/utils.h"
#include <stdio.h>
#include <ctype.h>

lexer_characters_t get_character_type(int32_t c) {
  lexer_characters_t type = CHAR_LENGTH_;
  switch (c) {
    case 'D':
      type = CHAR_D;
      break;
    case 'F':
      type = CHAR_F;
      break;
    case 'G':
      type = CHAR_G;
      break;
    case 'I':
      type = CHAR_I;
      break;
    case 'M':
      type = CHAR_M;
      break;
    case 'N':
      type = CHAR_N;
      break;
    case 'P':
      type = CHAR_P;
      break;
    case 'S':
      type = CHAR_S;
      break;
    case 'T':
      type = CHAR_T;
      break;
    case 'V':
      type = CHAR_V;
      break;
    case 'a':
      type = CHAR_a;
      break;
    case 'c':
      type = CHAR_c;
      break;
    case 'd':
      type = CHAR_d;
      break;
    case 'e':
      type = CHAR_e;
      break;
    case 'f':
      type = CHAR_f;
      break;
    case 'g':
      type = CHAR_g;
      break;
    case 'h':
      type = CHAR_h;
      break;
    case 'i':
      type = CHAR_i;
      break;
    case 'm':
      type = CHAR_m;
      break;
    case 'n':
      type = CHAR_n;
      break;
    case 'o':
      type = CHAR_o;
      break;
    case 'r':
      type = CHAR_r;
      break;
    case 's':
      type = CHAR_s;
      break;
    case 't':
      type = CHAR_t;
      break;
    case 'v':
      type = CHAR_v;
      break;
    case 'x':
      type = CHAR_x;
      break;
    case '+':
      type = CHAR_PLUS;
      break;
    case '-':
      type = CHAR_MINUS;
      break;
    case '*':
      type = CHAR_ASTERISK;
      break;
    case '=':
      type = CHAR_EQUALS;
      break;
    case '<':
      type = CHAR_LESS;
      break;
    case '>':
      type = CHAR_GREATER;
      break;
    case '!':
      type = CHAR_EXCLAMATION_MARK;
      break;
    case '&':
      type = CHAR_AMPERSAND;
      break;
    case '|':
      type = CHAR_PIPE;
      break;
    case '$':
      type = CHAR_DOLLAR;
      break;
    case '(':
      type = CHAR_PAROPEN;
      break;
    case ')':
      type = CHAR_PARCLOSE;
      break;
    case '\n':
      type = CHAR_NEWLINE;
      break;
    case EOF:
      type = CHAR_EOF;
      break;
    case ';':
      type = CHAR_SEMICOLON;
      break;
    case ',':
      type = CHAR_COMMA;
      break;
    default:
      if (isspace(c)) {
        type = CHAR_WHITESPACE;
      } else if (isdigit(c)) {
        type = CHAR_DIGIT;
      } else if (isalpha(c) && isupper(c)) {
        type = CHAR_UCASEALPHA;
      } else if (isalpha(c) && islower(c)) {
        type = CHAR_LCASEALPHA;
      } else {
        type = CHAR_OTHER;
      }
      break;
  }
  return type;
}
