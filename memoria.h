#ifndef MEMORIA_H
#define MEMORIA_H

#include "structs.h"

typedef struct {
    Pagina *frames;
    int numeroDeFrames;
    int framesOcupados;
    int numeroDeEnderecos;
} Memoria;

// Cria o contexto da memória com a quantidade de frames predefinidos
Memoria* criarMemoria(int numeroDeFrames, int numeroDeEnderecos);

// Percorre a memória e aloca a página em um frame
int alocarPagina(Memoria *memoria, Pagina* pagina);

void imprimirEstado(Memoria *memoria, int *contadorDeCiclos);

int converterEnderecoVirtual(Memoria *memoria, Processo *processo, int enderecoVirtual);

#endif