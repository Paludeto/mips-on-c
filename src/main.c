#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parser.h"

#define MAX_INPUT_SIZE 256

int main() {

    char lui[] = "move $t0, $zero";

    Register r_array[32];
    InstructionList inst_list;

    init_instruction_list(&inst_list);
    init_registers(r_array);


    // Unused for now
    print_instruction_list(&inst_list);
    tokenize_line(lui, r_array, &inst_list);

    // R-type arithmetics
    printf("Value of %s: %d\n", r_array[8].name, r_array[8].value);

    // I-type arithmetics
    
    return 0;

}