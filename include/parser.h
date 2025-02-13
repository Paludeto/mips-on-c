#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

/**
 * @brief Parses the file and tokenizes the lines
 * 
 * @param line 
 */
void clean_line(char *line);
int parse_file(char *file_name);
void tokenize_line(char *line, char *current_mode, bool *is_first_read, int *inst_line);

#endif