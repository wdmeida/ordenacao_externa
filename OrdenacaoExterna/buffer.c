#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

//Inicia o buffer passando como parâmetro o tamanho maximo.
Buffer criaBuffer(int tamanho){
    Buffer b;
    b = (Buffer) malloc(sizeof(tipo_buffer));

    if(!b) return NULL;

    b->tamanho = 0;
    b->tamanhoMaximo = tamanho;
    b->fim = NULL;
    b->inicio = NULL;
    return b;
}//criaBuffer()

//Insere um elemento no buffer, caso este não esteja cheio.
int inserirBuffer(Buffer b, registro e){
    tipo_nodo *novo;

    if(bufferCheio(b)) return 0;

    novo = (tipo_nodo*) malloc(sizeof(tipo_nodo));

    if(!novo) return 0;

    novo->elemento = e;
    if(bufferVazio(b))
    {
        novo->proximo = b->fim;
        b->inicio = novo;
    }
    else
    {
        novo->proximo = b->fim->proximo;
        b->fim->proximo = novo;

    }
    b->fim = novo;
    b->tamanho++;
    return 1;
}//inserirBuffer()

//Remove um elemento do buffer caso este já não esteja vazio.
int removerBuffer(Buffer b, registro *e){
    if(bufferVazio(b)) return 0;

    tipo_nodo *retira;
    retira = b->inicio;
    (*e) = retira->elemento;
    b->inicio = retira->proximo;
    b->tamanho--;
    if(bufferVazio(b))
        b->fim = NULL;
    free(retira);
    return 1;
}//removerBuffer()

//Verifica se o buffer está cheio
int bufferCheio(Buffer b){
    if(b->tamanhoMaximo == b->tamanho) return 1; return 0;
}//bufferCheio()

//Verifica se o buffer está vazio.
int bufferVazio(Buffer b){
    if(b->tamanho == 0) return 1; return 0;
}//bufferVazio()

//Retorna o tamanho do buffer
int tamanhoBuffer(Buffer b){
    return b->tamanho;
}//tamanhoBuffer()

//Libera a memória alocada pelo buffer.
void terminaBuffer(Buffer b){
    tipo_nodo *aux;
    while(b->inicio != NULL){
        aux = b->inicio;
        b->inicio = b->inicio->proximo;
        free(aux);
    }
    free(b);
}//terminaBuffer()
