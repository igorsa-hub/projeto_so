#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdbool.h>
#include <time.h>

typedef struct {
    bool estaEmMemoria;
    int frame;
    bool estaSendoReferenciada;
    time_t ultimoAcesso;
    int pid;
    int i;
} Pagina;

// Método usado para comparar o último acesso de duas páginas,
// retorna 1 se a p1 tiver sido acessada mais recentemente, 0 se forem iguais
// e -1 se p2 tiver sido acessada mais recentemente
int comparar(Pagina *p1, Pagina *p2);

typedef struct {
    int pid;
    Pagina *paginas;
    int numeroDePaginas;
} Processo;

Processo* criarProcesso(int numeroDePaginas, int pid);

#endif