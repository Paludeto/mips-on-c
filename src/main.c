#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parser.h"
#include "executors.h"
#include "encoder.h"

int main(void) {
  
	init_registers(r_array);

	parse_file("test.s");
	
	execute_instructions();

	// Table headers
	printf("+-----------+------------+\n");
	printf("| Register  | Value      |\n");
	printf("+-----------+------------+\n");

	// Table rows for each register
	for (int i = 0; i < REG_NUM; i++) {
		printf("| %-9s | %-10d |\n", r_array[i].name, r_array[i].value);
	}

	// Table footer
	printf("+-----------+------------+\n");

	return 0;

}