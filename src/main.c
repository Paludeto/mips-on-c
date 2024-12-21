#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parser.h"

#define MAX_INPUT_SIZE 256

int main() {

    char mips_code[MAX_INPUT_SIZE];

    if (fgets(mips_code, MAX_INPUT_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    size_t len = strlen(mips_code);
    if (len > 0 && mips_code[len - 1] == '\n') {
        mips_code[len - 1] = '\0';
    }

    Register r_array[32];
    InstructionList inst_list;

    init_instruction_list(&inst_list);
    init_registers(r_array);

    r_array[9].value = 2;
    r_array[10].value = 3; 

    tokenize_line(mips_code, r_array, &inst_list);

    print_instruction_list(&inst_list);

    printf("Value of %s: %d\n", r_array[11].name, r_array[11].value);
    
    return 0;

}