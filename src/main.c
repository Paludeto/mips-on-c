#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parser.h"

#define MAX_INPUT_SIZE 256

int main() {

    Register r_array[32];
    InstructionList inst_list;
    LabelList label_list;

    char line1[] = ".data:\narray: .word 1, 2, 3, 4, 5\n";
    char line2[] = "la $t0, array\n";
    char line3[] = "lw $t1, 4($t0)\n";
    char line4[] = "move $t2, $zero";
    char line5[] = "sw $t2, 4($t0)";

    init_instruction_list(&inst_list);
    init_registers(r_array);
    init_label_list(&label_list);

    tokenize_line(line1, r_array, &inst_list, &label_list);
    tokenize_line(line2, r_array, &inst_list, &label_list);
    tokenize_line(line3, r_array, &inst_list, &label_list);
    tokenize_line(line4, r_array, &inst_list, &label_list);
    tokenize_line(line5, r_array, &inst_list, &label_list);

    print_label_list(&label_list);
    print_instruction_list(&inst_list);
    
    free_instruction_list(&inst_list);
    free_label_list(&label_list);

    return 0;

}