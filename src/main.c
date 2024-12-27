#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parser.h"

#define MAX_INPUT_SIZE 256

int main() {

    Register r_array[32];
    InstructionList inst_list;
    LabelList label_list;

    char line1[] = "move $t0, $zero";
    char line2[] = "addi $t0, $t0, 5";

    init_instruction_list(&inst_list);
    init_registers(r_array);
    init_label_list(&label_list);

    tokenize_line(line1, r_array, &inst_list, &label_list);
    tokenize_line(line2, r_array, &inst_list, &label_list);

    printf("%s: %d\n", r_array[8].name, r_array[8].value);
    
    return 0;

}