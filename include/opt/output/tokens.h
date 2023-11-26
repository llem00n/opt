// *************************************************************************
// tokens.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 10/30/23
// *************************************************************************

#ifndef OPT_TOKENS_H
#define OPT_TOKENS_H

#include <opt/token.h>
#include <stdio.h>

/**
 * @brief Prints tokens table to the file
 * @param token - tokens to print
 * @param file - file to print to
 */
void print_tokens(token_t token[], FILE *file);

#endif //OPT_TOKENS_H
