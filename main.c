#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "memoria.h"
#include "structs.h"

int NUMERO_DE_FRAMES; // Número total de frames na memória
int NUMERO_DE_ENDERECOS; // Número de endereços por página

// Método para extrair os parâmetros de linha de comando
// Retorna true se forem extraídos com sucesso, e retorna false se não houver exatamente 2 parâmetros
bool extrairParametros(int argc, char *argv[], int *numeroDeFrames, int *numeroDeEnderecos) {
    // Se não for especificado o número de frames ou número de endereços em uma página,
    // exibir uma mensagem de ero
    if (argc != 3) {
        return false;
    }

    *numeroDeFrames = atoi(argv[1]);
    *numeroDeEnderecos = atoi(argv[2]);

    return true;
}

int main(int argc, char *argv[]) {
    if (!extrairParametros(&NUMERO_DE_FRAMES, &NUMERO_DE_ENDERECOS)) {
        printf("Parâmetros insuficientes, tente novamente com:\n\t<Número de frames> <Número de endereços>\n");

        return 1;
    }

    Memoria *memoria = criarMemoria(NUMERO_DE_FRAMES, NUMERO_DE_ENDERECOS);

    // Loop?
        // Criar tarefas
        // Cada tarefa pode solicitar acesso a endereços aleatórios
        // Memória avalia, vê se o endereço é válido para o processo e imprime na tela?

    return 0;
}