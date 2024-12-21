#include "instruction.h"

// TO-DO
void init_instruction(Instruction *inst);
void syscall(Instruction *inst, Register *arg, Register *dest);
void binary(Instruction inst);
void r_add(Register *rs, Register *rd, Register *rt);
void r_sub(Register *rs, Register *rd, Register *rt);
void r_mult(Register *rs, Register *rd, Register *rt);
void r_and(Register *rs, Register *rd, Register *rt);
void r_or(Register *rs, Register *rd, Register *rt);
void r_sll(Register *rs, Register *rd, int shamt);
void i_addi(Register *rs, Register *rt, int imm);