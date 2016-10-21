#include<stdio.h>
#include<stdlib.h>
#include"FilaPrioridadeHeap.h"

filaHeap criaFilaHeap(int tamanho){
    filaHeap fh = (filaHeap)malloc(sizeof(tipoFilaHeap));

    if(fh){
        fh->elementos = (tipoInfo*)malloc(sizeof(tipoInfo)*tamanho);
        fh->tamanho = 0;
        fh->tamanhoMax = tamanho;
    }
    return fh;
}

int insereFilaHeap(filaHeap fh,tipoInfo info){
    if(fh->tamanho > fh->tamanhoMax) return 0;

    fh->elementos[fh->tamanho] = info;
    fh->tamanho++;
    heapsort(fh,fh->tamanho);
    return 1;
}

int removeFilaHeap(filaHeap fh,Chave ch,tipoInfo *info){
    if(fh->tamanho <=0) return 0;
    int indice;

    for(indice = 0; indice < fh->tamanho;indice++){
        if(fh->elementos[indice].info.chave == ch)
            break;
    }

    *info = fh->elementos[indice];
    fh->elementos[indice] = fh->elementos[fh->tamanho-1];
    fh->tamanho--;
    heapsort(fh,fh->tamanho);
    return 1;
}

int removeFilaHeapInicio(filaHeap fh,tipoInfo *info){
    if(fh->tamanho <=0) return 0;

    *info = fh->elementos[0];
    fh->elementos[0] = fh->elementos[fh->tamanho-1];
    fh->tamanho--;
    heapsort(fh,fh->tamanho);
    return 1;
}

int pesquisaFilaHeap(filaHeap fh, Chave ch,tipoInfo info){
    int indice;
    for(indice = 0; indice < fh->tamanho;indice++)
        if(fh->elementos[indice].info.chave == ch){
            info = fh->elementos[indice];
            return 1;
        }
    return 0;
}

void terminaFilaHeap(filaHeap fh){
    free(fh->elementos);
    free(fh);
}

int chao(double n){
 return (int) n;
}

/* sobe o elemento i no heap */
void sobe(int i, filaHeap fh){
 int j; /* índice do pai de i */
 tipoInfo temp; /* variável usada na troca (swap) */

 j = chao((i-1)/2);

 /* se i tem pai e que seja maior que i */
 if(j >= 0 && fh->elementos[i].info.chave > fh->elementos[j].info.chave)
 {
   /* troca ambos */
   temp = fh->elementos[i];
   fh->elementos[i] = fh->elementos[j];
   fh->elementos[j] = temp;
   /* e continua subindo este elemento */
   sobe(j, fh);
 }
}

/* desce o elemento i no heap de tamanho n */
void desce(int i, filaHeap fh, int n){
 int j; /* índice do filho de i */
 tipoInfo temp; /* variável usada na troca (swap) */

 j = 2*i + 1;

 if(j < n) /* se i tem filhos */
 {
   if(j < n-1) /* se i tem filho direito */
   {
     /* pega o maior filho... */
     if(fh->elementos[j].info.chave < fh->elementos[j+1].info.chave)
       j++;
   }
   /* ..e compara com o pai */
   if(fh->elementos[j].info.chave > fh->elementos[i].info.chave)
   {
     /* troca ambos (swap) */
     temp = fh->elementos[i];
     fh->elementos[i] = fh->elementos[j];
     fh->elementos[j] = temp;
     /* e continua descendo o mesmo elemento */
     desce(j, fh, n);
   }
 }
}

void constroiHeap(filaHeap fh, int n){
 int i;
 for(i = chao(n/2); i >= 0; i--)
 {
   desce(i, fh, n);
 }
}

/* função de ordenação */
void heapsort(filaHeap fh, int n){
 int i; /* contador */
 tipoInfo temp; /* usado na troca (swap) */
 int tamanhoDoHeap;

 tamanhoDoHeap = n;

 constroiHeap(fh, n);
 for(i = n-1; i > 0; i--)
 {
   /* coloca o primeiro (que é o maior, pela definição de heap)
    no final do vetor e decrementa o tamanho do heap */
   temp = fh->elementos[i];
   fh->elementos[i] = fh->elementos[0];
   fh->elementos[0] = temp;

   tamanhoDoHeap--;

   desce(0, fh, tamanhoDoHeap);
 }
}

/*void imprime(filaHeap fh){
    int indice;
    for(indice = 0; indice < fh->tamanho;indice++)
        printf("%d\t",fh->elementos[indice].chave);
}*/

