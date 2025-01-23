// parser.c
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "parser.h"
#include "validator.h"
#include "label.h"
#include "memory.h"

// Define maximums
#define MAX_DIR 128
#define MAX_INPUT_SIZE 256
#define MAX_OPERANDS 4

void parse_file(char *file_name) {

    FILE *fp;
    char line[MAX_INPUT_SIZE];
    char current_mode[16] = "";
    bool is_first_read = true;
    int inst_line = 0;

    if ((fp = fopen(file_name, "r")) == NULL) {
        perror("File could not be opened");
        exit(EXIT_FAILURE);
    }

    initialize_memory();

    // First pass: Collect labels
    while (fgets(line, sizeof(line), fp)) {
        clean_line(line);
        tokenize_line(line, current_mode, &is_first_read, &inst_line);
    }

    // Reset and re-parse for instructions
    rewind(fp);
    is_first_read = false;
    inst_line = 0;

    while (fgets(line, sizeof(line), fp)) {
        clean_line(line);
        tokenize_line(line, current_mode, &is_first_read, &inst_line);
    }

    fclose(fp);

}

void clean_line(char *line) {

    size_t len = strlen(line);
    while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
        line[len - 1] = '\0';
        len--;
    }

    char *comment = strchr(line, '#');
    if (comment) *comment = '\0';

    while (isspace(*line)) line++;

}

void tokenize_line(char *line, char *current_mode, bool *is_first_read, int *inst_line) {

    const char delimiters[] = " \t,";
    char *token = strtok(line, delimiters);

    if (token == NULL) return; // Skip empty lines

    char *label_name = NULL;  // Declare label name outside

    // Detect label
    size_t token_len = strlen(token);

    if (token[token_len - 1] == ':') {
        token[token_len - 1] = '\0';  // Remove ':'
        label_name = token;

        if (*is_first_read) {
            if (strcasecmp(current_mode, ".text") == 0) {
                add_label(label_name, (*inst_line));  // Convert instruction count to byte address
            } else if (strcasecmp(current_mode, ".data") == 0) {
                add_label(label_name, current_data_address);
            }
        }

        token = strtok(NULL, delimiters);
        if (token == NULL) return;  // If only a label exists, move on
    }

    // Check section markers
    if (is_data_field(token)) {
        strcpy(current_mode, ".data");
        return;
    } else if (is_text_field(token)) {
        strcpy(current_mode, ".text");
        return;
    }

    if (strcasecmp(current_mode, ".data") == 0) {
        // Process .data directives
        char *args[MAX_DIR];
        int arg_count = 0;

        args[arg_count++] = token;  // Directive

        while ((token = strtok(NULL, delimiters)) != NULL) {
            args[arg_count++] = token;
        }

        if (arg_count > 0 && !(*is_first_read)) {
            // Pass the detected label name to the validation function
            validate_data_field(label_name, args, arg_count, label_arr);
        }

    } else if (strcasecmp(current_mode, ".text") == 0) {
        // Process .text instructions
        char *instruction = token;
        char *operands[MAX_OPERANDS];
        int operand_count = 0;

        while ((token = strtok(NULL, delimiters)) != NULL) {
            operands[operand_count++] = token;
            if (operand_count >= MAX_OPERANDS) break;
        }

        if (!(*is_first_read)) {
            validate_inst(instruction, operands, operand_count);
        }

        (*inst_line)++;  // Increment instruction line count
    }

}
