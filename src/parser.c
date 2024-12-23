#include "parser.h"

InstructionTable table[] = {
    {"add", R, 3, execute_add},
    {"sub", R, 3, execute_sub},
    {NULL, UNKNOWN, 0, NULL} // Sentinel to mark the end
};

void parseFile(char *file_name, Instruction *inst_arr, Register *r_array) {

    FILE *fp = fopen(file_name, "r");

    if (fp == NULL) {
        perror("File could not be opened\n");
        return;
    }

    // TO-DO (file parsing)

}

void tokenize_line(char *line, Register *r_array, InstructionList *inst_list) {

    const char delimiters[] = " \t,\n"; // Define delimiters
    char *token = strtok(line, delimiters); // Get the first token
    
    while (token != NULL) {

         if (is_inst(token)) {
            // Parse operands
            char *instruction = token;
            char *operands[10]; // Assume a maximum of 10 operands
            int operand_count = 0;

            while ((token = strtok(NULL, delimiters)) != NULL) {
                operands[operand_count++] = token;
            }

            // Validate instruction syntax and execute it (wip)
            validate_and_execute(instruction, operands, operand_count, r_array, inst_list);

        }

        // test_fn(token); tests tokenization

        token = strtok(NULL, delimiters); // Get the next token from where previous strtok left off

    }

}

// Checks if instruction is in the table
InstructionTable *find_instruction(const char *name) {

    for (int i = 0; table[i].name != NULL; i++) {
        if (strcmp(name, table[i].name) == 0) {
            return &table[i];
        }
    }

    return NULL;

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

void free_instruction(Instruction *inst) {

    free(inst->name);

    for (int i = 0; i < inst->op_count; i++) {
        free(inst->operands[i]);
    }

    free(inst->operands);
    free(inst);

}

bool validate_operands(const InstructionTable *inst_def, char **operands, int operand_count) {

    if (inst_def->op_count != operand_count) {
        printf("Error: %s expects %d operands, found %d\n", inst_def->name, inst_def->op_count, operand_count);
        return false;
    }
    return true;

}

// Validates and executes an instruction
void validate_and_execute(const char *instruction, char **operands, int operand_count, Register *r_array, InstructionList *inst_list) {

    InstructionTable *inst_def = find_instruction(instruction);
    if (!inst_def) {
        printf("Error: Unknown instruction: %s\n", instruction);
        return;
    }
    if (!validate_operands(inst_def, operands, operand_count)) {
        return;
    }

    Instruction *inst = create_instruction(instruction, operands, operand_count);
    inst_def->executor(inst->operands, r_array);
    free_instruction(inst);

}

void execute_add(char **operands, Register *r_array) {
    
    printf("Executing ADD with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);

    int rd = get_register_index(operands[0]);
    int rs = get_register_index(operands[1]);
    int rt = get_register_index(operands[2]);
    
    r_array[rd].value = r_array[rs].value + r_array[rt].value;

}

void execute_sub(char **operands, Register *r_array) {

    printf("Executing SUB with operands %s, %s, %s\n", operands[0], operands[1], operands[2]);
    

    Register rd = r_array[get_register_index(operands[0])];
    Register rs = r_array[get_register_index(operands[1])];
    Register rt = r_array[get_register_index(operands[2])];
    
    r_sub(&rs, &rt, &rd);

}

// Used to test each token's parse
void test_fn(char *token) {

    if (is_data_field(token)) {
        printf("Data field: %s\n", token);
    }

    if (is_directive(token)) {
        printf("Directive: %s\n", token);
    }

    if (is_text_field(token)) {
        printf("Text field: %s\n", token);
    }

    if (is_inst(token)) {
        printf("Instruction: %s\n", token);
    }
    
    if (is_label(token)) {
        printf("Label: %s\n", token);
    }

    if (is_op(token)) {
        printf("Operand: %s\n", token);
    }

    if (is_address(token)) {
        printf("Address: %s\n", token);
    }

}

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

bool is_inst(const char *token) {

    if (token == NULL) {
        return false;
    }
    // should be edited w/ the specified instructions later on
    const char *inst_arr[] = {
        "add", "sub", "mult", "div", "and", "or", "xor", "nor",
        "sll", "srl", "lw", "sw", "beq", "bne", "j", "jal", "jr",
        "nop", "addi", NULL
    };

    for (int i = 0; inst_arr[i] != NULL; i++) {
        if (strcmp(token, inst_arr[i]) == 0) {
            return true;
        }
    }

    return false;

}

bool is_op(const char *token) {

    if (token == NULL) {
        return false;
    }

    return is_reg(token) || is_imm(token);

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

bool is_reg(const char *token) {

    const char *registers[] = {
        "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3",
        "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
        "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
        "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"
    };

    for (int i = 0; i < 32; i++) {
        if (strcmp(token, registers[i]) == 0) {
            return true;
        }
    }

    return false;

}

int get_register_index(const char *reg) {

    const char *registers[] = {
        "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3",
        "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
        "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
        "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"
    };

    for (int i = 0; i < 32; i++) {
        if (strcmp(reg, registers[i]) == 0) {
            return i;
        }
    }

    return -1; // Return -1 if the register is invalid

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

    // Offset too large
    if (i > 5) {
        return false;
    }
    
    // Pointer arithmetic + offset to copy content to an array
    for (int j = 0; j < reg_len; j++) {
        reg[j] = *(open_paren + 1 + j);
    }

    reg[reg_len] = '\0';

    if (!is_reg(reg)) {
        return false;
    }

    return true;

}

bool is_data_field(const char *token) {

    return strcasecmp(token, ".data") == 0;

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