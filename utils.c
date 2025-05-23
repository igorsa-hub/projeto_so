#include <stdio.h>
#include <stdlib.h>

#define KILOBYTE 1024
#define MEGABYTE 1048576
#define GIGABYTE 1073741824

char* formatarTamanho(int tamanhoEmBytes) {
    char *resultado = (char*) malloc(20 * sizeof(char));
    char *sufixo;
    double tamanho;

    if (tamanhoEmBytes < KILOBYTE) {
        sufixo = "B";
        tamanho = tamanhoEmBytes;
    } else if (tamanhoEmBytes < MEGABYTE) {
        sufixo = "KB";
        tamanho = (double) tamanhoEmBytes / KILOBYTE;
    } else if (tamanhoEmBytes < GIGABYTE) {
        sufixo = "MB";
        tamanho = (double) tamanhoEmBytes / MEGABYTE;
    } else {
        sufixo = "GB";
        tamanho = (double) tamanhoEmBytes / GIGABYTE;
    }

    if ((int) tamanho == tamanho) {
        // Se o número for inteiro, não exibir casas decimais
        snprintf(resultado, 20, "%.0f %s", tamanho, sufixo);
    } else {
        // Caso contrário, exibir duas casas decimais
        snprintf(resultado, 20, "%.2f %s", tamanho, sufixo);
    }

    return resultado;
}