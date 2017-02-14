
//************************************************************************
// Tarefa 14 - Hash Enderecamento aberto
// Autor: Lucas de Morais Tramasso
// Matricula: 86859
// Data: 15/05/2015
// Curso : BCT
// Prof: Jurandy
//************************************************************************
//
#include <stdio.h>
#include <stdlib.h>

#define NIL -1

typedef int TChave;

typedef struct {
    TChave Chave;
    /* outros compomentes */
} TItem;

typedef int TIndice;

typedef struct {
    TItem *Item;
    TIndice m, n;
} THash;

TIndice h(THash *T, TChave k)
{
    return k % T->m;
}

TIndice H(THash *T, TChave k, int i)
{
    return (h(T, k) + i) % T->m;
}

THash *Inicializa(int m)
{
    TIndice i;
    THash *T;
    
    T = (THash *) malloc(sizeof(THash));
    
    T->n = 0; T->m = m;
    T->Item = (TItem *) malloc(T->m * sizeof(TItem));
    for (i = 0; i < T->m; i++)
        T->Item[i].Chave = NIL;
    
    return T;
}

TIndice Pesquisa(THash *T, TChave x)
{
    int i=0; //variavel i da funcao H
   // TIndice aux = H(T, x, i); //calcula h de x;
    while(T->Item[H(T, x, i)].Chave != x && i < T->m){ //procura o elemento na lista incrementando i quando necessario
        i++;
    }
    if(T->Item[H(T,x,i)].Chave ==x){ //se encontrar x
        return H(T, x, i); //retorna a pos de x
    }
    return NIL; //retorna NIL se nao encontrar
}

int Insere(THash *T, TItem x)
{
    if (T->n == T->m) { //verifica se o hash esta cheio
        return 0;
    }
    if (Pesquisa(T, x.Chave) != NIL) { // se a pesquisa encontrou o numero a ser inserido na tabela
        return 0; //nao insere o numero
    }
    int i =0; // i da funcao H
    while (T->Item[H(T,x.Chave,i)].Chave != NIL && i< T->m) { //enquanto houverem numeros no hash procura uma posicao livre
        i++;
    }
    T->Item[H(T,x.Chave,i)] = x; //insere o elemento na pos encontrada
    T->n++;
    return 1;
}


void Carrega(THash *T)
{
    int i, n;
    TItem x;
    
    scanf("%d", &n);
    for (i = 0; i < n ; i++) {
        scanf("%d", &x.Chave);
        Insere(T, x);
    }
}

void Libera(THash **T)
{
    THash *aux;
    aux = *T;
    if (aux != NULL) {
        if (aux->Item != NULL) free(aux->Item);
        free(aux);
        (*T) = NULL;
    }
}

void Imprime(THash *T)
{
    int i;
    if (T->m > 0) {
        for (i = 0; i < T->m; i++)
            printf("[%d] %d\n", i, T->Item[i].Chave);
    }
}

int main()
{
    TIndice m;
    THash *T;
    TItem x;
    
    scanf("%d", &m);
    T = Inicializa(m);
    Carrega(T);
    scanf("%d", &x.Chave);
    if (Pesquisa(T, x.Chave) == NIL)
        Insere(T, x);
    Imprime(T);
    Libera(&T);
    
    return 0;
}