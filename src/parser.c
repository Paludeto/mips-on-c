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
            // Parse operands
            char *instruction = token;
            char *operands[10]; // Assume a maximum of 10 operands
            int operand_count = 0;

            while ((token = strtok(NULL, delimiters)) != NULL) {
                operands[operand_count++] = token;
            }

            // Validate instruction syntax and execute it (TO-DO)
            validate_instruction(instruction, operands, operand_count);
        }

        // test_fn(token); tests tokenization + checks

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

bool is_data_field(const char *token) {

    return strcasecmp(token, ".data") == 0;

}

bool is_text_field(const char *token) {

    return strcasecmp(token, ".text") == 0;

}

bool is_directive(const char *token) {

    const char *directives[] = {".word", ".byte", ".half", ".float", ".double", ".space", NULL};

    for (int i = 0; directives[i] != NULL; i++) {
        if (strcmp(token, directives[i]) == 0) {
            return true; // Valid directive found
        }
    }

    return false;

}

void validate_instruction(char *instruction, char **operands, int operand_count) {

    if (strcmp(instruction, "add") == 0 || strcmp(instruction, "sub") == 0 || strcmp(instruction, "mult") == 0 || 
        strcmp(instruction, "slt") == 0 || strcmp(instruction, "and") == 0 || strcmp(instruction, "or") == 0) {
        // R-type: 3 register operands
        if (operand_count != 3) {
            printf("Error: %s expects 3 operands, found %d\n", instruction, operand_count);
            return;
        }

        for (int i = 0; i < operand_count; i++) {
            if (!is_reg(operands[i])) {
                printf("Error: %s operand %d is not a valid register: %s\n", instruction, i + 1, operands[i]);
                return;
            }
        }

    } else if (strcmp(instruction, "lw") == 0 || strcmp(instruction, "sw") == 0 || strcmp(instruction, "lui") == 0) {
        // I-type: 1 register and 1 address
        if (operand_count != 2) {
            printf("Error: %s expects 2 operands, found %d\n", instruction, operand_count);
            return;
        }

        if (!is_reg(operands[0])) {
            printf("Error: %s first operand is not a valid register: %s\n", instruction, operands[0]);
            return;
        }

        if (!is_address(operands[1])) {
            printf("Error: %s second operand is not a valid address: %s\n", instruction, operands[1]);
            return;
        }

    } else if (strcmp(instruction, "beq") == 0 || strcmp(instruction, "bne") == 0 || strcmp(instruction, "slti") == 0 || strcmp(instruction, "addi") == 0) {
        // I-type: 2 registers and 1 immediate
        if (operand_count != 3) {
            printf("Error: %s expects 3 operands, found %d\n", instruction, operand_count);
            return;
        }

        if (!is_reg(operands[0]) || !is_reg(operands[1])) {
            printf("Error: %s requires the first two operands to be registers.\n", instruction);
            return;
        }

        if (!is_imm(operands[2])) {
            printf("Error: %s requires the third operand to be an immediate: %s\n", operands[2]);
            return;
        }

    // } else if (strcmp(instruction, "j") == 0 || strcmp(instruction, "jal") == 0) {
    //     // J-type: 1 label
    //     if (operand_count != 1) {
    //         printf("Error: %s expects 1 operand, found %d\n", instruction, operand_count);
    //         return;
    //     }

    //     if (!is_label(operands[0])) {
    //         printf("Error: %s requires a label as the operand: %s\n", instruction, operands[0]);
    //         return;
    //     }    

    } else {
        printf("Error: Unknown instruction: %s\n", instruction);
    }

}


void test_fn(char *token) {

    if (is_data_field(token)) {
        printf("Data field: %s\n", token);
    }

    if (is_directive(token)) {
        printf("Directive: %s\n", token);
    }

    if (is_text_field(token)) {
        printf("Text field: %s\n", token);
    }

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

}