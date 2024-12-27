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
    new_node->label.name = strdup(label->name);  // Copy name
    new_node->label.address = label->address;
    new_node->next = list->head;
    list->head = new_node;
    list->size++;

}

// Print all labels in the list
void print_label_list(LabelList *list) {

    LabelNode *current = list->head;

    while (current) {
        printf("Label: %s, Address: %d\n", current->label.name, current->label.address);
        current = current->next;
    }

}

Label *find_label(LabelList *list, const char *name) {

    LabelNode *current = list->head;

    while (current != NULL) {

        if (strcmp(current->label.name, name) == 0) {
            return &current->label; // Return the matching label
        }

        current = current->next;

    }

    return NULL; // Return NULL if no match is found

}

void free_label(Label *label) {

    if (label) {
        free(label->name);
        free(label);
    }
    
}

// Free all memory associated with the label list
void free_label_list(LabelList *list) {

    LabelNode *current = list->head;

    while (current) {

        LabelNode *next = current->next;

        // Free the label's name
        if (current->label.name) {
            free(current->label.name);
        }

        // Free the label's address (if dynamically allocated)
        if (current->label.address) {
            free(current->label.address);
        }

        // Free the node itself
        free(current);
        current = next;
         
    }

    list->head = NULL;
    list->size = 0;

}
