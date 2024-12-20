#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "instruction.h"

void tokenize_line(char *line);
bool is_reg(const char *token);
bool is_label(const char *token);
bool is_inst(const char *token);
bool is_op(const char *token);
bool is_imm(const char *token);
bool is_address(const char *token);

#endif