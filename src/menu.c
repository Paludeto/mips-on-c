#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "executors.h"
#include "register.h"
#include "encoder.h"
#include "memory.h"

// Função para limpar a tela, compatível com Windows e Unix
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Função para aguardar o usuário pressionar Enter (apenas 1 vez)
void wait_for_enter() {
    printf("\nPressione Enter para continuar...");
    getchar(); // aguarda um único Enter
}

int menu() {    
    int op = 0;

    do {    
        // Limpa a tela antes de exibir o menu
        clear_screen();

        printf("========================================\n");
        printf("              MENU PRINCIPAL            \n");
        printf("========================================\n");
        printf("1. Carregar arquivo\n");
        printf("2. Executar instrucoes\n");
        printf("3. Imprimir tabela de registradores\n");
        printf("4. Imprimir codigos binarios\n");
        printf("5. Sair\n");
        printf("========================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &op);

        // Limpa o buffer do teclado após a leitura
        while(getchar() != '\n');

        switch (op) {
            case 1:
                clear_screen();
                printf("Carregando arquivo...\n");
                parse_file("test.s");
                wait_for_enter();
                break;
            case 2:
                clear_screen();
                printf("Executando instrucoes...\n");
                execute_instructions();
                wait_for_enter();
                break;
            case 3:
                clear_screen();
                print_reg_table();
                wait_for_enter();
                break;    
            case 4:
                clear_screen();
                encode_inst_arr(inst_memory);
                wait_for_enter();
                break;
            case 5:
                printf("Saindo do programa...\n");
                return EXIT_SUCCESS;
            default:
                printf("Opcao invalida. Tente novamente...\n");
                wait_for_enter();
                break;
        }

    } while (op != 5);

    return EXIT_SUCCESS;
}
