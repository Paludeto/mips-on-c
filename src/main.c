#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parser.h"

#define MAX_INPUT_SIZE 256

int main() {

    Register r_array[32];
    InstructionList inst_list;
    LabelList label_list;

    init_instruction_list(&inst_list);
    init_registers(r_array);
    init_label_list(&label_list);

    parseFile("test.s", r_array, &inst_list, &label_list);

    print_label_list(&label_list);
    print_instruction_list(&inst_list);
    
    free_instruction_list(&inst_list);
    free_label_list(&label_list);

    return 0;

}