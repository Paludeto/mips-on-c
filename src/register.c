#include <string.h>
#include <stdio.h>

#include "register.h"

Register r_array[REG_NUM];
uint32_t pc = 0;

const char *valid_registers[] = {
    "$zero", "$at", "$v0", "$v1",
    "$a0", "$a1", "$a2", "$a3",
    "$t0", "$t1", "$t2", "$t3",
    "$t4", "$t5", "$t6", "$t7",
    "$s0", "$s1", "$s2", "$s3",
    "$s4", "$s5", "$s6", "$s7",
    "$t8", "$t9", "$k0", "$k1",
    "$gp", "$sp", "$fp", "$ra",
    NULL // Sentinel
};

void init_registers() {

    for (int i = 0; valid_registers[i] != NULL; i++) {
        strncpy(r_array[i].name, valid_registers[i], 5);
        r_array[i].number = i;
        r_array[i].value = 0;
    }
    
}

void print_reg_table() {
    
	printf("+-----------+------------+\n");
	printf("| Register  | Value      |\n");
	printf("+-----------+------------+\n");

	for (int i = 0; i < REG_NUM; i++) {
		printf("| %-9s | %-10d |\n", r_array[i].name, r_array[i].value);
	}

	printf("+-----------+------------+\n");

}

// Obtains register index
int get_register_index(const char *reg) {
    
    for (int i = 0; valid_registers[i] != NULL; i++) {
        if (strcmp(reg, valid_registers[i]) == 0) {
            return i;
        }
    }

    return -1; // Return -1 if the register is invalid

}