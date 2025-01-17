#ifndef INSTRUCTION_LIST_H
#define INSTRUCTION_LIST_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "register.h"
#include "label_list.h"

typedef enum InstructionType {
    R,
    I,
    J,
    P,
    UNKNOWN
} InstructionType;

// Dispatcher pattern, where we map the instruction's name to a function in a table via function pointers
// Each instruction has its own executor function in the table
typedef struct Instruction {
    char *name;
    char **operands;
    InstructionType type;
    int op_count;
    // Generalize second parameter to take label into account
    void (*basic_executor)(char **operands, Register *r_array); 
    void (*label_executor)(char **operands, Register *r_array, LabelList *label_list);
} Instruction;

typedef struct Node {
    Instruction *instruction;  // Use pointer to Instruction
    struct Node *next;
} Node;

typedef struct InstructionList {
    Node *head;
    int size;
} InstructionList;

// Function declarations
void init_instruction_list(InstructionList *list);
void add_instruction(InstructionList *list, struct Instruction *inst);
void print_instruction_list(const InstructionList *list);
void free_instruction(Instruction *inst);
void free_instruction_list(InstructionList *list);
Instruction *create_instruction(const char *name, InstructionType type, char **operands, int op_count);
Instruction *find_instruction(const char *name);

// BLOAT
void binary(Instruction inst);

#endif