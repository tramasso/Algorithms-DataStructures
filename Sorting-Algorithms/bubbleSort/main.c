//************************************************************************
// Ordenação - Bolha
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
    printf("Digite a quantidade de números a serem ordenados\n");
    scanf("%d", &n);
    
    (*A) = Aloca(n);
    for (i = 0; i < n ; i++){
        printf("\nDigite o %d número: \n", i+1);
        scanf("%d", &(*A)[i].Chave);
    }
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
    TItem aux;
    for(i=0;i<n-1;i++){
    //loop para percorrer o vetor e ver a partir de que indice o vetor ja está ordenado
        for(j=0;j<n-i-1;j++){
    //loop para efetuar as trocas até o fim do vetor ( da parte desordenada já que após n-i o vetor já está ordenado)
            if(A[j].Chave > A[j+1].Chave){
                aux = A[j+1];
                A[j+1] = A[j];
                A[j] = aux;
    //se caso um elemento é maior que o proximo então ambos trocam de posição
            }
            
        }
    }
}

int main()
{
    TItem *A;
    int n;
    printf("-- Algoritmo de Ordenação Bubblesort Inicializado --\n");
    n = Carrega(&A);
    Ordena(A, n);
    Imprime(A,n);
    Libera(&A);
    
    return 0;
}