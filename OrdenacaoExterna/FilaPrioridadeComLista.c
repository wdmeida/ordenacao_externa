#include<stdio.h>
#include<stdlib.h>
#include"FilaPrioridadeComLista.h"
#include"registro.h"

Lista criaLista(int tamanho){
    Lista l =(Lista) malloc(sizeof(tipoLista));
    if(l){
        l->inicio = NULL;
        l->tamanho = 0;
        l->tamanhoMax = tamanho;
    }
    return l;
}

void terminaLista(Lista l){
    tipoNodo *n;
    n = l->inicio;
    while(l->inicio){
        l->inicio = n->prox;
        free(n);
        n = l->inicio;
    }
    free(l);
}
void imprimeLista(Lista l){
    tipoNodo *n;
    n = l->inicio;
    while(n){
        printf("%d\t",n->info.info.chave);
        n = n->prox;
    }
}

int insereListaOrdenado(Lista l ,tipoInfo info){
    tipoNodo *novo, *a = NULL, *p = l->inicio;

    if(l->tamanho > l->tamanhoMax) return 0;
        //procura posição de inserção
    while (p != NULL && p->info.info.chave < info.info.chave){
        a = p;
        p = p->prox;
    }
     //cria novo elemento
    novo = (tipoNodo*) malloc(sizeof(tipoNodo));
    novo->info = info;
    //encadeia elemento
    if (a == NULL){
//        insere elemento no início
        novo->prox = l->inicio; l->inicio = novo;
    }else {
//     insere elemento no meio da lista
        novo->prox = a->prox;
        a->prox = novo;
    }
    l->tamanho++;
    return 1;
}


int pesquisaLista(Lista l,tipoInfo *info,Chave chave){
    tipoNodo *n;

    n = l->inicio;
    while(n){
        if(n->info.info.chave == chave){
            *info = n->info;
            return 1;
        }
        n = n->prox;
    }
    return 0;
}

int retiraLista(Lista l,tipoInfo *info,Chave chave){
    tipoNodo *n,*a;

    n = l->inicio;
    while(n){
        if(n->info.info.chave == chave){
            if(n == l->inicio){
                l->inicio = n->prox;
                n->prox = NULL;
            }else{
                a->prox = n->prox;
                n->prox = NULL;
            }
            *info = n->info;
            free(n);
            l->tamanho--;
            return 1;
        }
        a = n;
        n = n->prox;
    }
    return 0;
}

int retiraListaInicio(Lista l,tipoInfo *info){
    tipoNodo *n;

    if(l->inicio == NULL) return 0;

    n = l->inicio;
    l->inicio = n->prox;
    *info = n->info;
    free(n);
    l->tamanho--;
    return 1;
}

int listaVazia(Lista l){
    return (l->tamanho == 0);
}
