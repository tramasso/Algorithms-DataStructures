//************************************************************************
// Ordenação - Inserção
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
    int i,j;
    TItem chave;
    for(i=1;i<n;i++){
        chave = A[i];
        for(j=i-1;j>=0;j--){
            if(chave.Chave < A[j].Chave){
                A[j+1]=A[j];
                A[j]=chave;
            }
        }
    
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














