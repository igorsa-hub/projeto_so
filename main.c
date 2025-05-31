#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "memoria.h"
#include "structs.h"
#include "utils.h"

int NUMERO_DE_FRAMES; // Número total de frames na memória
int NUMERO_DE_ENDERECOS; // Número de endereços por página
int NUMERO_DE_PROCESSOS; // Número de processos
int TEMPO_DE_CICLO; // Tempo de ciclo, quanto maior, mais devagar o ciclo vai passar

Processo *processos; // Array de processos

int ciclo = 0; // Contador de ciclos
int count = 0;

// Método para extrair os parâmetros de linha de comando
// Retorna true se forem extraídos com sucesso, e retorna false se não houver exatamente 2 parâmetros
bool extrairParametros(int argc, char *argv[], int *numeroDeFrames, int *numeroDeEnderecos, int *numeroDeProcessos, int *tempoDeCiclo) {
    // Se não for especificado o número de frames ou número de endereços em uma página,
    // exibir uma mensagem de ero
    if (argc != 5) {
        return false;
    }

    *numeroDeFrames = atoi(argv[1]);
    *numeroDeEnderecos = atoi(argv[2]);
    *numeroDeProcessos = atoi(argv[3]);
    *tempoDeCiclo = atoi(argv[4]);

    // Se algum dos valores for menor que 0
    if (*numeroDeFrames <= 0 || *numeroDeEnderecos <= 0 || *numeroDeProcessos <= 0 || *tempoDeCiclo <= 0) {
        return false;
    }

    printf(
        "[INFO] Informações da memória:\n\tNúmero de frames: %d\n\tNúmero de endereços: %d\n\tMemória disponível: %s\n\n",
        *numeroDeFrames,
        *numeroDeEnderecos,
        formatarTamanho((*numeroDeFrames) * (*numeroDeEnderecos))
    );

    return true;
}

void simularPaginacao(Memoria *memoria, int politica, const char *nomeAlgoritmo) {
    int totalAcessos = 0;
    int totalPageFaults = 0;
    int count = 0;

    printf(" --- SIMULADOR DE PAGINAÇÃO ---\n");
    printf("Algoritmo de substituição: %s\n", nomeAlgoritmo);

    while (count < 10) {
        int processoAleatorio = rand() % NUMERO_DE_PROCESSOS;

        int pagina = rand() % (int)(processos[processoAleatorio].numeroDePaginas * 1.1);
        int deslocamento = rand() % (int)(NUMERO_DE_ENDERECOS * 1.1);

        int enderecoAleatorio = (pagina << 20) | deslocamento;

        printf("[INFO] Processo %d solicitou acesso ao endereço virtual 0x%04x\n",
               processos[processoAleatorio].pid, enderecoAleatorio);

        totalAcessos++;
        int enderecoFisico = converterEnderecoVirtual(memoria, &processos[processoAleatorio], enderecoAleatorio, politica);

        if (enderecoFisico != -1) {
            printf("\t[INFO] Endereço físico: 0x%04x\n", enderecoFisico);
        } else {
            printf("\t[ERRO] Falha ao acessar o endereço virtual 0x%04x\n", enderecoAleatorio);
            totalPageFaults++;
        }

        imprimirEstado(memoria, &ciclo);
        sleep(TEMPO_DE_CICLO);
        ciclo++;
        count++;
        printf("\n");
    }

    printf("======== ESTATÍSTICAS DA SIMULAÇÃO ========\n");
    printf("Total de acessos à memória: %d\n", totalAcessos);
    printf("Total de page faults: %d\n", totalPageFaults);
    printf("Taxa de page faults: %.2f%%\n", (totalPageFaults * 100.0) / totalAcessos);
    printf("\nAlgoritmo: %s\n\n", nomeAlgoritmo);
}

void criarProcessos() {
    processos = (Processo *)malloc(NUMERO_DE_PROCESSOS * sizeof(Processo));

    for (int i = 0; i < NUMERO_DE_PROCESSOS; i++) {
        // Cria um número aleatório de páginas para cada processo
        int numeroDePaginasDoProcesso = rand() % (int) (NUMERO_DE_FRAMES * 3) + 1;

        Processo *processo = criarProcesso(numeroDePaginasDoProcesso, i);
        processos[i] = *processo;
    }
}


int main(int argc, char *argv[]) {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    if (!extrairParametros(argc, argv, &NUMERO_DE_FRAMES, &NUMERO_DE_ENDERECOS, &NUMERO_DE_PROCESSOS, &TEMPO_DE_CICLO)) {
        printf("Parâmetros insuficientes, tente novamente com:\n\t<Número de frames> <Número de endereços> <Número de processos>\n");

        return 1;
    }

    Memoria *memoria = criarMemoria(NUMERO_DE_FRAMES, NUMERO_DE_ENDERECOS);
    criarProcessos();
    simularPaginacao(memoria, 0, "LRU");
    simularPaginacao(memoria, 1, "FIFO");
     
    return 0;
}
