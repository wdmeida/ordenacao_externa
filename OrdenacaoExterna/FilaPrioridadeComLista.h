#ifndef FILAPRIORIDADECOMLISTA_H_INCLUDED
#define FILAPRIORIDADECOMLISTA_H_INCLUDED

#include "registro.h"

typedef struct tipoNodo{
    struct tipoNodo* prox;
    tipoInfo info;
}tipoNodo;

typedef struct {
    tipoNodo *inicio;
    int tamanho;
    int tamanhoMax;
}tipoLista;

typedef tipoLista* Lista;


Lista criaLista(int);
void terminaLista(Lista);
void imprimeLista(Lista);
int insereListaOrdenado(Lista,tipoInfo);
int retiraLista(Lista l,tipoInfo *info,Chave chave);
int pesquisaLista(Lista l,tipoInfo *info,Chave chave);
int retiraListaInicio(Lista l,tipoInfo *info);
int listaVazia(Lista);

#endif // FILAPRIORIDADECOMLISTA_H_INCLUDED
