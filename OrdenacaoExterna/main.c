#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "OrdenacaoExterna.h"
#include "FilaPrioridadeComLista.h"
#include "FilaPrioridadeHeap.h"

//Gera um arquivo com valores aleatórios para serem ordenados.
void criaArquivoTexte(char *nome, int tamanho){
    int i;
    registro reg;
    FILE *f = fopen(nome,"w");
    srand(time(NULL));
    for(i = 0; i < tamanho; i++){
        reg.chave = rand();
        fprintf(f,"%d\n",reg.chave);
    }
    fclose(f);
}//criaArquivoTexte(char *nome)

int main(int args, char *argv[])
{
    int tamanho = 1000000;
    criaArquivoTexte(argv[1],tamanho);
    mergeSortExterno(argv[1],atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),atoi(argv[5]));

    return 0;
}
