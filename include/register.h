#ifndef REGISTER_H
#define REGISTER_H

#include <stdint.h>

#define REG_NUM 32

/**
 * @brief Global program counter
 * 
 */
extern uint32_t pc;

/**
 * @brief Register structure
 * 
 */
typedef struct Register {
    char name[5];
    __int32_t number;
    __int32_t value;
} Register;

/**
 * @brief Global register array 
 * 
 */
extern Register r_array[REG_NUM];

/**
 * @brief Register operations
 * 
 */
void init_registers();
void print_reg_table();
int get_register_index(const char *reg);

#endif