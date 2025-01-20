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

// Actual instructions
typedef struct Instruction {

    InstructionType type;

    union {
        uint8_t funct;    
        uint16_t imm;      
        uint32_t address;  
    } value;             

    uint8_t opcode;        
    uint8_t rs, rt, rd;

} Instruction;

typedef struct InstructionInfo {
    
    char *name;
    InstructionType type;
    uint8_t opcode;
    uint8_t funct;
    uint8_t op_count;
    
} InstructionInfo;

InstructionInfo *find_instruction(const char *name);

#endif