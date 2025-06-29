// Inclusão de bibliotecas
#include <stdio.h>

// Definição das constantes de operações
#define READ 10
#define WRITE 11

#define LOAD 20
#define STORE 21
#define GET 22

#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33

#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43

#define MEMORY_SIZE 100

// Funções do Simpletron
void showInitialMessage();
void readInstructions(int memory[]);
int readInstructionsFromFile(int memory[]);
void executeInstructions(int memory[], int *accumulator, int *instructionCounter, int *instructionRegister, int *operationCode, int *operand, int *instruction, int *address, int *input, int *output);
void showMemory(int memory[]);

// Implementação das funções

/**
 * Função que exibe a mensagem inicial do Simpletron
 */
void showInitialMessage()
{
    printf("***           Welcome to Simpletron!          ***\n");
    printf("*** Please enter your program one instruction ***\n");
    printf("*** (or data word) at a time. I will type the ***\n");
    printf("*** location number and a question mark (?).  ***\n");
    printf("*** You then type the word for that location. ***\n");
    printf("*** Type the sentinel -99999 to stop entering ***\n");
    printf("*** your program.                             ***\n");
}

/**
 * Função que lê a entrada do usuário com as instruções em linguagem de máquina Simpletron (LMS)
 */
void readInstructions(int memory[])
{
    int instruction = 0;

    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        memory[i] = 0;
    }

    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        printf("%02d ? ", i);
        scanf("%d", &instruction);

        if (instruction == -99999)
        {
            break;
        }

        memory[i] = instruction;
    }

    printf("*** Program loading completed ***\n");
}

/**
 * Função que lê as instruções em linguagem de máquina Simpletron (LMS) de um arquivo
 */
int readInstructionsFromFile(int memory[])
{
    FILE *file = fopen("simpletron.txt", "r");

    if (file == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    int instruction = 0;

    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        memory[i] = 0;
    }

    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        fscanf(file, "%d", &instruction);

        if (instruction == -99999)
        {
            break;
        }

        memory[i] = instruction;
    }

    printf("*** Program loading completed ***\n");

    fclose(file);
    return 0;
}

/**
 * Função que executa as instruções em linguagem de máquina Simpletron (LMS)
 */
void executeInstructions(int memory[], int *accumulator, int *instructionCounter, int *instructionRegister, int *operationCode, int *operand, int *instruction, int *address, int *input, int *output)
{
    *instructionCounter = 0;

    while (*instructionCounter < MEMORY_SIZE)
    {
        *instructionRegister = memory[*instructionCounter];
        *operationCode = *instructionRegister / 100;
        *operand = *instructionRegister % 100;

        switch (*operationCode)
        {
        case READ:
            fflush(stdin);
            printf("Enter an integer: ");
            scanf("%d", &memory[*operand]);
            break;

        case WRITE:
            fflush(stdin);
            printf("Output: %d\n", memory[*operand]);
            break;

        case LOAD:
            *accumulator = memory[*operand];
            break;

        case STORE:
            memory[*operand] = *accumulator;
            break;

        case ADD:
            *accumulator += memory[*operand];
            break;

        case SUBTRACT:
            *accumulator -= memory[*operand];
            break;

        case DIVIDE:
            *accumulator /= memory[*operand];
            break;

        case MULTIPLY:
            *accumulator *= memory[*operand];
            break;

        case BRANCH:
            *instructionCounter = *operand;
            break;

        case BRANCHNEG:
            if (*accumulator < 0)
            {
                *instructionCounter = *operand - 1;
            }
            break;

        case BRANCHZERO:
            if (*accumulator == 0)
            {
                *instructionCounter = *operand;
            }
            break;

        case HALT:
            printf("*** Simpletron execution terminated ***\n");
            return;

        default:
            printf("*** Invalid operation code ***\n");
            printf("Operation code: %d\n", *operationCode);
            printf("Operand: %d\n", *operand);
            return;
        }

        (*instructionCounter)++;
    }
}

/**
 * Função que exibe o conteúdo da memória do Simpletron
 */
void showMemory(int memory[])
{
    printf("\nREGISTERS:\n");
    printf("accumulator: %d\n", 0);
    printf("instructionCounter: %d\n", 0);
    printf("instructionRegister: %d\n", 0);
    printf("operationCode: %d\n", 0);
    printf("operand: %d\n", 0);
    printf("\nMEMORY:\n");

    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        if (i % 10 == 0)
        {
            printf("\n");
        }

        printf("%02d ", memory[i]);
    }

    printf("\n");
}
