#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parser.h"

#define MAX_INPUT_SIZE 256

int main() {

    char add[] = "add $t0, $t1, $t2\n";
    char sub[] = "sub $t1, $t0, $t2\n";

    Register r_array[32];
    InstructionList inst_list;

    init_instruction_list(&inst_list);
    init_registers(r_array);

    r_array[9].value = 1;
    r_array[10].value = 2;

    tokenize_line(add, r_array, &inst_list);
    tokenize_line(sub, r_array, &inst_list);

    // Unused for now
    print_instruction_list(&inst_list);

    printf("Value of %s: %d\n", r_array[9].name, r_array[9].value);
    
    return 0;

}