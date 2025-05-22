#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "memoria.h"

Pagina* criarPagina(int NUMERO_DE_ENDERECOS) {
    Pagina *p = (Pagina*) malloc(sizeof(Pagina));

    p->numeroDeEnderecos = NUMERO_DE_ENDERECOS;

    return p;
}

Processo* criarProcesso(int numeroDePaginas, Memoria *m) {
    Processo* processo = (Processo*) malloc(sizeof(Processo));
    processo->paginas = (Pagina*) malloc(numeroDePaginas * sizeof(Pagina));
    processo->tabelaDePaginas = malloc(numeroDePaginas * sizeof(int));

    for (int i = 0; i < numeroDePaginas; i++) {
        Pagina *p = criarPagina(m->numeroDeEnderecos);
        processo->paginas[i] = p;

        processo->tabelaDePaginas[i] = alocarPagina(m, p);
    }

}