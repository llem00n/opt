// *************************************************************************
// lexer.c
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 9/26/2023
// *************************************************************************

#include <opt/lexer.h>
#include <opt/config/lexer_config.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define TOKEN_VALUE_MAX_LENGTH 1024

typedef uint16_t state_t;

lexer_characters_t get_character_type(int32_t c);
bool is_terminating_state(state_t state);
bool is_invalid_state(state_t state);
token_t create_token(char *token_value, state_t state, uint32_t line);
token_type_t get_token_type(state_t state);
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
    lexer_characters_t character_type;
    bool is_terminating;
    if (read_next) c = getc(file);
    read_next = true;
    if (c == '\n') line++;

    character_type = get_character_type(c);
    state = LEXER_TABLE[state][character_type];
    is_terminating = is_terminating_state(state);
    bool adding = should_add(character_type, state);
    if (is_terminating && tokens_length == tokens_max_length) {
      result = ERROR_TOO_MUCH_TOKENS;
    } else if (is_terminating) {
      read_next = false;
      tokens[tokens_length++] = create_token(token_value, state, line);
      strcpy_s(token_value, TOKEN_VALUE_MAX_LENGTH, "");
      token_value_length = 0;
    } else if (is_invalid_state(state)) {
      result = ERROR_INVALID_TOKEN;
      tokens[tokens_length++] = create_token(token_value, state, line);
      strcpy_s(token_value, TOKEN_VALUE_MAX_LENGTH, "");
      token_value_length = 0;
    } else if (adding && token_value_length == TOKEN_VALUE_MAX_LENGTH) {
      result = ERROR_TOKEN_TOO_LONG;
      tokens[tokens_length++] = create_token(token_value, state, line);
      strcpy_s(token_value, TOKEN_VALUE_MAX_LENGTH, "");
      token_value_length = 0;
    } else if (adding) {
      token_value[token_value_length++] = (char)c;
      token_value[token_value_length] = 0;
    }
  }

  return result;
}

lexer_characters_t get_character_type(int32_t c) {
  lexer_characters_t type = CHAR_LENGTH_;
  switch (c) {
    case 'a':
      type = CHAR_a;
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
    case 'l':
      type = CHAR_l;
      break;
    case 'n':
      type = CHAR_n;
      break;
    case 'o':
      type = CHAR_o;
      break;
    case 'p':
      type = CHAR_p;
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
    case 'u':
      type = CHAR_u;
      break;
    case 'w':
      type = CHAR_w;
      break;
    case 'x':
      type = CHAR_x;
      break;
    case '_':
      type = CHAR__;
      break;
    case '!':
      type = CHAR_EXCLAMATION_MARK;
      break;
    case '"':
    case '\'':
      type = CHAR_QUOTE;
      break;
    case '*':
      type = CHAR_ASTERISK;
      break;
    case '(':
      type = CHAR_PARENTHESES_OPEN;
      break;
    case ')':
      type = CHAR_PARENTHESES_CLOSED;
      break;
    case '-':
      type = CHAR_MINUS;
      break;
    case '+':
      type = CHAR_PLUS;
      break;
    case '=':
      type = CHAR_EQUALS;
      break;
    case '/':
      type = CHAR_SLASH;
      break;
    case '%':
      type = CHAR_PERCENT;
      break;
    case '<':
      type = CHAR_LESS;
      break;
    case '>':
      type = CHAR_GREATER;
      break;
    case '.':
      type = CHAR_PERIOD;
      break;
    case '&':
      type = CHAR_AMPERSAND;
      break;
    case '|':
      type = CHAR_PIPE;
      break;
    case ';':
      type = CHAR_SEMICOLON;
      break;
    case EOF:
      type = CHAR_EOF;
      break;
    default:
      if (isalpha(c)) {
        type = CHAR_ALPHABETIC;
      } else if (isdigit(c)) {
        type = CHAR_DIGIT;
      } else if (isspace(c)) {
        type = CHAR_WHITESPACE;
      }
      break;
  }
  return type;
}

bool is_terminating_state(state_t state) {
  bool result = false;
  switch (state) {
    case TSTATE_IDENTIFIER:
    case TSTATE_DO:
    case TSTATE_ELSE:
    case TSTATE_GOTO:
    case TSTATE_IF:
    case TSTATE_REPEAT:
    case TSTATE_TO:
    case TSTATE_UNTIL:
    case TSTATE_NEXT:
    case TSTATE_WHILE:
    case TSTATE_THEN:
      result = true;
      break;
    default:
      result = false;
  }

  return result;
}

bool is_invalid_state(state_t state) {
  return false;
}

token_t create_token(char *token_value, state_t state, uint32_t line) {
  size_t size = 0;

  token_t token = {
    .line = line,
    .type = get_token_type(state),
    .value = NULL,
  };

  if (token.type < SELF_CONTAINING_TOKENS_START) {
    size = strlen(token_value) + 1;
    token.value = malloc(sizeof(char) * size);
    strcpy_s(token.value, size, token_value);
  }

  return token;
}

token_type_t get_token_type(state_t state) {
  token_type_t token_type;

  switch (state) {
    case TSTATE_IDENTIFIER:
      token_type = TOKEN_IDENTIFIER;
      break;
    case TSTATE_DO:
      token_type = TOKEN_DO;
      break;
    case TSTATE_ELSE:
      token_type = TOKEN_ELSE;
      break;
    case TSTATE_GOTO:
      token_type = TOKEN_GOTO;
      break;
    case TSTATE_IF:
      token_type = TOKEN_IF;
      break;
    case TSTATE_REPEAT:
      token_type = TOKEN_REPEAT;
      break;
    case TSTATE_TO:
      token_type = TOKEN_TO;
      break;
    case TSTATE_UNTIL:
      token_type = TOKEN_UNTIL;
      break;
    case TSTATE_NEXT:
      token_type = TOKEN_NEXT;
      break;
    case TSTATE_WHILE:
      token_type = TOKEN_WHILE;
      break;
    case TSTATE_THEN:
      token_type = TOKEN_THEN;
      break;
    default:
      token_type = TOKEN_ERROR;
      break;
  }

  return token_type;
}

bool should_add(lexer_characters_t  char_type, state_t state) {
  return char_type != CHAR_WHITESPACE;
}

#undef TOKEN_VALUE_MAX_LENGTH