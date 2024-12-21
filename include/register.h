#ifndef REGISTER_H
#define REGISTER_H

#include <stdint.h>
#include <string.h>

#define REG_NUM 32

typedef struct Register {
    char name[5];
    __int32_t number;
    __int32_t value;
} Register;

void init_registers(Register *regArray);

#endif