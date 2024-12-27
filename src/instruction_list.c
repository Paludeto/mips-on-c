#include "instruction_list.h"
#include "executors.h"

// Instruction table
Instruction table[] = {
    {"add", NULL, R, 3, execute_add, NULL},
    {"sub", NULL, R, 3, execute_sub, NULL},
    {"mult", NULL, R, 3, execute_mult, NULL},
    {"and", NULL, R, 3, execute_and, NULL},
    {"or", NULL, R, 3, execute_or, NULL},
    {"sll", NULL, R, 3, execute_sll, NULL},
    {"lui", NULL, I, 2, execute_lui, NULL},
    {"addi", NULL, I, 3, execute_addi, NULL},
    {"move", NULL, R, 2, execute_move, NULL},
    {"slt", NULL, R, 3, execute_slt, NULL},
    {"slti", NULL, I, 3, execute_slti, NULL},
    {NULL, NULL, UNKNOWN, 0, NULL} // Sentinel to mark the end
};

// Initialize the instruction list
void init_instruction_list(InstructionList *list) {

    list->head = NULL;
    list->size = 0;

}

// Add an instruction to the list
void add_instruction(InstructionList *list, struct Instruction *inst) {

    Node *new_node = (Node *)malloc(sizeof(Node));

    if (!new_node) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return;
    }

    new_node->instruction = inst;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }

    list->size++;

}

// Creates instruction object
Instruction *create_instruction(const char *name, char **operands, int op_count) {

    Instruction *new_inst = malloc(sizeof(Instruction));
    new_inst->name = strdup(name);
    new_inst->operands = malloc(sizeof(char *) * op_count);

    for (int i = 0; i < op_count; i++) {
        new_inst->operands[i] = strdup(operands[i]);
    }

    return new_inst;

}

// Print all instructions in the list
void print_instruction_list(const InstructionList *list) {

    Node *current = list->head;
    int index = 1;

    while (current != NULL) {

        struct Instruction *inst = current->instruction;
        printf("Instruction %d: %s", index++, inst->name);
        for (int i = 0; i < inst->op_count; i++) {
            printf(" %s", inst->operands[i]);
        }
        printf(", type %d\n", inst->type);
        current = current->next;

    }

}

// Free all nodes in the list
void free_instruction_list(InstructionList *list) {

    Node *current = list->head;

    while (current != NULL) {

        Node *temp = current;
        current = current->next;
        free(temp);

    }

    list->head = NULL;
    list->size = 0;

}

// Checks if instruction is in the table
Instruction *find_instruction(const char *name) {

    for (int i = 0; table[i].name != NULL; i++) {
        if (strcmp(name, table[i].name) == 0) {
            return &table[i];
        }
    }

    return NULL;

}


// TO-DO: implement behavior
void syscall(Instruction *inst, Register *arg, Register *dest);
void binary(Instruction inst);