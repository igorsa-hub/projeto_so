#ifndef MEMORIA_H
#define MEMORIA_H

#include "structs.h"

typedef struct {
    Pagina **frames;
    int numeroDeEnderecos;
    int numeroDeFrames;
} Memoria;

// Cria o contexto da memória com a quantidade de frames 
// e número de endereços por página pré-definidos
Memoria* criarMemoria(int numeroDeFrames, int numeroDeEnderecos);

// Percore a memória e aloca a página em um frame, retorna o número do frame
// no qual a página foi alocada
int alocarPagina(Memoria *memoria, Pagina* pagina);

#endif