#ifndef BUFFER_H_INCLUDED
#define BUFFER_H_INCLUDED
#include "registro.h"

typedef struct nodo{
    struct nodo *proximo;
    registro elemento;
}tipo_nodo;

typedef struct{
    int tamanho;
    int tamanhoMaximo;
    tipo_nodo *inicio, *fim;
}tipo_buffer;

typedef tipo_buffer *Buffer;

Buffer criaBuffer(int tamanho);
int inserirBuffer(Buffer, registro);
int removerBuffer(Buffer, registro*);
int tamanhoBuffer(Buffer);
int bufferCheio(Buffer);
int bufferVazio(Buffer);
void terminaBuffer(Buffer);
#endif // BUFFER_H_INCLUDED
