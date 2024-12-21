#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parser.h"

#define MAX_INPUT_SIZE 256

int main() {

    char line1[] = "addi $t1, $t1, -5\n";
    char line2[] = "addi $t2, $t2, -5\n";
    char line3[] = "add $t1, $t2, $t3\n";
    char line4[] = "mult $t1, $t3, $t3\n";
    char line5[] = "addi $t3, $t3, -48\n";

    Register r_array[32];
    InstructionList inst_list;

    init_instruction_list(&inst_list);
    init_registers(r_array);

    // Instruction testing
    tokenize_line(line1, r_array, &inst_list);
    tokenize_line(line2, r_array, &inst_list);
    tokenize_line(line3, r_array, &inst_list);
    tokenize_line(line4, r_array, &inst_list);
    tokenize_line(line5, r_array, &inst_list);

    print_instruction_list(&inst_list);

    printf("Value of %s: %d\n", r_array[11].name, r_array[11].value);
    
    return 0;

}