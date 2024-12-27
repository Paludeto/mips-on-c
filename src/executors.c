#include "executors.h"
#include <stdio.h>

// Executors
void execute_add(char **operands, Register *r_array) {

    printf("Executing ADD with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rd = get_register_index(operands[0]);
    int rs = get_register_index(operands[1]);
    int rt = get_register_index(operands[2]);

    r_array[rd].value = r_array[rs].value + r_array[rt].value; // rd = rs + rt

}

void execute_sub(char **operands, Register *r_array) {

    printf("Executing SUB with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rd = get_register_index(operands[0]);
    int rs = get_register_index(operands[1]);
    int rt = get_register_index(operands[2]);

    r_array[rd].value = r_array[rs].value - r_array[rt].value; // rd = rs - rt

}

void execute_mult(char **operands, Register *r_array) {

    printf("Executing MULT with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rd = get_register_index(operands[0]);
    int rs = get_register_index(operands[1]);
    int rt = get_register_index(operands[2]);

    r_array[rd].value = r_array[rs].value * r_array[rt].value; // rd = rs * rt

}

void execute_and(char **operands, Register *r_array) {

    printf("Executing AND with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rd = get_register_index(operands[0]);
    int rs = get_register_index(operands[1]);
    int rt = get_register_index(operands[2]);


    r_array[rd].value = r_array[rs].value & r_array[rt].value; // rd = rs & rt
}

void execute_or(char **operands, Register *r_array) {

    printf("Executing OR with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rd = get_register_index(operands[0]);
    int rs = get_register_index(operands[1]);
    int rt = get_register_index(operands[2]);

    r_array[rd].value = r_array[rs].value | r_array[rt].value; // rd = rs | rt

}

void execute_sll(char **operands, Register *r_array) {

    printf("Executing SLL with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rd = get_register_index(operands[0]);
    int rt = get_register_index(operands[1]);
    int shamt = atoi(operands[2]);

    if (shamt < 0 || shamt > 31) {
        printf("SHAMT must be between 0 and 31\n");
        return;
    }

    r_array[rd].value = r_array[rt].value << shamt; // rd = rt << shamt

}

void execute_lui(char **operands, Register *r_array) {

    printf("Executing LUI with operands %s, %s\n", operands[0], operands[1]);

    int rt = get_register_index(operands[0]);
    int imm = atoi(operands[1]);

    r_array[rt].value = (int32_t)imm << 16; // rt = imm << 16

}

void execute_addi(char **operands, Register *r_array) {

    printf("Executing ADDI with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rt = get_register_index(operands[0]);
    int rs = get_register_index(operands[1]);
    int imm = atoi(operands[2]);

    r_array[rt].value = r_array[rs].value + imm; // rt = rs + imm

}

void execute_move(char **operands, Register *r_array) {

    printf("Executing MOVE with operands %s, %s\n", operands[0], operands[1]);

    int rd = get_register_index(operands[0]);
    int rs = get_register_index(operands[1]);
  

    r_array[rd].value = r_array[rs].value; // rd = rs
    
}

void execute_slt(char **operands, Register *r_array) {

    printf("Executing SLT with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rd = get_register_index(operands[0]);
    int rs = get_register_index(operands[1]);
    int rt = get_register_index(operands[2]);

    r_array[rd].value = r_array[rs].value < r_array[rt].value ? 1 : 0; // rd = (rs < rt) ? 1 : 0

}

void execute_slti(char **operands, Register *r_array) {

    printf("Executing SLTI with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rt = get_register_index(operands[0]);
    int rs = get_register_index(operands[1]);
    int imm = atoi(operands[2]);

    r_array[rt].value = r_array[rs].value < imm ? 1 : 0; // rt = (rs < imm) ? 1 : 0

}
