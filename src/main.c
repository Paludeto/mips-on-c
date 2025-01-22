#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "executors.h"
#include "register.h"

int main(void) {
  
	init_registers();

	parse_file("test.s");
	
	execute_instructions();

	print_reg_table();

	return 0;

}