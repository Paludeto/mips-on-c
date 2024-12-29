#include "executors.h"
#include "memory.h"
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

void execute_lw(char **operands, Register *r_array, LabelList *label_list) {

    printf("Executing LW with operands %s, %s\n", operands[0], operands[1]);

    // Get the target register index
    int rt = get_register_index(operands[0]);
    if (rt == -1) {
        printf("Error: Invalid target register %s\n", operands[0]);
        return;
    }

    // Parse the second operand: "offset(base)"
    char *operand = operands[1];
    char *open_paren = strchr(operand, '(');
    char *close_paren = strchr(operand, ')');

    if (!open_paren || !close_paren || open_paren > close_paren) {
        printf("Error: Invalid memory access syntax: %s\n", operand);
        return;
    }

    // Extract offset string
    size_t offset_len = open_paren - operand;
    if (offset_len == 0) {
        printf("Error: Missing offset in memory access operand: %s\n", operand);
        return;
    }

    char offset_str[offset_len + 1];
    strncpy(offset_str, operand, offset_len);
    offset_str[offset_len] = '\0';

    // Convert offset to integer
    char *endptr;
    long offset_long = strtol(offset_str, &endptr, 10);
    if (*endptr != '\0') {
        printf("Error: Invalid offset value: %s\n", offset_str);
        return;
    }

    // Validate offset range (16-bit signed)
    if (offset_long < -32768 || offset_long > 32767) {
        printf("Error: Offset %ld out of 16-bit signed range for LW\n", offset_long);
        return;
    }

    int offset = (int)offset_long;

    // Extract base register name
    size_t reg_len = close_paren - open_paren - 1;
    if (reg_len <= 0 || reg_len >= sizeof(((Register *)0)->name)) { // Prevent buffer overflow
        printf("Error: Invalid base register in operand: %s\n", operand);
        return;
    }

    char reg_name[reg_len + 1];
    strncpy(reg_name, open_paren + 1, reg_len);
    reg_name[reg_len] = '\0';

    // Get base register index
    int base = get_register_index(reg_name);
    if (base == -1) {
        printf("Error: Invalid base register %s\n", reg_name);
        return;
    }

    // Calculate effective address
    long base_value = r_array[base].value;
    long effective_address = base_value + offset;

    // Validate effective address within memory bounds
    if (effective_address < 0 || (uint32_t)effective_address + 3 >= MEMORY_SIZE) {
        printf("Error: Effective address 0x%lX out of memory bounds for LW\n", effective_address);
        return;
    }

    // Check alignment
    if (effective_address % 4 != 0) {
        printf("Error: Unaligned memory access at address: 0x%lX for LW\n", effective_address);
        return;
    }

    // Load word from simulated memory
    int loaded_word;
    if (!load_word_from_memory((uint32_t)effective_address, &loaded_word)) {
        // Error already printed in load_word_from_memory
        return;
    }

    // Store the loaded word into the target register
    r_array[rt].value = loaded_word;

    printf("LW: Loaded 0x%X into register %s\n", loaded_word, operands[0]);

}

// Enhanced execute_sw function
void execute_sw(char **operands, Register *r_array, LabelList *label_list) {

    printf("Executing SW with operands %s, %s\n", operands[0], operands[1]);

    // Get the source register index
    int rt = get_register_index(operands[0]);
    if (rt == -1) {
        printf("Error: Invalid source register %s\n", operands[0]);
        return;
    }

    // Parse the second operand: "offset(base)"
    char *operand = operands[1];
    char *open_paren = strchr(operand, '(');
    char *close_paren = strchr(operand, ')');

    if (!open_paren || !close_paren || open_paren > close_paren) {
        printf("Error: Invalid memory access syntax: %s\n", operand);
        return;
    }

    // Extract offset string
    size_t offset_len = open_paren - operand;
    if (offset_len == 0) {
        printf("Error: Missing offset in memory access operand: %s\n", operand);
        return;
    }
    char offset_str[offset_len + 1];
    strncpy(offset_str, operand, offset_len);
    offset_str[offset_len] = '\0';

    // Convert offset to integer
    char *endptr;
    long offset_long = strtol(offset_str, &endptr, 10);
    if (*endptr != '\0') {
        printf("Error: Invalid offset value: %s\n", offset_str);
        return;
    }

    // Validate offset range (16-bit signed)
    if (offset_long < -32768 || offset_long > 32767) {
        printf("Error: Offset %ld out of 16-bit signed range for SW\n", offset_long);
        return;
    }
    int offset = (int)offset_long;

    // Extract base register name
    size_t reg_len = close_paren - open_paren - 1;
    if (reg_len <= 0 || reg_len >= sizeof(((Register *)0)->name)) { // Prevent buffer overflow
        printf("Error: Invalid base register in operand: %s\n", operand);
        return;
    }
    char reg_name[reg_len + 1];
    strncpy(reg_name, open_paren + 1, reg_len);
    reg_name[reg_len] = '\0';

    // Get base register index
    int base = get_register_index(reg_name);
    if (base == -1) {
        printf("Error: Invalid base register %s\n", reg_name);
        return;
    }

    // Calculate effective address
    long base_value = r_array[base].value;
    long effective_address = base_value + offset;

    // Validate effective address within memory bounds
    if (effective_address < 0 || (uint32_t)effective_address + 3 >= MEMORY_SIZE) {
        printf("Error: Effective address 0x%lX out of memory bounds for SW\n", effective_address);
        return;
    }

    // Check alignment
    if (effective_address % 4 != 0) {
        printf("Error: Unaligned memory access at address: 0x%lX for SW\n", effective_address);
        return;
    }

    // Get the value to store from the source register
    int value_to_store = r_array[rt].value;

    // Store the word into simulated memory
    if (!store_word_to_memory((uint32_t)effective_address, value_to_store)) {
        // Error already printed in store_word_to_memory
        return;
    }

    printf("SW: Stored 0x%X from register %s into address 0x%lX\n", value_to_store, operands[0], effective_address);
    
}