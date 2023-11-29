// *************************************************************************
// lexer.c
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 9/26/2023
// *************************************************************************

#include "opt/lexer/lexer.h"
#include "opt/lexer/table.h"
#include "opt/lexer/utils.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define TOKEN_VALUE_MAX_LENGTH 1024

bool should_add(lexer_characters_t char_type, state_t state);

error_t get_tokens(FILE *file, token_t tokens[], uint32_t tokens_max_length) {
  state_t state = 0;
  uint32_t tokens_length = 0;
  int32_t c = 0;
  char token_value[TOKEN_VALUE_MAX_LENGTH + 1] = "";
  uint16_t token_value_length = 0;
  error_t result = ERROR_OK;
  uint32_t line = 1;
  bool read_next = true;

  while (c != EOF) {
    if (read_next) c = getc(file);
    if (c == '\n' && read_next) line++;
    read_next = true;

    const lexer_characters_t character_type = get_character_type(c);
    state = LEXER_TABLE[state][character_type];
    const bool is_terminating = is_terminating_state(state);
    const bool adding = should_add(character_type, state);

    if (is_terminating && tokens_length == tokens_max_length) {
      result = ERROR_TOO_MUCH_TOKENS;
      read_next = false;
      state = 0;
    } else if (is_terminating) {
      read_next = false;
      const token_type_t token_type = get_token_type(state);
      if (token_type != TOKEN_COMMENT && token_type != TOKEN_WHITESPACE) {
        tokens[tokens_length++] = create_token(token_value, state, line);
      }
      token_value_length = 0;
      state = 0;
    } else if (adding && token_value_length == TOKEN_VALUE_MAX_LENGTH) {
      result = ERROR_TOKEN_TOO_LONG;
      tokens[tokens_length++] = create_token(token_value, state, line);
      token_value_length = 0;
    } else if (adding) {
      token_value[token_value_length++] = (char)c;
      token_value[token_value_length] = 0;
    }
  }

  if (tokens_length == tokens_max_length) {
    result = ERROR_TOO_MUCH_TOKENS;
  } else {
    tokens[tokens_length++] = (token_t){ .type = TOKEN_EOF, .line = line, .value = NULL };
  }

  return result;
}

token_t create_token(const char *token_value, const state_t state, const uint32_t line) {
  token_t token = {
    .line = line,
    .type = get_token_type(state),
    .value = NULL,
  };

  if (token.type < SELF_CONTAINING_TOKENS_START) {
    const size_t size = strlen(token_value) + 1;
    token.value = malloc(sizeof(char) * size);
    strncpy(token.value, token_value, size);
  }

  return token;
}

bool should_add(const lexer_characters_t  char_type, const state_t state) {
  if (!state) return false;

  switch (char_type) {
    case CHAR_WHITESPACE:
    case CHAR_NEWLINE:
    case CHAR_EOF:
      return false;
    default:
      return true;
  }
}

#undef TOKEN_VALUE_MAX_LENGTH
