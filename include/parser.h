#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "instruction.h"

void tokenize_line(char *line);
bool is_label(char *token);
bool is_inst(char *token);
bool is_op(char *token);
bool is_int(char *token);

#endif