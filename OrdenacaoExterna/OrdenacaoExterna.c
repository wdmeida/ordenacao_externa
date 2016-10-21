#include <stdlib.h>
#include <stdio.h>
#include "OrdenacaoExterna.h"
#include "FilaPrioridadeComLista.h"
#include "FilaPrioridadeHeap.h"

/*Recebe as informações do usuário e inicia a ordenação do arquivo.*/
void mergeSortExterno(char *nome, int tamanhoBloco, int tamBufferEntrada, int tamBufferSaida,int numFila){
    float inicio = clock();
    char novo[20];
    int numArqs = criaArquivosOrdenados(nome, tamanhoBloco); //Total de runs geradas.
    int i; //

    void *fila;

    if(numFila == 0)
        fila = criaFilaHeap(numArqs);
    else
        fila = criaLista(numArqs);

    remove(nome);
    merge(nome,numArqs,tamBufferEntrada,tamBufferSaida,fila,numFila);

    //Remove todos os arquivos temporários criados.
    for(i = 0; i < numArqs; i++){
        sprintf(novo,"Temp%d.txt",i+1);
        remove(novo);
    }
    //Abre o arquivo gerado e registra o tempo.
    FILE *f = fopen(nome,"a");
    if(f != NULL)
        fprintf(f,"\nTempo de execucao = %.2f s\n",(clock() - inicio) / 1000);
    fclose(f);
}//mergeSortExterno()

/*Cria as runs que serão usadas para fazer a intercalação.*/
int criaArquivosOrdenados(char *nome, int tamanhoBloco){
    registro V[tamanhoBloco];
    int cont = 0, total = 0;
    char novo[20];
    FILE *f = fopen(nome,"r");

    /*Inicia a leitura do arquivo e o divide em arquivos menores
      j ordenados para depois realizar a intercalação.*/
    while(!feof(f)){
        fscanf(f,"%d",&V[total].chave);
        total++;
        /*Verifica se chegou ao tamanho determinado para cada bloco, caso tenha chegado,
          ordena o bloco, e salva em um arquivo temporário.*/
        if(total == tamanhoBloco){
            cont++;
            sprintf(novo,"Temp%d.txt",cont);
            qsort(V,total,sizeof(registro),compara);
            salvaArquivo(novo,V,total);
            total = 0;
        }
    }//While(!feof(f))

    /*Verifica se ainda sobraram dados que não completaram um bloco, caso ainda existam arquivos
      ordena-os e salva o conteúdo em um arquivo temporário.*/
    if(total > 0){
        cont++;
        sprintf(novo,"Temp%d.txt",cont);
        qsort(V,total,sizeof(registro),compara);
        salvaArquivo(novo,V,total);
    }
    fclose(f);

    //Retorna a quantidade de arquivos temporários gerados.
    return cont;
}//criaArquivosOrdenados()

/*Salva o conteúdo de uma run em um arquivo temporário.*/
void salvaArquivo(char *nome, registro *V, int tam){
    int i;
    FILE *f = fopen(nome,"a");
    if(f != NULL)
        for(i = 0; i < tam; i++)
            fprintf(f,"%d\n",V[i].chave);
    fclose(f);
}//salvaArquivo()

/*Salva o conteúdo do buffer no fim do arquivo.*/
void salvaArquivoOrdenado(char *nome, Buffer b){
    registro v;
    FILE *f = fopen(nome,"a");
    if(f != NULL)
        while(!bufferVazio(b)){
            removerBuffer(b,&v);
            fprintf(f,"%d\n",v.chave);
        }
    fclose(f);
}//salvaArquivo()

/*Lê os arquivos temporários gerados, para gerar um novo arquivo ordenado.*/
void merge(char *nome, int numArqs, int tamBufferEntrada, int tamBufferSaida, void* fila,int numFila){
    char novo[20];
    int i;
    tipoInfo e;
    registro r;
    //Inicia o buffer de entrada,
    Buffer saida = criaBuffer(tamBufferSaida);
    /*Forma antiga, apagar depois.
    registro *buffer = (registro*) malloc(K*sizeof(registro));
    */

    //Declara a estrutura que conterá todos os arquivos temporários abertos.
    struct arquivo* arq;
    arq = (struct arquivo*) malloc(numArqs * sizeof(struct arquivo));

    //Abre todos os arquivos e inicializa os buffers
    for(i = 0; i < numArqs; i++){
        sprintf(novo,"Temp%d.txt",i+1);
        arq[i].f = fopen(novo,"r");
        arq[i].maximo = 0;
        arq[i].pos = 0;
        arq[i].entrada = criaBuffer(tamBufferEntrada);

        //mexer nessa função
        preencheBuffer(&arq[i],tamBufferEntrada);

        //Preenche a fila de prioridades com um arquivo de cada buffer.
        removerBuffer(arq[i].entrada,&r);
        e.arqOrigem = i; //Atribui o arquivo de origem.
        e.info = r;
        selecionaFilaInsere(fila,numFila,e);
    }

    tipoInfo menor;
    //Retira o menor elemento da fila e insere no buffer de saida.
    while(procuraMenor(arq,numArqs,fila,numFila,tamBufferEntrada,&menor) == 1){
        inserirBuffer(saida,menor.info);
        //Verifica se o buffer esta cheio, caso esteja, salva o conteudo no arquivo e esvazia o buffer.
        if(bufferCheio(saida))
            salvaArquivoOrdenado(nome, saida);
    }
    //Verifica se ainda existem arquivos no buffer, caso hajam, salva o conteúdo no arquivo.
    if(!bufferVazio(saida))
        salvaArquivoOrdenado(nome, saida);

    //Libera a memória alocada para os buffers e as estruturas.
    for(i = 0; i < numArqs; i++)
        terminaBuffer(arq[i].entrada);
    free(arq);
    terminaBuffer(saida);
}//merge()

/*Retira o menor elemento da fila e controla o fluxo de inserção de elementos no buffer de entrada.*/
int procuraMenor(struct arquivo* arq, int numArqs, void* fila, int numFila,int tamBufferEntrada, tipoInfo *menor){
    tipoInfo aux;
    registro r;

    //Verifica se a fila esta vazia.
    if(retornaTamanhoFila(fila,numFila) != 0){
        selecionaFilaRemove(fila,numFila,&aux);
        *menor = aux;
        int posicao = aux.arqOrigem;
        //Verifica o buffer que originou o arquivo removido se possui mais valores.
        if(!bufferVazio(arq[posicao].entrada)){
            removerBuffer(arq[posicao].entrada,&r);
            aux.info = r;
            aux.arqOrigem = posicao;
            selecionaFilaInsere(fila,numFila,aux);
        }
        else{
            //Caso o buffer esteja vazio, preenche com buffer com mais valores do arquivo.
            preencheBuffer(&arq[posicao],tamBufferEntrada);
            if(!bufferVazio(arq[posicao].entrada)){
                aux.info = r;
                aux.arqOrigem = posicao;
                selecionaFilaInsere(fila,numFila,aux);
            }
        }
        return 1;
    }
    return 0;
}//procuraMenor()

//Preenche o buffer com os valores do arquivo.
void preencheBuffer(struct arquivo* arq, int tamBuffer){
    int i;
    if(arq->f == NULL) return;

    registro e;

    arq->pos = 0;
    arq->maximo = 0;
    for(i = 0; i < tamBuffer; i++){
        //Verifica se não chegou ao fim do arquivo.
        if(!feof(arq->f)){
            fscanf(arq->f,"%d",&e.chave);
            inserirBuffer(arq->entrada,e);
            arq->maximo++;
        }else{
            fclose(arq->f);
            arq->f = NULL;
            break;
        }
    }
}//preencheBuffer()


//Função de comparação utilizada pela função qsort para ordenar o array
int compara(const void* a, const void* b){
    if((*(registro*)a).chave == (*(registro*)b).chave) return 0;
    else
        if((*(registro*)a).chave < (*(registro*)b).chave) return -1;
    else
        return 1;
}//compara()

void selecionaFilaInsere(void* fila, int numFila,tipoInfo info){
   filaHeap fh;
    Lista fl;
    if(numFila == 0){
        fh = (filaHeap) fila;
        insereFilaHeap(fh,info);
    }else{
        fl = (Lista) fila;
        insereListaOrdenado(fl,info);
    }
}

void selecionaFilaRemove(void* fila, int numFila,tipoInfo *info){
    filaHeap fh;
    Lista fl;
    if(numFila == 0){
        fh = (filaHeap) fila;
        removeFilaHeapInicio(fh,info);
    }else{
        fl = (Lista) fila;
        retiraListaInicio(fl,info);
    }
}

int retornaTamanhoFila(void* fila, int numFila){
    filaHeap fh;
    Lista fl;
    if(numFila == 0){
        fh = (filaHeap) fila;
        return fh->tamanho;
    }else{
        fl = (Lista) fila;
        return fl->tamanho;
    }
}
