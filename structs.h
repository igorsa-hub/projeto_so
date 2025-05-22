#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    int numeroDeEnderecos;
} Pagina;

typedef struct {
    int pid;
    Pagina **paginas;
    int *tabelaDePaginas;
} Processo;

Processo* criarProcesso(int numeroDePaginas, int NUMERO_DE_ENDERECOS);

#endif