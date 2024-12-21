#include "instruction_list.h"

// Initialize the instruction list
void init_instruction_list(InstructionList *list) {

    list->head = NULL;
    list->size = 0;
}

// Add an instruction to the list
void add_instruction(InstructionList *list, Instruction *inst) {

    Node *new_node = (Node *)malloc(sizeof(Node));

    if (!new_node) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return;
    }

    new_node->instruction = *inst;
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

// Print all instructions in the list
void print_instruction_list(InstructionList *list) {

    Node *current = list->head;
    int index = 1;
    while (current != NULL) {

        if (current->instruction.type == R) {
            printf("Instruction %d: %s", index++, current->instruction.opcode);
            printf(" %s", current->instruction.params[0]);
            printf(" %s", current->instruction.params[1]);
            printf(" %s", current->instruction.params[2]);
            printf(", type %d\n", current->instruction.type);
        } else if (current->instruction.type == I) {
            printf("Instruction %d: %s", index++, current->instruction.opcode);
            printf(" %s", current->instruction.params[0]->r.name);
            printf(" %s", current->instruction.params[1]->r.name);
            printf(" %d", current->instruction.params[2]->i);
            printf(", type %d\n", current->instruction.type);
        }
        
        current = current->next;
    }

}

// Free all nodes in the list
void free_instruction_list(InstructionList *list) {

    Node *current = list->head;
    Node *temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->size = 0;

}
