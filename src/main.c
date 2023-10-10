// *************************************************************************
// lexer.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 9/25/2023
// *************************************************************************

#include <opt/lexer.h>
#include <stdio.h>

#define MAX_TOKENS_LENGTH 500

int main() {
  FILE *file;
  errno_t errno = fopen_s(&file, "D:\\tmp.txt", "rt");
  if (!file) return 0;

  token_t tokens[MAX_TOKENS_LENGTH];
  error_t error = get_tokens(file, tokens, MAX_TOKENS_LENGTH);
  fclose(file);
  return 0;
}
