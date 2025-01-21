#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parser.h"
#include "executors.h"

int main(void) {

	initialize_memory();         

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
		for (int i = 0; i < curr_label; i++) {
		printf("%s, %d\n", label_arr[i].name, label_arr[i].address);
	}

	return 0;

}