#include "instruction.h"

// TO-DO
void syscall(Instruction *inst, Register *arg, Register *dest);
void binary(Instruction inst);

// R-Type Instructions

void r_add(Register *rs, Register *rt, Register *rd) {
    rd->value = rs->value + rt->value; // rd = rs + rt
}

void r_sub(Register *rs, Register *rt, Register *rd) {
    rd->value = rs->value - rt->value; // rd = rs - rt
}

void r_mult(Register *rs, Register *rt, Register *rd) {
    rd->value = rs->value * rt->value; // rd = rs * rt
}

void r_and(Register *rs, Register *rt, Register *rd) {
    rd->value = rs->value & rt->value; // rd = rs & rt
}

void r_or(Register *rs, Register *rt, Register *rd) {
    rd->value = rs->value | rt->value; // rd = rs | rt
}

void r_sll(Register *rt, Register *rd, int shamt) {

    if (shamt < 0 || shamt > 31) {
        printf("SHAMT must be between 0 and 31\n");
        return;
    }

    rd->value = rt->value << shamt; // rd = rt << shamt

}

// I-Type Instructions

void i_addi(Register *rs, Register *rt, int imm) {

    rt->value = rs->value + imm; // rt = rs + imm
    
}

void i_lui(Register *rt, int16_t imm) {

    rt->value = (int32_t)imm << 16; // rt = imm << 16 (upper 16 bits)

}