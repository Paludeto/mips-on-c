#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parser.h"

int main() {

    char mips_code[] =   "label1: add $t0, $t1, $t2\n"
    "    lw $t0, 0($t1)\n"
    "label2: sub $t0, $t1, $t2\n"
    "beq $t0, $t1, label2\n";

    tokenize_line(mips_code);
    
    return 0;

}