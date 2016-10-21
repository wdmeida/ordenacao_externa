#ifndef REGISTRO_H_INCLUDED
#define REGISTRO_H_INCLUDED

typedef int Chave;

typedef struct{
    Chave chave;
    /*Outras infos
     char teste[508];*/
}registro;

typedef struct{
    registro info;
    int arqOrigem;
}tipoInfo;

#endif // REGISTRO_H_INCLUDED
