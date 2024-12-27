#ifndef EXECUTORS_H
#define EXECUTORS_H

#include "register.h"
#include "label_list.h"
#include <stdio.h>

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
void execute_slt(char **operands, Register *r_array);
void execute_slti(char **operands, Register *r_array);
void execute_la(char **operands, Register *r_array, LabelList *label_list);

#endif // EXECUTORS_H