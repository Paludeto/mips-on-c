#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "register.h"
#include <stdio.h>

typedef enum InstructionType {
    R,
    I,
    J
} InstructionType;

// Operands for specified R and I instructions
typedef struct Operand {
    Register r;
    int32_t i; 
} Operand;

typedef struct Instruction {
    char opcode[10]; 
    InstructionType type;
    Operand params[3][20];
    int param_count;
} Instruction;

// Branching (?) not sure if we'll implement it
typedef struct Label {
    char name[256];
    uint32_t line;
} Label;

void syscall(Instruction *inst, Register *arg, Register *dest);
void binary(Instruction inst);

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