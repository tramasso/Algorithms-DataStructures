
//************************************************************************
// Ordenação - bucketSort
// Autor: Lucas de Morais Tramasso
// Matricula: 86859
// Data: 26/03/2015
// Curso : BCT
// Prof: Jurandy
//************************************************************************
//
#include <stdio.h>
#include <stdlib.h>

typedef int TChave;
typedef struct TC{
    int info;
    struct TC *prox;
    struct TC *ant;
}TC;
typedef struct {
    TChave Chave;
    /* outros compomentes */
} TItem;
typedef struct {
    TC item;
}TLista;
    
TItem *Aloca(int n)
{
    return ((n > 0) ? ((TItem *) malloc(n * sizeof(TItem))) : (NULL));
}

int Carrega(TItem **A)
{
    int i, n;
    
    scanf("%d", &n);
    
    (*A) = Aloca(n);
    for (i = 0; i < n ; i++)
        scanf("%d", &(*A)[i].Chave);
    
    return n;
}
int carregaLista(TItem **A)
{
    int i, n=0;
    
    (*A) = Aloca(n);
    for (i = 0; i < n ; i++)
        scanf("%d", &(*A)[i].Chave);
    
    return n;
}

void Libera(TItem **A)
{
    if ((*A) != NULL) {
        free(*A);
        (*A) = NULL;
    }
}

void Imprime(TItem *A, int n)
{
    int i;
    if (n > 0) {
        printf("%d", A[0].Chave);
        for (i = 1; i < n; i++)
            printf(" %d", A[i].Chave);
        printf("\n");
    }
}
void insereElementoFinal(TLista *listaAux,int info){  //Função para inserir no fim da lista
    TLista *novo;
    //    printf("Digite o número que deseja adicionar\n");
    //  scanf("%d",&novo->info);
    novo->item.info = info;
    if(listaAux[0].item.prox== NULL){
        novo->item.prox = NULL;
        novo->item.ant = NULL;
        listaAux[0].item.prox = novo;
    }else{
        listaAux->ultimo->prox = novo;
        novo->ant = listaAux->ultimo;
        novo->prox = NULL;
        listaAux->ultimo = novo;
    }
    listaAux->tamanhoLista++;
}

int quickSort_particao(TItem *A, int p, int r)
{

    
    
}


int main()
{
    TItem *A;
    int n;
    
    n = Carrega(&A);
    quickSort_particao(A, 0, n-1);
    Imprime(A, n);
    quickSort(A, n);
    Imprime(A, n);
    Libera(&A);
    
    return 0;
}