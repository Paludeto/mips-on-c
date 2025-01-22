// executors.h
#ifndef EXECUTORS_H
#define EXECUTORS_H

#include "instructions.h"

// Function prototypes for executors
void execute_add(Instruction inst);
void execute_sub(Instruction inst);
void execute_mult(Instruction inst);
void execute_and(Instruction inst);
void execute_or(Instruction inst);
void execute_sll(Instruction inst);
void execute_lui(Instruction inst);
void execute_addi(Instruction inst);
void execute_slt(Instruction inst);
void execute_slti(Instruction inst);
void execute_la(Instruction inst);
void execute_lw(Instruction inst);
void execute_sw(Instruction inst);
void execute_syscall(Instruction inst);
void execute_li(Instruction inst);
void execute_pseudo_inst(Instruction inst);
void execute_j(Instruction inst);
void execute_instructions();

#endif // EXECUTORS_H
