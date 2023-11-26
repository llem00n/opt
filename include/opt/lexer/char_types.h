// *************************************************************************
// char_types.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 10/23/23
// *************************************************************************

#ifndef OPT_LEXER_CHAR_TYPES_H
#define OPT_LEXER_CHAR_TYPES_H

/**
 * @brief Defines an enumeration of character types for lexical analyzation
 */
typedef enum {
  CHAR_D,
  CHAR_F,
  CHAR_G,
  CHAR_I,
  CHAR_M,
  CHAR_N,
  CHAR_P,
  CHAR_S,
  CHAR_T,
  CHAR_V,
  CHAR_a,
  CHAR_c,
  CHAR_d,
  CHAR_e,
  CHAR_f,
  CHAR_g,
  CHAR_h,
  CHAR_i,
  CHAR_m,
  CHAR_n,
  CHAR_o,
  CHAR_r,
  CHAR_s,
  CHAR_t,
  CHAR_v,
  CHAR_x,
  CHAR_PLUS,
  CHAR_MINUS,
  CHAR_ASTERISK,
  CHAR_EQUALS,
  CHAR_LESS,
  CHAR_GREATER,
  CHAR_EXCLAMATION_MARK,
  CHAR_AMPERSAND,
  CHAR_PIPE,
  CHAR_DOLLAR,
  CHAR_PAROPEN,
  CHAR_PARCLOSE,
  CHAR_COLON,
  CHAR_SEMICOLON,
  CHAR_COMMA,
  CHAR_UCASEALPHA,
  CHAR_LCASEALPHA,
  CHAR_DIGIT,
  CHAR_NEWLINE,
  CHAR_WHITESPACE,
  CHAR_EOF,
  CHAR_OTHER,
  CHAR_LENGTH_
} lexer_characters_t;

#endif //OPT_LEXER_CHAR_TYPES_H
