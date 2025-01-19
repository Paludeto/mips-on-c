#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "register.h"
#include "label.h"

typedef enum InstructionType {
    R,
    I,
    J,
    P,
    SYS,
    UNKNOWN
} InstructionType;

// Dispatcher pattern, where we map the instruction's name to a function in a table via function pointers
// Each instruction has its own executor function in the table
typedef struct Instruction {
    char *name;
    InstructionType type;
    uint32_t opcode;
    uint32_t funct;
    uint32_t op_count;
} Instruction;

Instruction *find_instruction(const char *name);

#endif