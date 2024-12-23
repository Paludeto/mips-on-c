#include "instruction.h"
#include <stdlib.h>

// Instruction table
Instruction table[] = {
    {"add", NULL, R, 3, execute_add},
    {"sub", NULL, R, 3, execute_sub},
    {"mult", NULL, R, 3, execute_mult},
    {NULL, NULL, UNKNOWN, 0, NULL} // Sentinel to mark the end
};


// TO-DO: implement behavior
void syscall(Instruction *inst, Register *arg, Register *dest);
void binary(Instruction inst);

// Executors
void execute_add(char **operands, Register *r_array) {
    
    printf("Executing ADD with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rd = get_register_index(operands[0]);
    int rs = get_register_index(operands[1]);
    int rt = get_register_index(operands[2]);

    r_add(&r_array[rs], &r_array[rt], &r_array[rd]);

}

void execute_sub(char **operands, Register *r_array) {

    printf("Executing SUB with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rd = get_register_index(operands[0]);
    int rs = get_register_index(operands[1]);
    int rt = get_register_index(operands[2]);
    
    r_sub(&r_array[rs], &r_array[rt], &r_array[rd]);

}

void execute_mult(char **operands, Register *r_array) {

    printf("Executing MULT with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rd = get_register_index(operands[0]);
    int rs = get_register_index(operands[1]);
    int rt = get_register_index(operands[2]);

    r_mult(&r_array[rs], &r_array[rt], &r_array[rd]);

}

// Checks if instruction is in the table
Instruction *find_instruction(const char *name) {

    for (int i = 0; table[i].name != NULL; i++) {
        if (strcmp(name, table[i].name) == 0) {
            return &table[i];
        }
    }

    return NULL;

}

// Creates instruction object
Instruction *create_instruction(const char *name, char **operands, int op_count) {

    Instruction *new_inst = malloc(sizeof(Instruction));
    new_inst->name = strdup(name);
    new_inst->operands = malloc(sizeof(char *) * op_count);

    for (int i = 0; i < op_count; i++) {
        new_inst->operands[i] = strdup(operands[i]);
    }

    return new_inst;

}

// Destroys instruction object
void free_instruction(Instruction *inst) {

    if (inst->name) {
        free(inst->name);
    }

    if (inst->operands) {
        for (int i = 0; i < inst->op_count; i++) {
            if (inst->operands[i]) {
                free(inst->operands[i]);
            }
        }
        free(inst->operands);
    }

    free(inst);

}

// R-Type Instructions
void r_add(Register *rs, Register *rt, Register *rd) {

    rd->value = rs->value + rt->value; // rd = rs + rt

}

void r_sub(Register *rs, Register *rt, Register *rd) {

    rd->value = rs->value - rt->value; // rd = rs - rt

}

void r_mult(Register *rs, Register *rt, Register *rd) {

    rd->value = rs->value * rt->value; // rd = rs * rt

}

void r_and(Register *rs, Register *rt, Register *rd) {

    rd->value = rs->value & rt->value; // rd = rs & rt

}

void r_or(Register *rs, Register *rt, Register *rd) {

    rd->value = rs->value | rt->value; // rd = rs | rt

}

void r_sll(Register *rt, Register *rd, int shamt) {

    if (shamt < 0 || shamt > 31) {
        printf("SHAMT must be between 0 and 31\n");
        return;
    }

    rd->value = rt->value << shamt; // rd = rt << shamt

}

// I-Type Instructions
void i_addi(Register *rs, Register *rt, int imm) {

    rt->value = rs->value + imm; // rt = rs + imm
    
}

void i_lui(Register *rt, int16_t imm) {

    rt->value = (int32_t)imm << 16; // rt = imm << 16 (upper 16 bits)

}