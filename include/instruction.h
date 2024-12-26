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

// Dispatcher pattern, where we map the instruction's name to a function in a table via function pointers
// Each instruction has its own executor function in the table
typedef struct Instruction {
    char *name;
    char **operands;
    InstructionType type;
    int op_count;
    void (*executor)(char **operands, Register *r_array);  
} Instruction;

void syscall(Instruction *inst, Register *arg, Register *dest);
void binary(Instruction inst);

// R-Type instructions
void r_add(Register *rs, Register *rt, Register *rd);
void r_sub(Register *rs, Register *rt, Register *rd);
void r_mult(Register *rs, Register *rt, Register *rd);
void r_and(Register *rs, Register *rt, Register *rd);
void r_or(Register *rs, Register *rt, Register *rd);
void r_sll(Register *rt, Register *rd, int shamt);
void move(Register *rd, Register *rs);

// I-Type instructions
void i_addi(Register *rs, Register *rt, int imm);
void i_lui(Register *rt, int16_t imm);

// Instruction executors
void execute_add(char **operands, Register *r_array);
void execute_sub(char **operands, Register *r_array);
void execute_mult(char **operands, Register *r_array);
void execute_and(char **operands, Register *r_array);
void execute_or(char **operands, Register *r_array);
void execute_sll(char **operands, Register *r_array);
void execute_lui(char **operands, Register *r_array);
void execute_addi(char **operands, Register *r_array);
void execute_move(char **operands, Register *r_array);

// Instruction creation and validation
Instruction *find_instruction(const char *name);
Instruction *create_instruction(const char *name, char **operands, int op_count);
void free_instruction(Instruction *inst);

#endif