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

        if (is_inst(token)) {
            printf("Instruction: %s\n", token);
        }
        
        if (is_label(token)) {
            printf("Label: %s\n", token);
        }

        if (is_op(token)) {
            printf("Operand: %s\n", token);
        }

        if (is_address(token)) {
            printf("Address: %s\n", token);
        }

        token = strtok(NULL, delimiters); // Get the next token from where previous strtok left off

    }

}

bool is_label(const char *token) {

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

bool is_inst(const char *token) {

    if (token == NULL) {
        return false;
    }
    // should be edited w/ the specified instructions later on
    const char *inst_arr[] = {
        "add", "sub", "mul", "div", "and", "or", "xor", "nor",
        "sll", "srl", "lw", "sw", "beq", "bne", "j", "jal", "jr",
        "nop", "addi", NULL
    };

    for (int i = 0; inst_arr[i] != NULL; i++) {
        if (strcmp(token, inst_arr[i]) == 0) {
            return true;
        }
    }

    return false;

}

bool is_op(const char *token) {

    if (token == NULL) {
        return false;
    }

    return is_reg(token) || is_imm(token);

}

bool is_imm(const char *token) {

    if (*token == '-' || *token == '+') {
        token++;
    }

    if (token == NULL || *token == '\0') {
        return false;       
    }

    while (*token) {
        if (!isdigit(*token)) {
            return false;
        }
        token++;
    }

    return true;

}

bool is_reg(const char *token) {

    const char *registers[] = {
        "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3",
        "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
        "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
        "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"
    };

    for (int i = 0; i < 32; i++) {
        if (strcmp(token, registers[i]) == 0) {
            return true;
        }
    }

    return false;

}

bool is_address(const char *token) {

    if (token == NULL) {
        return false;
    }

    int i = 0;
    char *open_paren = strchr(token, '(');
    char *closed_paren = strchr(token, ')');

    if (open_paren == NULL || closed_paren == NULL) {
        return false;
    }

    // Pointer arithmetic determines array size
    int reg_len = closed_paren - open_paren - 1;
    char reg[reg_len];

    if (reg_len <= 0) {
        return false;
    }

    // Checks digit size and puts immediate inside of an array of i digits
    while (token[i] != '(') {

        if (!isdigit(token[i])) {
            return false;
        }

        i++;
    }

    // Offset too large
    if (i > 5) {
        return false;
    }
    
    // Pointer arithmetic + offset to copy content to an array
    for (int j = 0; j < reg_len; j++) {
        reg[j] = *(open_paren + 1 + j);
    }

    reg[reg_len] = '\0';

    if (!is_reg(reg)) {
        return false;
    }

    return true;

}