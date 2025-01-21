// parser.c
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define maximums
#define MAX_DIR 128
#define MAX_INPUT_SIZE 256
#define MAX_OPERANDS 4

// void interactive_parse() {

//     char line[MAX_INPUT_SIZE];
//     char current_mode[16] = ""; // Controla o contexto atual (data ou text)
//     printf("Modo Interativo: Digite uma instrução ou '.exit' para sair.\n");

//     while (1) {
        
//         printf("> "); // Prompt interativo
//         if (fgets(line, sizeof(line), stdin) == NULL) {
//             break; // EOF ou erro de leitura
//         }

//         // Remove caracteres de nova linha
//         size_t len = strlen(line);
//         while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
//             line[len - 1] = '\0';
//             len--;
//         }

//         // Ignorar linhas vazias
//         if (len == 0) continue;

//         // Verificar comando de saída
//         if (strcmp(line, ".exit") == 0) {
//             printf("Saindo do modo interativo.\n");
//             break;
//         }

//         // Reutilizar tokenize_line para processar a entrada
//         tokenize_line(line, current_mode);
//     }

// }

// Function to parse the entire file
void parseFile(char *file_name) {

    FILE *fp = fopen(file_name, "r");
    char line[MAX_INPUT_SIZE];
    char current_mode[16] = "";

    if (fp == NULL) {
        perror("File could not be opened");
        return;
    }
    
    initialize_memory();

    while (fgets(line, sizeof(line), fp)) {
        // Remove newline characters
        size_t len = strlen(line);
        while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
            line[len - 1] = '\0';
            len--;
        }

        // Remove comments
        char *comment = strchr(line, '#');
        if (comment) *comment = '\0';

        // Trim leading whitespace
        char *start = line;
        while (isspace(*start)) start++;

        if (*start == '\0') continue; // Skip empty lines

        tokenize_line(start, current_mode);
    }

    fclose(fp);

}

void tokenize_line(char *line, char *current_mode) {

    const char delimiters[] = " \t,";
    char *token = strtok(line, delimiters);

    if (token == NULL) return; // Empty line

    // Capture label if it exists
    char *label_name = NULL;
    size_t token_len = strlen(token);
    if (token[token_len - 1] == ':') {
        token[token_len - 1] = '\0';  // Remove ':'
        label_name = token;           // Capture label name

        // Store label and address in label array
        if (strcasecmp(current_mode, ".text") == 0) {
            strcpy(label_arr[curr_label].name, label_name);
            label_arr[curr_label].address = current_text_address;
            curr_label++;
        }

        token = strtok(NULL, delimiters);  // Move to the next token
        if (token == NULL) return;         // Line has only a label
    }

    // Check for section markers
    if (is_data_field(token)) {
        strcpy(current_mode, ".data");
        return;
    } else if (is_text_field(token)) {
        strcpy(current_mode, ".text");
        return;
    }

    if (strcasecmp(current_mode, ".data") == 0) {
        // Process data directives
        char *args[MAX_DIR];
        int arg_count = 0;

        args[arg_count++] = token; // Directive

        while ((token = strtok(NULL, delimiters)) != NULL) {
            args[arg_count++] = token;
        }

        if (arg_count > 0) {
            validate_data_field(label_name, args, arg_count, label_arr);
        }

    } else if (strcasecmp(current_mode, ".text") == 0) {
        // Process instructions
        char *instruction = token;
        char *operands[MAX_OPERANDS];
        int operand_count = 0;

        while ((token = strtok(NULL, delimiters)) != NULL) {
            operands[operand_count++] = token;
            if (operand_count >= MAX_OPERANDS) break;
        }

        validate_inst(instruction, operands, operand_count);

    }
    
}
