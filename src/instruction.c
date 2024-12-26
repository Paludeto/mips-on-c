#include "instruction.h"
#include <stdlib.h>

// Instruction table
Instruction table[] = {
    {"add", NULL, R, 3, execute_add},
    {"sub", NULL, R, 3, execute_sub},
    {"mult", NULL, R, 3, execute_mult},
    {"and", NULL, R, 3, execute_and},
    {"or", NULL, R, 3, execute_or},
    {"sll", NULL, R, 3, execute_sll},
    {"lui", NULL, I, 2, execute_lui},
    {"addi", NULL, I, 3, execute_addi},
    {"move", NULL, R, 2, execute_move},
    {"slt", NULL, R, 3, execute_slt},
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

void execute_and(char **operands, Register *r_array) {

    printf("Executing AND with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rd = get_register_index(operands[0]);
    int rs = get_register_index(operands[1]);
    int rt = get_register_index(operands[2]);

    r_and(&r_array[rs], &r_array[rt], &r_array[rd]);

}

void execute_or(char **operands, Register *r_array) {

    printf("Executing OR with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rd = get_register_index(operands[0]);
    int rs = get_register_index(operands[1]);
    int rt = get_register_index(operands[2]);

    r_or(&r_array[rs], &r_array[rt], &r_array[rd]);

}

void execute_sll(char **operands, Register *r_array) {

    printf("Executing SLL with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rd = get_register_index(operands[0]);
    int rt = get_register_index(operands[1]);
    int shamt = atoi(operands[2]);

    r_sll(&r_array[rt], &r_array[rd], shamt);

}

void execute_lui(char **operands, Register *r_array) {

    printf("Executing LUI with operands %s, %s\n", operands[0], operands[1]);

    int rt = get_register_index(operands[0]);
    int imm = atoi(operands[1]);

    i_lui(&r_array[rt], imm);

}

void execute_addi(char **operands, Register *r_array) {

    printf("Executing ADDI with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rs = get_register_index(operands[0]);
    int rt = get_register_index(operands[1]);
    int imm = atoi(operands[2]);

    i_addi(&r_array[rs], &r_array[rt], imm);

}

void execute_move(char **operands, Register *r_array) {

    printf("Executing MOVE with operands %s, %s\n", operands[0], operands[1]);

    int rd = get_register_index(operands[0]);
    int rs = get_register_index(operands[1]);

    move(&r_array[rd], &r_array[rs]);

}

void execute_slt(char **operands, Register *r_array) {

    printf("Executing SLT with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rd = get_register_index(operands[0]);
    int rs = get_register_index(operands[1]);
    int rt = get_register_index(operands[2]);

    slt(&r_array[rs], &r_array[rt], &r_array[rd]);

}

void execute_slti(char **operands, Register *r_array) {

    printf("Executing SLTI with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rs = get_register_index(operands[0]);
    int rt = get_register_index(operands[1]);
    int imm = atoi(operands[2]);

    slti(&r_array[rs], &r_array[rt], imm);

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

void move(Register *rd, Register *rs) {

    rd->value = rs->value;

}

void slt(Register *rs, Register *rt, Register *rd) {

    rd->value = rs->value < rt->value ? 1 : 0;

}

void slti(Register *rs, Register *rt, int imm) {

    rt->value = rs->value < imm ? 1 : 0;

}