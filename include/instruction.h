#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "register.h"
#include <stdio.h>

#define INSTR_SIZE 32

typedef enum InstructionType {
    R,
    I,
    J
} InstructionType;

typedef struct Instruction {
    char opcode[10]; 
    InstructionType type;
    char params[3][20];
    int paramCount;
} Instruction;

// Branching
typedef struct Label {
    char name[256];
    uint32_t line;
} Label;

// Operands for specified R and I instructions
typedef struct Operand {
    union {
        Register r;
        int32_t i;
    };
} Operand;

void syscall(int i, Register arg, Register *v0);
void init_instruction(Instruction *inst);
void binary(Instruction inst);
void r_add(Register *rs, Register *rd, Register *rt);
void r_sub(Register *rs, Register *rd, Register *rt);
void r_mult(Register *rs, Register *rd, Register *rt);
void r_and(Register *rs, Register *rd, Register *rt);
void r_or(Register *rs, Register *rd, Register *rt);
void r_sll(Register *rs, Register *rd, int shamt);
void i_addi(Register *rs, Register *rt, int immediate);

#endif