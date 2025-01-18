#include "instructions.h"
#include "executors.h"

// Instruction table
Instruction table[] = {
    {"add", NULL, R, 3},
    {"sub", NULL, R, 3},
    {"and", NULL, R, 3},
    {"or", NULL, R, 3},
    {"sll", NULL, R, 3},
    {"slt", NULL, R, 3},
    {"addi", NULL, I, 3},
    {"slti", NULL, I, 3},
    {"lui", NULL, I, 2},
    {"lw", NULL, I, 2},
    {"sw", NULL, I, 2},
    {"li", NULL, I, 2},
    {"move", NULL, P, 2},
    {"la", NULL, P, 2},
    {"mul", NULL, P, 3},
    {"syscall", NULL, SYS, 0}, // Added syscall here
    {NULL, NULL, UNKNOWN, 0} // Sentinel to mark the end
};

// Checks if instruction is in the table
Instruction *find_instruction(const char *name) {

    for (int i = 0; table[i].name != NULL; i++) {
        if (strcmp(name, table[i].name) == 0) {
            return &table[i];
        }
    }

    return NULL;

}