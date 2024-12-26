#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parser.h"

#define MAX_INPUT_SIZE 256

int main() {

    Register r_array[32];
    InstructionList inst_list;
    LabelList label_list;

    char line1[] = ".data\ntest: .word 1, 2, 3, 4\n";

    init_instruction_list(&inst_list);
    init_registers(r_array);
    init_label_list(&label_list);

    tokenize_line(line1, r_array, &inst_list, &label_list);

    while (label_list.head) {
        printf("Label: %s, Address: %d\n", label_list.head->label.name, label_list.head->label.address[0]);
        label_list.head = label_list.head->next;
    }
    
    return 0;

}