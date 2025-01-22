#ifndef PARSER_H
#define PARSER_H

// Function prototypes
void clean_line(char *line);
void parse_file(char *file_name);
void tokenize_line(char *line, char *current_mode, bool *is_first_read, int *inst_line);

#endif