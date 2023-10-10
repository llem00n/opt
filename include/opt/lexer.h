// *************************************************************************
// lexer.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 9/25/2023
// *************************************************************************

#ifndef SRC_LEXER_H
#define SRC_LEXER_H

#include <stdint.h>
#include <stdio.h>
#include <opt/token.h>
#include <opt/err.h>


error_t get_tokens(FILE* file, token_t tokens[], uint32_t tokens_length);

#endif //SRC_LEXER_H
