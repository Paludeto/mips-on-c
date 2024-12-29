// label_list.c
#include "label_list.h"

// Initialize the label list
void init_label_list(LabelList *list) {
    list->head = NULL; // Set the head pointer to NULL
    list->size = 0;    // Initialize size to 0
}

// Create a new label
Label *create_label(const char *name, uint32_t address) {

    Label *new_label = malloc(sizeof(Label));
    if (!new_label) {
        printf("Error: Memory allocation failed for label %s\n", name);
        return NULL;
    }

    // Allocate and copy the name
    new_label->name = malloc(strlen(name) + 1);

    if (!new_label->name) {
        printf("Error: Memory allocation failed for label name %s\n", name);
        free(new_label);
        return NULL;
    }
     
    strcpy(new_label->name, name);

    new_label->address = address; // Assign the address value

    return new_label;

}

// Add a label to the list
void add_label(LabelList *list, Label *label) {

    if (label == NULL) return; // Prevent adding NULL labels

    // Allocate memory for the new node
    LabelNode *new_node = malloc(sizeof(LabelNode));
    if (!new_node) {
        printf("Error: Memory allocation failed for LabelNode\n");
        return;
    }

    new_node->label = label;       // Set the label
    new_node->next = list->head;   // Insert at the beginning
    list->head = new_node;         // Update the head
    list->size++;                  // Increment the size

}

// Print all labels in the list
void print_label_list(const LabelList *list) {

    LabelNode *current = list->head;

    while (current) {
        printf("Label: %s, Address: 0x%X\n", current->label->name, current->label->address);
        current = current->next;
    }

}

// Find a label by name
Label *find_label(LabelList *list, const char *name) {

    LabelNode *current = list->head;

    while (current != NULL) {
        if (strcmp(current->label->name, name) == 0) {
            return current->label; // Return the matching label
        }
        current = current->next;
    }

    return NULL; // Label not found

}

// Free a single label
void free_label(Label *label) {

    if (label) {

        if (label->name) {
            free(label->name);
        }

        free(label);

    }

}

// Free all memory associated with the label list
void free_label_list(LabelList *list) {

    LabelNode *current = list->head;

    while (current) {

        LabelNode *next = current->next;

        // Free the label structure
        if (current->label) {
            free_label(current->label);
        }

        // Free the node itself
        free(current);
        current = next;

    }

    // Reset the list
    list->head = NULL;
    list->size = 0;

}