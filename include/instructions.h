#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdbool.h>
#include <stdint.h>

typedef enum InstructionType {
    R,
    I,
    J,
    P,
    UNKNOWN
} InstructionType;

// Actual instructions
typedef struct Instruction {

    uint8_t opcode;

    InstructionType type;

    union {

        struct {
            uint8_t rs;
            uint8_t rt;
            uint8_t rd;
            uint8_t shamt;
            uint8_t funct;
        } RType;

        struct {
            uint8_t rs;
            uint8_t rt;
            uint16_t imm;
        } IType;

        struct {
            uint32_t address;
        } JType;

        struct {

            uint8_t rt;
            bool is_label;

            union {
                uint32_t address;
                uint32_t imm;    
            } data;

        } PType;

    } value;

} Instruction;

typedef struct InstructionInfo {
    
    char *name;
    InstructionType type;
    uint8_t opcode;
    uint8_t funct;
    uint8_t op_count;
    
} InstructionInfo;

typedef void (*InstructionHandler)(Instruction);
extern InstructionHandler jump_table[];

InstructionInfo *find_instruction(const char *name);

#endif