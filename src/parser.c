#include "parser.h"

void parseFile(char *file_name, Instruction *inst_arr, Register *r_arr, Label *label_arr) {

    FILE *fp = fopen(file_name, "r");

    if (fp == NULL) {
        perror("File could not be opened\n");
        return;
    }

    // TO-DO  

}

void tokenize_line(char *line) {

    const char delimiters[] = " \t,\n"; // Define delimiters
    char *token = strtok(line, delimiters); // Get the first token

    while (token != NULL) {

        printf("Token: %s\n", token); // Print the current token
        token = strtok(NULL, delimiters); // Get the next token from where previous strtok left off

        if (is_label(token)) {
            printf("%s is a label!\n", token);
        }

    }

}

bool is_label(char *token) {

    int i = 0;

    if (token == NULL) {
        return false;
    }

    for (int i = 0; token[i] != '\0'; i++) {
        if (token[i] == ':') {
            return true;
        }
    }

    return false;

}

bool is_inst(char *token) {

    // should be edited w/ the specified instructions later on
    const char *inst_arr[] = {
        "add", "sub", "mul", "div", "and", "or", "xor", "nor",
        "sll", "srl", "lw", "sw", "beq", "bne", "j", "jal", "jr",
        "nop", NULL
    };

    for (int i = 0; inst_arr[i] != NULL; i++) {
        if (strcmp(token, inst_arr[i]) == 0) {
            return true;
        }
    }

    return false;

}

bool is_op(char *token) {

    return token[0] == '$'; // TO-DO, finish for immediates

}

bool is_int(char *token) {

    // TO-DO, necessary to check for int operands (shamt and addi)

}

