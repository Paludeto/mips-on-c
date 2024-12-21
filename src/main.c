#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parser.h"

int main() {

    char mips_code[] =   "add $t1, $t2, $t3";

    tokenize_line(mips_code);
    
    return 0;

}