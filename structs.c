#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "structs.h"


int comparar(Pagina *p1, Pagina *p2) {
    if (p1->ultimoAcesso > p2->ultimoAcesso) {
        return 1;
    } else if (p1->ultimoAcesso == p2->ultimoAcesso) {
        return 0;
    } else {
        return -1;
    }
}

Pagina* criarPagina(int i) {
    Pagina *p = (Pagina*) malloc(sizeof(Pagina));
    
    p->estaEmMemoria = false;
    p->frame = -1;
    p->estaSendoReferenciada = false;
    p->i = i;
    p->ultimoAcesso = 0;
    
    return p;
}

Processo* criarProcesso(int numeroDePaginas, int pid) {
    Processo* processo = (Processo*) malloc(sizeof(Processo));
    processo->paginas = (Pagina*) malloc(numeroDePaginas * sizeof(Pagina));
    processo->numeroDePaginas = numeroDePaginas;
    processo->pid = pid;

    for (int i = 0; i < numeroDePaginas; i++) {
        Pagina *p = criarPagina(i + 1);
        p->pid = processo->pid;
        processo->paginas[i] = *p;
    }

    return processo;
}