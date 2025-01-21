#include "instructions.h"
#include "executors.h"

InstructionInfo table[] = {
    {"add",  R, 0x00, 0x20, 3},   // R-type: opcode = 0x00, funct = 0x20
    {"sub",  R, 0x00, 0x22, 3},   // R-type: opcode = 0x00, funct = 0x22
    {"and",  R, 0x00, 0x24, 3},   // R-type: opcode = 0x00, funct = 0x24
    {"or",   R, 0x00, 0x25, 3},   // R-type: opcode = 0x00, funct = 0x25
    {"sll",  R, 0x00, 0x00, 3},   // R-type: opcode = 0x00, funct = 0x00 (shift left logical)
    {"slt",  R, 0x00, 0x2A, 3},   // R-type: opcode = 0x00, funct = 0x2A (set on less than)
    {"mult", R, 0x00, 0x18, 2},   // R-type: opcode = 0x00, funct = 0x18, 2 operands 

    {"addi", I, 0x08, 0x00, 3},   // I-type: opcode = 0x08, funct = N/A
    {"slti", I, 0x0A, 0x00, 3},   // I-type: opcode = 0x0A, funct = N/A
    {"lui",  I, 0x0F, 0x00, 2},   // I-type: opcode = 0x0F, funct = N/A (load upper immediate)
    {"lw",   I, 0x23, 0x00, 2},   // I-type: opcode = 0x23, funct = N/A (load word)
    {"sw",   I, 0x2B, 0x00, 2},   // I-type: opcode = 0x2B, funct = N/A (store word)

    {"j",    J, 0x02, 0x00, 1},

    {"li",   P, 0x00, 0x00, 2},   // Pseudo-instruction: Needs translation
    {"la",   P, 0x00, 0x00, 2},   // Pseudo-instruction: Needs translation

    {"syscall", SYS, 0x00, 0x0C, 0}, // System call

    {NULL, UNKNOWN, 0x00, 0x00, 0}  // Sentinel to mark the end
};  

InstructionHandler jump_table[64] = {

    [0x20] = execute_add,   // R-type ADD (funct 0x20)
    [0x22] = execute_sub,   // R-type SUB (funct 0x22)
    [0x24] = execute_and,   // R-type AND (funct 0x24)
    [0x25] = execute_or,    // R-type OR (funct 0x25)
    [0x00] = execute_sll,   // R-type SLL (funct 0x00)
    [0x2A] = execute_slt,   // R-type SLT (funct 0x2A)
    [0x18] = execute_mult,  // R-type MULT (funct 0x18)
    
    [0x08] = execute_addi,  // I-type ADDI (opcode 0x08)
    [0x0A] = execute_slti,  // I-type SLTI (opcode 0x0A)
    [0x0F] = execute_lui,   // I-type LUI (opcode 0x0F)
    [0x23] = execute_lw,    // I-type LW (opcode 0x23)
    [0x2B] = execute_sw,    // I-type SW (opcode 0x2B)
    
    // [0x02] = execute_j,     // J-type J (opcode 0x02) 

};

// Checks if instruction is in the table
InstructionInfo *find_instruction(const char *name) {

    for (int i = 0; table[i].name != NULL; i++) {
        if (strcmp(name, table[i].name) == 0) {
            return &table[i];
        }
    }

    return NULL;

}