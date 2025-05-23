#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "memoria.h"
#include "structs.h"
#include "utils.h"

#define NUMERO_MAXIMO_DE_PROCESSOS 20 // Número máximo de processos que podem ser criados

int NUMERO_DE_FRAMES; // Número total de frames na memória
int NUMERO_DE_ENDERECOS; // Número de endereços por página

Processo *processos; // Array de processos

int ciclo = 0; // Contador de ciclos

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

    printf(
        "[INFO] Informações da memória:\n\tNúmero de frames: %d\n\tNúmero de endereços: %d\n\tMemória disponível: %s\n\n",
        *numeroDeFrames,
        *numeroDeEnderecos,
        formatarTamanho((*numeroDeFrames) * (*numeroDeEnderecos))
    );

    return true;
}


void criarProcessos() {
    processos = (Processo *)malloc(NUMERO_MAXIMO_DE_PROCESSOS * sizeof(Processo));

    for (int i = 0; i < NUMERO_MAXIMO_DE_PROCESSOS; i++) {
        // Cria um número aleatório de páginas para cada processo
        int numeroDePaginasDoProcesso = rand() % (int) (NUMERO_DE_FRAMES * 3) + 1;

        Processo *processo = criarProcesso(numeroDePaginasDoProcesso, i);
        processos[i] = *processo;
    }
}

int main(int argc, char *argv[]) {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    if (!extrairParametros(argc, argv, &NUMERO_DE_FRAMES, &NUMERO_DE_ENDERECOS)) {
        printf("Parâmetros insuficientes, tente novamente com:\n\t<Número de frames> <Número de endereços>\n");

        return 1;
    }

    Memoria *memoria = criarMemoria(NUMERO_DE_FRAMES, NUMERO_DE_ENDERECOS);
    criarProcessos();

    while (true) {        
        // Escolher um processo aleatório para realizar a requisição
        int processoAleatorio = rand() % NUMERO_MAXIMO_DE_PROCESSOS;
        
        // Gera uma página aleatória para o processo escolhido, com 20% de chance de ser maior que o número de páginas do processo
        int pagina = rand() % (int) (processos[processoAleatorio].numeroDePaginas * 1.1);
        // Gera um endereço virtual aleatório, com 20% de chance de ser maior que o número de endereços
        int deslocamento = rand() % (int) (NUMERO_DE_ENDERECOS * 1.1);

        // Gera o endereço virtual, com a página nos primeiros 12 bits e o deslocamento nos últimos 20 bits
        int enderecoAleatorio = (pagina << 20) | deslocamento;

        printf("[INFO] Processo %d solicitou acesso ao endereço virtual 0x%04x\n", processos[processoAleatorio].pid, enderecoAleatorio);
        
        int enderecoFisico = converterEnderecoVirtual(memoria, &processos[processoAleatorio], enderecoAleatorio);
        if (enderecoFisico != -1) {
            printf("\t[INFO] Endereço físico: 0x%04x\n", enderecoFisico);
        } else {
            printf("\t[ERRO] Falha ao acessar o endereço virtual 0x%04x\n", enderecoAleatorio);
        }

        imprimirEstado(memoria, &ciclo);

        sleep(4); // Simula o tempo de espera para o próximo acesso à memória
        ciclo++;
        printf("\n");
    }

    return 0;
}
