#include "label_list.h"

void init_label_list(LabelList *list) {

    list->head = NULL; // Set the head pointer to NULL
    list->size = 0;    // Initialize size to 0

}

Label *create_label(const char *name, int32_t *address) {

    Label *label = malloc(sizeof(Label));

    label->name = strdup(name);  // Copy name
    label->address = address;

    return label;

}

// Add a label to the list
void add_label(LabelList *list, Label *label) {

    LabelNode *new_node = (LabelNode *)malloc(sizeof(LabelNode));
    new_node->label = label;
    new_node->next = list->head;
    list->head = new_node;
    list->size++;

}

// Print all labels in the list
void print_label_list(LabelList *list) {

    LabelNode *current = list->head;

    while (current) {
        printf("Label: %s, Address: 0x%x\n", current->label->name, current->label->address);
        current = current->next;
    }

}

Label *find_label(LabelList *list, const char *name) {

    LabelNode *current = list->head;

    while (current != NULL) {

        if (strcmp(current->label->name, name) == 0) {
            return current->label; // Return the matching label
        }

        current = current->next;

    }

    return NULL; // Return NULL if no match is found

}

// Free all memory associated with the label list
void free_label_list(LabelList *list) {

    LabelNode *current = list->head;

    while (current) {
        LabelNode *next = current->next;

        // Free the label's fields
        if (current->label) {
            if (current->label->name) {
                free(current->label->name);
            }
            if (current->label->address) {
                free(current->label->address);
            }
            // Free the label structure itself
            free(current->label);
        }

        // Free the node itself
        free(current);
        current = next;
    }

    list->head = NULL;
    list->size = 0;

}
