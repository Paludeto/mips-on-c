#ifndef REGISTER_H
#define REGISTER_H

#include <stdint.h>

#define REG_NUM 32

extern uint32_t pc;

typedef struct Register {
    char name[5];
    __int32_t number;
    __int32_t value;
} Register;

extern Register r_array[REG_NUM];

void init_registers();
void print_reg_table();
int get_register_index(const char *reg);

#endif