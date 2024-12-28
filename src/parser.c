#include "parser.h"

// this crap should be temporary until we figure out how to modularize it
#define MAX_OP 4
#define MAX_DIR 100

void parseFile(char *file_name, Instruction *inst_arr, Register *r_array) {

    FILE *fp = fopen(file_name, "r");

    if (fp == NULL) {
        perror("File could not be opened\n");
        return;
    }

    // TO-DO (file parsing)

}

void tokenize_line(char *line, Register *r_array, InstructionList *inst_list, LabelList *label_list) {

    const char delimiters[] = " \t,\n"; // Define delimiters
    char *token = strtok(line, delimiters); // Get the first token
    
    while (token != NULL) {
        
        // If token is an instruction
        if (find_instruction(token) != NULL) {
            // Parse operands
            char *instruction = token;
            char *operands[MAX_OP]; // Assume a maximum of 10 operands
            int operand_count = 0;
        
            while ((token = strtok(NULL, delimiters)) != NULL) {

                operands[operand_count++] = token;

            }

            // Validate instruction syntax and execute it
            validate_execute_inst(instruction, operands, operand_count, r_array, inst_list, label_list);

        }
       
        // This is where this POS gets hacky
        if (token != NULL && is_data_field(token)) {

            char *args[MAX_DIR];
            int arg_count = 0;

            while ((token = strtok(NULL, delimiters)) != NULL) {
                args[arg_count++] = token;
            }   // adds label + directives to an array

            if (arg_count > MAX_DIR) {
                printf("Too many directives\n");
                return;
            }

            validate_data_field(line, args, arg_count, label_list);
           
        }

      
        token = strtok(NULL, delimiters); // Get the next token from where previous strtok left off       

    }

}

// TO-DO: be customized according to instruction type
bool validate_operands(const Instruction *inst_def, char **operands, int operand_count) {

    if (inst_def->op_count != operand_count) {
        printf("Error: %s expects %d operands, found %d\n", inst_def->name, inst_def->op_count, operand_count);
        return false;
    }

    if (inst_def->type == R) {  
        
        if (operand_count == 3) { 
            // Checks first two operands are registers
            if (get_register_index(operands[0]) == -1 || get_register_index(operands[1]) == -1) {
                printf("Error: Invalid register(s) for instruction %s\n", inst_def->name);
                return false;
            }

            // Checks if third operand is a register or int value
            if (get_register_index(operands[2]) == -1 && !is_imm(operands[2])) {
                printf("Error: Invalid register for instruction %s\n", inst_def->name);
                return false;
            }

            return true;
        }

        if (operand_count == 2) {
            
            if (get_register_index(operands[0]) == -1 || get_register_index(operands[1]) == -1) {
                printf("Error: Invalid register(s) for instruction %s\n", inst_def->name);
                return false;
            }

            return true;

        }
    } 

    if (inst_def->type == I) {
        
        if (operand_count == 3) {

            // Checks first two operands are registers
            if (get_register_index(operands[0]) == -1 || get_register_index(operands[1]) == -1) {
                printf("Error: Invalid register(s) for instruction %s\n", inst_def->name);
                return false;
            }

            // Checks if third operand is an immediate value
            if (!is_imm(operands[2])) {
                printf("Error: Invalid immediate value for instruction %s\n", inst_def->name);
                return false;
            }

            return true;

        } 

        if (operand_count == 2 && strcmp(inst_def->name, "lw") != 0 && strcmp(inst_def->name, "sw") != 0) {

            if (get_register_index(operands[0]) == -1 || !is_imm(operands[1])) {
                return false;
            }

            return true;

        } else if (operand_count == 2 && (strcmp(inst_def->name, "lw") == 0 || strcmp(inst_def->name, "sw") == 0)) {

            if (get_register_index(operands[0]) == -1 || !is_address(operands[1])) {
                return false;
            }

            return true;

        }
    
        return true;

    }

    if (inst_def->type == P) {
        
        if (operand_count == 2 && get_register_index(operands[0]) != -1) {
            return true;
        }

    }

    return true;

}

// Validates and executes an instruction
void validate_execute_inst(const char *instruction, char **operands, int operand_count, Register *r_array, InstructionList *inst_list, LabelList *label_list) {

    Instruction *inst_def = find_instruction(instruction);

    if (!inst_def) {
        printf("Error: Unknown instruction: %s\n", instruction);
        return;
    }

    // TO-DO: Modularize according to instruction type
    if (!validate_operands(inst_def, operands, operand_count)) {
        return;
    }

    Instruction *inst = create_instruction(instruction, inst_def->type, operands, operand_count);

    if (inst_def->basic_executor != NULL) {
        inst_def->basic_executor(inst->operands, r_array);
    } else if (inst_def->label_executor != NULL) {
        inst_def->label_executor(inst->operands, r_array, label_list);
    }
    
    // Adds instruction to linked-list
    add_instruction(inst_list, inst);
    
}

void validate_data_field(const char *token, char **args, int arg_count, LabelList *label_list) {

    if (!is_label(args[0]) || !is_directive(args[1])) {
        printf("Error: Invalid data field\n");
        return;
    }

    __int32_t *memchunk = malloc(sizeof(__int32_t)* (arg_count - 2));

    if (strcmp(args[1], ".word") == 0) {

        for (int i = 2; i < arg_count; i++) {

            if (!is_imm(args[i])) {
                printf("Error: Invalid immediate value\n");
                free(memchunk);
                return;
            } 

            memchunk[i - 2] = atoi(args[i]);

        }

    } else {
        printf("Invalid directive\n");
        return;
    }

    size_t len = strlen(args[0]);
    char *stripped_name = strdup(args[0]); // Duplicate the string

    if (stripped_name[len - 1] == ':') {
        stripped_name[len - 1] = '\0'; // Remove the trailing ':'
    }

    Label *newLabel = create_label(stripped_name, memchunk);
    free(stripped_name);

    add_label(label_list, newLabel);

}

// Used to test each token's parse
// void test_fn(char *token) {

//     if (is_data_field(token)) {
//         printf("Data field: %s\n", token);
//     }

//     if (is_directive(token)) {
//         printf("Directive: %s\n", token);
//     }

//     if (is_text_field(token)) {
//         printf("Text field: %s\n", token);
//     }
    
//     if (is_label(token)) {
//         printf("Label: %s\n", token);
//     }

//     if (is_op(token)) {
//         printf("Operand: %s\n", token);
//     }

//     if (is_address(token)) {
//         printf("Address: %s\n", token);
//     }

// }

bool is_label(const char *token) {

    if (token == NULL) {
        return false;
    }

    for (int i = 0; token[i] != '\0'; i++) {
        if (token[i] == ':') {
            return true;
        }
    }

    return false;

}

bool is_op(const char *token) {

    if (token == NULL) {
        return false;
    }

    if (get_register_index(token) == -1) {
        return false;
    }

    return is_imm(token);

}

bool is_imm(const char *token) {

    if (*token == '-' || *token == '+') {
        token++;
    }

    if (token == NULL || *token == '\0') {
        return false;       
    }

    while (*token) {
        if (!isdigit(*token)) {
            return false;
        }
        token++;
    }

    return true;

}

bool is_address(const char *token) {

    if (token == NULL) {
        return false;
    }

    int i = 0;
    char *open_paren = strchr(token, '(');
    char *closed_paren = strchr(token, ')');

    if (open_paren == NULL || closed_paren == NULL) {
        return false;
    }

    // Pointer arithmetic determines array size
    int reg_len = closed_paren - open_paren - 1;
    char reg[reg_len];

    if (reg_len <= 0) {
        return false;
    }

    // Checks digit size and puts immediate inside of an array of i digits
    while (token[i] != '(') {

        if (!isdigit(token[i])) {
            return false;
        }

        i++;
    }

    // Offset too large (numerical offset is too large)
    if (i > 5) {
        return false;
    }
    
    // Pointer arithmetic + offset to copy content to an array
    for (int j = 0; j < reg_len; j++) {
        reg[j] = *(open_paren + 1 + j);
    }

    reg[reg_len] = '\0';

    if (get_register_index(reg) == -1) {
        return false;
    }

    return true;

}

bool is_data_field(const char *token) {

    return strcasecmp(token, ".data:") == 0;

}

bool is_text_field(const char *token) {

    return strcasecmp(token, ".text") == 0;

}

bool is_directive(const char *token) {

    const char *directives[] = {".word", ".byte", ".half", ".float", ".double", ".space", NULL};

    for (int i = 0; directives[i] != NULL; i++) {
        if (strcmp(token, directives[i]) == 0) {
            return true; // Valid directive found
        }
    }

    return false;

}