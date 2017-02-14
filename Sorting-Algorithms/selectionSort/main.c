//************************************************************************
// Ordenação - Seleção
// Autor: Lucas de Morais Tramasso
// Matricula: 86859
// Data: 05/03/2015
// Curso : BCT
// Prof: Jurandy
//************************************************************************
#include <stdio.h>
#include <stdlib.h>

typedef int TChave;

typedef struct {
    TChave Chave;
    /* outros compomentes */
} TItem;

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

void Ordena(TItem *A, int n)
{
    int i,j,indice;
    TItem aux;
    for(i=0;i<n;i++){
    //loop que atualiza o indice do valor a ser comparado
        indice = i;
        for(j=i+1;j<n;j++){
    //percorre todo o vetor procurando algum valor menor do que A[i]
            if(A[indice].Chave > A[j].Chave){
    //encontra um valor menor do que A[i] atualiza o indice de menor valor
                indice = j;
            }
        }
        aux = A[indice];
        A[indice] = A[i];
        A[i] = aux;
    //realiza a troca entre duas chaves
    }
}

int main()
{
    TItem *A;
    int n;
    
    n = Carrega(&A);
    Ordena(A, n);
    Imprime(A,n);
    Libera(&A);
    
    return 0;
}