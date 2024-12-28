#include "executors.h"
#include <stdio.h>

// Executors
void execute_add(char **operands, Register *r_array) {

    printf("Executing ADD with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rd = get_register_index(operands[0]);
    int rs = get_register_index(operands[1]);
    int rt = get_register_index(operands[2]);

    r_array[rd].value = r_array[rs].value + r_array[rt].value; // rd = rs + rt

}

void execute_sub(char **operands, Register *r_array) {

    printf("Executing SUB with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rd = get_register_index(operands[0]);
    int rs = get_register_index(operands[1]);
    int rt = get_register_index(operands[2]);

    r_array[rd].value = r_array[rs].value - r_array[rt].value; // rd = rs - rt

}

void execute_mult(char **operands, Register *r_array) {

    printf("Executing MULT with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rd = get_register_index(operands[0]);
    int rs = get_register_index(operands[1]);
    int rt = get_register_index(operands[2]);

    r_array[rd].value = r_array[rs].value * r_array[rt].value; // rd = rs * rt

}

void execute_and(char **operands, Register *r_array) {

    printf("Executing AND with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rd = get_register_index(operands[0]);
    int rs = get_register_index(operands[1]);
    int rt = get_register_index(operands[2]);


    r_array[rd].value = r_array[rs].value & r_array[rt].value; // rd = rs & rt
}

void execute_or(char **operands, Register *r_array) {

    printf("Executing OR with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rd = get_register_index(operands[0]);
    int rs = get_register_index(operands[1]);
    int rt = get_register_index(operands[2]);

    r_array[rd].value = r_array[rs].value | r_array[rt].value; // rd = rs | rt

}

void execute_sll(char **operands, Register *r_array) {

    printf("Executing SLL with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rd = get_register_index(operands[0]);
    int rt = get_register_index(operands[1]);
    int shamt = atoi(operands[2]);

    if (shamt < 0 || shamt > 31) {
        printf("SHAMT must be between 0 and 31\n");
        return;
    }

    r_array[rd].value = r_array[rt].value << shamt; // rd = rt << shamt

}

void execute_lui(char **operands, Register *r_array) {

    printf("Executing LUI with operands %s, %s\n", operands[0], operands[1]);

    int rt = get_register_index(operands[0]);
    int imm = atoi(operands[1]);

    r_array[rt].value = (int32_t)imm << 16; // rt = imm << 16

}

void execute_addi(char **operands, Register *r_array) {

    printf("Executing ADDI with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rt = get_register_index(operands[0]);
    int rs = get_register_index(operands[1]);
    int imm = atoi(operands[2]);

    r_array[rt].value = r_array[rs].value + imm; // rt = rs + imm

}

void execute_move(char **operands, Register *r_array) {

    printf("Executing MOVE with operands %s, %s\n", operands[0], operands[1]);

    int rd = get_register_index(operands[0]);
    int rs = get_register_index(operands[1]);
  

    r_array[rd].value = r_array[rs].value; // rd = rs
    
}

void execute_slt(char **operands, Register *r_array) {

    printf("Executing SLT with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rd = get_register_index(operands[0]);
    int rs = get_register_index(operands[1]);
    int rt = get_register_index(operands[2]);

    r_array[rd].value = r_array[rs].value < r_array[rt].value ? 1 : 0; // rd = (rs < rt) ? 1 : 0

}

void execute_slti(char **operands, Register *r_array) {

    printf("Executing SLTI with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rt = get_register_index(operands[0]);
    int rs = get_register_index(operands[1]);
    int imm = atoi(operands[2]);

    r_array[rt].value = r_array[rs].value < imm ? 1 : 0; // rt = (rs < imm) ? 1 : 0

}

void execute_la(char **operands, Register *r_array, LabelList *label_list) {

    printf("Executing LA with operands %s, %s\n", operands[0], operands[1]);

    int rt = get_register_index(operands[0]);
    Label *label = find_label(label_list, operands[1]);

    // Null check if label is not found
    if (label == NULL) {
        printf("Error: Label %s not found\n", operands[1]);
        return;
    }

    r_array[rt].value = (intptr_t)label->address; // rt = address of label

}

void execute_lw(char **operands, Register *r_array) {

    // Get the register index for destination
    int rt = get_register_index(operands[0]);

    // Parse the offset value
    char *open_paren = strchr(operands[1], '(');
    char *close_paren = strchr(operands[1], ')');

    // Extract offset
    int offset = atoi(operands[1]); // Parses the numeric part before '('

    // Extract the register name inside parentheses
    size_t reg_len = close_paren - open_paren - 1; // Length of the register name
    char *reg_name = malloc(reg_len + 1); // Allocate space for the register name

    if (!reg_name) {
        perror("Error: Memory allocation failed\n");
        return;
    }

    strncpy(reg_name, open_paren + 1, reg_len); // Copy the register name
    reg_name[reg_len] = '\0'; // Null-terminate the string

    // Get the base register index
    int base_reg = get_register_index(reg_name);
    if (base_reg == -1) {
        printf("Error: Invalid base register %s\n", reg_name);
        free(reg_name);
        return;
    }

    // Simulate loading the word 
    intptr_t memory_address = (intptr_t) r_array[base_reg].value + offset; // Calculate address
    printf("Loading from address: %d into register %s\n", memory_address, operands[0]);

    // Perform memory access
    r_array[rt].value = *(int *)memory_address; 

    free(reg_name); // Free allocated memory

}

void execute_sw(char **operands, Register *r_array) {

    // Get the register index for destination
    int rt = get_register_index(operands[0]);

    // Parse the offset value
    char *open_paren = strchr(operands[1], '(');
    char *close_paren = strchr(operands[1], ')');

    // Extract offset
    int offset = atoi(operands[1]); // Parses the numeric part before '('

    // Extract the register name inside parentheses
    size_t reg_len = close_paren - open_paren - 1; // Length of the register name
    char *reg_name = malloc(reg_len + 1); // Allocate space for the register name

    if (!reg_name) {
        perror("Error: Memory allocation failed\n");
        return;
    }

    strncpy(reg_name, open_paren + 1, reg_len); // Copy the register name
    reg_name[reg_len] = '\0'; // Null-terminate the string

    // Get the base register index
    int base_reg = get_register_index(reg_name);
    if (base_reg == -1) {
        printf("Error: Invalid base register %s\n", reg_name);
        free(reg_name);
        return;
    }

    // Simulate loading the word 
    intptr_t memory_address = (intptr_t) r_array[base_reg].value + offset; // Calculate address
    printf("Storing at address: %d register %s\n", memory_address, operands[0]);

    // Perform memory access
    *(int *)memory_address = r_array[rt].value; 

    free(reg_name); // Free allocated memory

}