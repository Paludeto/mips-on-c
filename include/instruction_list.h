#ifndef INSTRUCTION_LIST_H
#define INSTRUCTION_LIST_H

// This is for debugging purposes, we should probably use some sort of 
#include "instruction.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Node {
    Instruction instruction;
    struct Node *next;
} Node;

typedef struct InstructionList {
    Node *head;
    int size;
} InstructionList;

void init_instruction_list(InstructionList *list);
void add_instruction(InstructionList *list, Instruction *inst);
void print_instruction_list(InstructionList *list);
void free_instruction_list(InstructionList *list);

#endif 