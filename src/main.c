#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parser.h"

#define MAX_INPUT_SIZE 256

int main() {

    Register r_array[32];
    InstructionList inst_list;

    char line1[] = "move $t0, $zero";
    char line2[] = "move $t1, $zero";
    char line3[] = "addi $t1, $t1, 5";
    char line4[] = "slt $t2, $t0, $t1";

    init_instruction_list(&inst_list);
    init_registers(r_array);

    tokenize_line(line1, r_array, &inst_list);
    tokenize_line(line2, r_array, &inst_list);
    tokenize_line(line3, r_array, &inst_list);
    tokenize_line(line4, r_array, &inst_list);

    // R-type arithmetics
    printf("Value of %s: %d\n", r_array[10].name, r_array[10].value);
    
    return 0;

}