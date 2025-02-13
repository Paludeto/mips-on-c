#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "executors.h"
#include "register.h"
#include "encoder.h"
#include "memory.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void wait_for_enter() {
    printf("\n%sPressione Enter para continuar...%s", ANSI_COLOR_YELLOW, ANSI_COLOR_RESET);
    getchar();
}

void clear_instructions() {
    memset(inst_memory, 0, sizeof(Instruction) * INST_MEM_SIZE);
    current_text_address = 0;
    pc = 0;
}

int menu() {

    int op = 0;
    int file_loaded = 0;
    char filepath[256] = "";
    int result;

    do {

        clear_screen();
        printf("%s========================================\n", ANSI_COLOR_CYAN);
        printf("              MENU PRINCIPAL            \n");
        printf("========================================%s\n", ANSI_COLOR_RESET);
        printf("%s1.%s Carregar arquivo\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
        printf("%s2.%s Executar instruções\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
        printf("%s3.%s Imprimir tabela de registradores\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
        printf("%s4.%s Imprimir binários\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
        printf("%s5.%s Sair\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
        printf("%s========================================\n", ANSI_COLOR_CYAN);

        printf("Escolha uma opção: %s", ANSI_COLOR_MAGENTA);
        scanf("%d", &op);
        printf(ANSI_COLOR_RESET);

        while(getchar() != '\n');

        switch(op) {

            case 1: {

                clear_screen();
                printf("%sDigite o diretório do arquivo: %s", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
                fgets(filepath, sizeof(filepath), stdin);
                size_t len = strlen(filepath);

                if(len > 0 && filepath[len - 1] == '\n') {
                    filepath[len - 1] = '\0';
                }   
                
                clear_instructions();
                init_registers();

                printf("%sCarregando arquivo: %s%s\n", ANSI_COLOR_YELLOW, filepath, ANSI_COLOR_RESET);
                result = parse_file(filepath);

                if(result == 0) {
                    file_loaded = 1;
                    printf("%sArquivo carregado \xE2\x9C\x94%s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
                } else {
                    file_loaded = 0;
                    printf("%sErro ao carregar o arquivo.%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
                }

                wait_for_enter();
                
                break;

            }
            case 2: {

                if(!file_loaded) {
                    printf("%sErro: Carregue um arquivo primeiro.%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
                    wait_for_enter();
                } else {

                    clear_screen();
                    clear_instructions();
                    init_registers();
                    printf("%sRe-carregando arquivo: %s%s\n", ANSI_COLOR_YELLOW, filepath, ANSI_COLOR_RESET);
                    result = parse_file(filepath);

                    if(result == 0) {
                        printf("%sArquivo recarregado \xE2\x9C\x94%s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
                        printf("%sExecutando instruções...%s\n", ANSI_COLOR_YELLOW, ANSI_COLOR_RESET);
                        execute_instructions();
                        printf("%sInstruções executadas.%s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
                    } else {
                        printf("%sErro ao recarregar o arquivo.%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
                    }

                    wait_for_enter();

                }

                break;
            }
            case 3:

                if(!file_loaded) {
                    printf("%sErro: Carregue um arquivo primeiro.%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
                    wait_for_enter();
                } else {
                    clear_screen();
                    print_reg_table();
                    wait_for_enter();
                }

                break;

            case 4:

                if(!file_loaded) {
                    printf("%sErro: Carregue um arquivo primeiro.%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
                    wait_for_enter();
                } else {
                    clear_screen();
                    encode_inst_arr(inst_memory);
                    wait_for_enter();
                }

                break;

            case 5:

                printf("%sSaindo do programa...%s\n", ANSI_COLOR_MAGENTA, ANSI_COLOR_RESET);
                return EXIT_SUCCESS;

            default:

                printf("%sOpção inválida. Tente novamente.%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
                wait_for_enter();
                break;

        }

    } while(op != 5);

    return EXIT_SUCCESS;

}