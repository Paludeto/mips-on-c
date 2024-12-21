#include <register.h>

void init_registers(Register *r_arr) {

    const char *names[] = {
        "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3",
        "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
        "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
        "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"
    };

    for (int i = 0; i < REG_NUM; i++) {
        strncpy(r_arr[i].name, names[i], 5);
        r_arr[i].number = i;
    }

}