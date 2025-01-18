#include "instructions.h"
#include "executors.h"

// Instruction table
Instruction table[] = {
    {"add", R, 0x00, 0x20, 3},   // R-type: opcode = 0x00, funct = 0x20
    {"sub", R, 0x00, 0x22, 3},   // R-type: opcode = 0x00, funct = 0x22
    {"and", R, 0x00, 0x24, 3},   // R-type: opcode = 0x00, funct = 0x24
    {"or", R, 0x00, 0x25, 3},    // R-type: opcode = 0x00, funct = 0x25
    {"sll", R, 0x00, 0x00, 3},   // R-type: opcode = 0x00, funct = 0x00 (shift left logical)
    {"slt", R, 0x00, 0x2A, 3},   // R-type: opcode = 0x00, funct = 0x2A (set on less than)
    {"mult", R, 0x00, 0x18, 2},  // R-type: opcode = 0x00, funct = 0x18, 2 operands 
    {"addi", I, 0x08, 0x00, 3},  // I-type: opcode = 0x08, funct = N/A
    {"slti", I, 0x0A, 0x00, 3},  // I-type: opcode = 0x0A, funct = N/A
    {"lui", I, 0x0F, 0x00, 2},   // I-type: opcode = 0x0F, funct = N/A (load upper immediate)
    {"lw", I, 0x23, 0x00, 2},    // I-type: opcode = 0x23, funct = N/A (load word)
    {"sw", I, 0x2B, 0x00, 2},    // I-type: opcode = 0x2B, funct = N/A (store word)
    {"li", P, 0x00, 0x00, 2},    // Pseudo-instruction: Needs translation
    {"la", P, 0x00, 0x00, 2},    // Pseudo-instruction: Needs translation
    {"syscall", SYS, 0x00, 0x0C, 0}, // System call
    {NULL, UNKNOWN, 0x00, 0x00, 0}   // Sentinel to mark the end
};
// Checks if instruction is in the table
Instruction *find_instruction(const char *name) {

    for (int i = 0; table[i].name != NULL; i++) {
        if (strcmp(name, table[i].name) == 0) {
            return &table[i];
        }
    }

    return NULL;

}