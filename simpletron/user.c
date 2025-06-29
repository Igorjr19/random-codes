// Inclusão de bibliotecas
#include <stdio.h>

// Funções do usuário
void showOptionsMessage();
int selectOption();
void showEndMessage();

// Implementação das funções

/**
 * Função que exibe as opções disponíveis para o usuário
 */
void showOptionsMessage()
{
    printf("Simpletron\n");
    printf("1 - Read instructions from file\n");
    printf("2 - Read instructions from user\n");
    printf("0 - Exit\n");
    printf("Choose an option: ");
}

/**
 * Função que seleciona a opção escolhida pelo usuário
 */
int selectOption()
{
    int option = 0;
    scanf("%d", &option);
    return option;
}

/**
 * Função que exibe a mensagem de encerramento do Simpletron
 */
void showEndMessage()
{
    printf("*** Simpletron program terminated ***\n");
}
