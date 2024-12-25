#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parser.h"

#define MAX_INPUT_SIZE 256

int main() {

    //t1 = 1, t2 = 2 defined later in the code
    char add[] = "add $t0, $t1, $t2\n"; // $t0 = $t1 + $t2 (3)
    char sub[] = "sub $t1, $t0, $t2\n";  // $t1 = $t0 - $t2 (1)
    char mult[] = "mult $t0, $t1, $t2\n";   // $t0 = $t1 * $t2 (2)
    char and[] = "and $t5, $t3, $t4\n"; // $t3 = $t4 & $t5 (1)
    char or[] = "or $t6, $t3, $t4\n"; // $t6 = $t3 | $t4 (1)

    Register r_array[32];
    InstructionList inst_list;

    init_instruction_list(&inst_list);
    init_registers(r_array);

    r_array[9].value = 1;
    r_array[10].value = 2;

    // and, $t3 and $t4, stores in $t5(13) and &t6 (14) respectively 
    r_array[11].value = 1;
    r_array[12].value = 1;

    tokenize_line(add, r_array, &inst_list);
    tokenize_line(sub, r_array, &inst_list);
    tokenize_line(mult, r_array, &inst_list);
    tokenize_line(and, r_array, &inst_list);
    tokenize_line(or, r_array, &inst_list);


    // Unused for now
    print_instruction_list(&inst_list);

    // R-type arithmetics
    printf("Value of %s: %d\n", r_array[8].name, r_array[8].value);

    // R-type bitwise
    printf("Value of %s: %d\n", r_array[13].name, r_array[13].value);
    printf("Value of %s: %d\n", r_array[14].name, r_array[14].value);
    
    return 0;

}