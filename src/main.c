#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parser.h"

int main() {

    char mips_code[] =   "label1: add $t0, $t1, $t2\n"
    "    lw $t0, 256($t1)\n"
    "label2: sub $t0, $t1, $t2\n"
    "beq $t0, $t1, label2\n"
    "addi $t0, $t0, 1\n";

    tokenize_line(mips_code);
    
    return 0;

}