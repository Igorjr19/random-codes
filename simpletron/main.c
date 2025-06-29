/**
 * Simpletron
 * Disciplina: Linguagens de Programação
 * Autor: Ígor José Rodrigues
 */

// Inclusão de bibliotecas
#include "simpletron.c"
#include "user.c"

// Função principal
int main()
{
    // Variáveis necessárias para o Simpletron
    int memory[MEMORY_SIZE];
    int accumulator = 0;
    int instructionCounter = 0;
    int instructionRegister = 0;
    int operationCode = 0;
    int operand = 0;
    int instruction = 0;
    int address = 0;
    int input = 0;
    int output = 0;

    // Interface com o usuário
    showOptionsMessage();
    int option = selectOption();

    // Execução do Simpletron
    if (option == 1)
    {
        int correctFileSML = readInstructionsFromFile(memory);
        if (correctFileSML == 1)
        {
            return 1;
        }
    }
    else if (option == 2)
    {
        showInitialMessage();
        readInstructions(memory);
    }
    else if (option == 0)
    {
        showEndMessage();
        return 0;
    }
    else
    {
        printf("Invalid option\n");
        return 1;
    }
    executeInstructions(memory, &accumulator, &instructionCounter, &instructionRegister, &operationCode, &operand, &instruction, &address, &input, &output);
    showMemory(memory);

    return 0;
}
