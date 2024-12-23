#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "register.h"
#include <stdio.h>

typedef enum InstructionType {
    R,
    I,
    J,
    UNKNOWN
} InstructionType;

typedef struct Instruction {
    char *name; 
    char **operands;
    InstructionType type;
    int op_count;
} Instruction;

// For future use with command pattern
typedef struct InstructionTable {
    char *name;
    InstructionType type;
    int op_count;
    void (*executor)(char **operands, Register *r_array);  
} InstructionTable;

void syscall(Instruction *inst, Register *arg, Register *dest);
void binary(Instruction inst);

void execute_add(char **operands, Register *r_array);
void execute_sub(char **operands, Register *r_array);

// R-Type instructions
void r_add(Register *rs, Register *rt, Register *rd);
void r_sub(Register *rs, Register *rt, Register *rd);
void r_mult(Register *rs, Register *rt, Register *rd);
void r_and(Register *rs, Register *rt, Register *rd);
void r_or(Register *rs, Register *rt, Register *rd);
void r_sll(Register *rt, Register *rd, int shamt);

// I-Type instructions
void i_addi(Register *rs, Register *rt, int imm);
void i_lui(Register *rt, int16_t imm);

#endif