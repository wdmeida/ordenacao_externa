#ifndef FILAPRIORIDADEHEAP_H_INCLUDED
#define FILAPRIORIDADEHEAP_H_INCLUDED
#define MAX 100

#include "registro.h"

typedef struct{
    tipoInfo* elementos;
    int tamanhoMax;
    int tamanho;
}tipoFilaHeap;

typedef tipoFilaHeap* filaHeap;

filaHeap criaFilaHeap(int);
int insereFilaHeap(filaHeap,tipoInfo);
int removeFilaHeap(filaHeap,Chave,tipoInfo*);
int removeFilaHeapInicio(filaHeap,tipoInfo*);
void terminaFilaHeap(filaHeap);
void sobe(int i, filaHeap fh);
int chao(double n);
void constroiHeap(filaHeap fh, int n);
void heapsort(filaHeap fh, int n);
void desce(int i, filaHeap fh, int n);
void imprime(filaHeap fh);

#endif // FILAPRIORIDADEHEAP_H_INCLUDED
