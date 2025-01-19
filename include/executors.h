// executors.h
#ifndef EXECUTORS_H
#define EXECUTORS_H

#include "parser.h"    // Assuming parser.h defines Register, LabelList, etc.
#include "register.h"
#include "memory.h"    // Include memory functions

// Function prototypes for executors
void execute_add(char **operands, Register *r_array);
void execute_sub(char **operands, Register *r_array);
void execute_mult(char **operands, Register *r_array);
void execute_and(char **operands, Register *r_array);
void execute_or(char **operands, Register *r_array);
void execute_sll(char **operands, Register *r_array);
void execute_lui(char **operands, Register *r_array);
void execute_addi(char **operands, Register *r_array);
void execute_move(char **operands, Register *r_array);
void execute_slt(char **operands, Register *r_array);
void execute_slti(char **operands, Register *r_array);
void execute_la(char **operands, Register *r_array, Label *label_arr);
void execute_lw(char **operands, Register *r_array);
void execute_sw(char **operands, Register *r_array);
void execute_syscall(char **operands, Register *r_array);
void execute_li(char **operands, Register *r_array);

#endif // EXECUTORS_H
