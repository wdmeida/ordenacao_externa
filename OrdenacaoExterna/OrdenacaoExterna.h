#ifndef ORDENACAOEXTERNA_H_INCLUDED
#define ORDENACAOEXTERNA_H_INCLUDED
#include "registro.h"
#include "buffer.h"
#include "FilaPrioridadeHeap.h"
#include "FilaPrioridadeComLista.h"

struct arquivo{
    FILE *f;
    int pos, maximo;
    Buffer entrada;
};

void mergeSortExterno(char *nome, int tamanhoBloco, int tamBufferEntrada, int tamBufferSaida,int numFila);
int criaArquivosOrdenados(char *nome, int tamanhoBloco);
void salvaArquivo(char *nome, registro *V, int tam);
void salvaArquivoOrdenado(char *nome, Buffer b);
void preencheBuffer(struct arquivo* arq, int tamanhoBuffer);
int procuraMenor(struct arquivo* arq, int numArqs, void* fila, int numFila, int tamBufferEntrada, tipoInfo *menor);
void merge(char *nome, int numArqs, int tamBufferEntrada, int tamBufferSaida,void* fila,int numFila);
int compara(const void* a, const void* b);
void selecionaFilaInsere(void* fila, int numFila,tipoInfo info);
void selecionaFilaRemove(void* fila, int numFila,tipoInfo *info);
int retornaTamanhoFila(void* fila, int numFila);

#endif
