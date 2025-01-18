#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include "label_list.h"
#include "validator.h"

// Function prototypes
void interactive_parse();
void parseFile(char *file_name);
void tokenize_line(char *line, char *current_mode);

#endif