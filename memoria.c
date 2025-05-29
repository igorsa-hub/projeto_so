#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "memoria.h"

Memoria* criarMemoria(int numeroDeFrames, int numeroDeEnderecos) {
    Memoria *memoria = (Memoria*) malloc(sizeof(Memoria));

    memoria->frames = (Pagina*) malloc(numeroDeFrames * sizeof(Pagina));
    memoria->numeroDeFrames = numeroDeFrames;
    memoria->framesOcupados = 0;
    memoria->numeroDeEnderecos = numeroDeEnderecos;

    return memoria;
}

// Retorna o frame em que a página utilizada há mais tempo se encontra
int leastRecentlyUsed(Memoria *m) {
    Pagina leastRecentlyUsed = m->frames[0];
    int index = 0;
    // Percore a memória procurando a página com o maior intervalo desde o último acesso
    for (int i = 1; i < m->framesOcupados; i++) {
        // Se a atual for mais antiga que a que já temos, trocar as variáveis 
        if (comparar(&leastRecentlyUsed, &m->frames[i]) == 1) {
            leastRecentlyUsed = m->frames[i];
            index = i;
        }
    }

    return index;
}

int alocarPagina(Memoria *memoria, Pagina *pagina) {
    if (memoria->framesOcupados < memoria->numeroDeFrames) {
        pagina->frame = memoria->framesOcupados;
        pagina->estaEmMemoria = true;
        pagina->ultimoAcesso = time(NULL);

        memoria->frames[memoria->framesOcupados] = *pagina;
        memoria->framesOcupados++;

        printf("\t[INFO] Página %d @ PID %d foi alocada no frame %d\n", pagina->i, pagina->pid, pagina->frame);

        return pagina->frame;
    } else {
        printf("\t[INFO] A memória está cheia, removendo a página mais antiga\n");
        int index = leastRecentlyUsed(memoria);

        memoria->frames[index].estaEmMemoria = false;  // Corrigido
        printf("\t[INFO] A página %d @ PID %d foi removida do frame %d\n", memoria->frames[index].i, memoria->frames[index].pid, index);


        pagina->frame = index;
        pagina->estaEmMemoria = true;
        pagina->ultimoAcesso = time(NULL);

        memoria->frames[index] = *pagina;

        printf("\t[INFO] A página %d @ PID %d foi alocada no frame %d\n", memoria->frames[index].i, memoria->frames[index].pid, index);

        return index;
    }
}


void extrairInformacoes(Memoria *m, Processo *p, int enderecoVirtual, int *pagina, int *deslocamento) {
    
    *pagina = (enderecoVirtual >> 20) & 0xFFF; // 12 bits
    *deslocamento = enderecoVirtual & 0xFFFFF; // 20 bits

    if (*pagina >= p->numeroDePaginas) {
        printf("\tA página %d é inválida para o processo %d (%d páginas válidas)\n", *pagina + 1, p->pid, p->numeroDePaginas);
        *pagina = -1;
    }
     if (*deslocamento >= m->numeroDeEnderecos) {
        printf("\tO deslocamento %d solicitado é inválido (%d endereços válidos)\n", *deslocamento, m->numeroDeEnderecos);
        *deslocamento = -1;
    }
}

int converterEnderecoVirtual(Memoria *memoria, Processo *processo, int enderecoVirtual) {
    int pagina, deslocamento;

    extrairInformacoes(memoria, processo, enderecoVirtual, &pagina, &deslocamento);

    if (pagina == -1 || deslocamento == -1) {
        printf("\tAcesso inválido ao endereço virtual 0x%04x\n", enderecoVirtual);
        return -1;
    }


    // Verifica se a página já está na memória
    if (processo->paginas[pagina].estaEmMemoria) {
        printf("\tA página %d @ PID %d já está na memória\n", pagina + 1, processo->pid);
        processo->paginas[pagina].ultimoAcesso = time(NULL);
    } else {
        printf("\t[PAGE FAULT] A página %d @ PID %d não está na memória\n", pagina + 1, processo->pid);
        int frame = alocarPagina(memoria, &processo->paginas[pagina]);
    }
    
    printf("\t[INFO] Página %d com deslocamento %d (Frame %d)\n", pagina + 1, deslocamento, processo->paginas[pagina].frame);
    // Endereço físico = frame * número de endereços + deslocamento
    return processo->paginas[pagina].frame * memoria->numeroDeEnderecos + deslocamento;
}

void imprimirEstado(Memoria *memoria, int *contadorDeCiclos) {
    printf("[CICLO %d] Estado da memória:\n", *contadorDeCiclos + 1);
    for (int i = 0; i < memoria->numeroDeFrames; i++) {
        Pagina pagina = memoria->frames[i];
        int enderecoInicial = i * memoria->numeroDeEnderecos;
        int enderecoFinal = (i + 1) * memoria->numeroDeEnderecos - 1;

        if (pagina.estaEmMemoria) {
            printf("\tFrame %d (0x%04x a 0x%04x): Página %d @ PID %d\n", i, enderecoInicial, enderecoFinal, pagina.i, pagina.pid);
        } else {
            printf("\tFrame %d (0x%04x a 0x%04x): Vazio\n", i, enderecoInicial, enderecoFinal);
        }
    }
}