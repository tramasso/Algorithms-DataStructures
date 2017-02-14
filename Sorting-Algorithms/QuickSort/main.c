
//************************************************************************
// Ordenação - QuickSort
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

int quickSort_particao(TItem *A, int p, int r)
{
    //variáveis auxiliares para efetuar troca de valores
    TItem aux,aux2;
    //variáveis que percorrerão o vetor
    int i,j;
    //j é inicializado no início do vetor
    j = p;
    //i é inicializado uma posicao antes de j
    i = j-1;
    //aux recebe o ultimo valor do vetor
    aux = A[r];
    //loop que percorre todo vetor r
    while(j<r){
        //se a chave da posicao j for maior que a chave contida em aux
        if(A[j].Chave < aux.Chave){
            //i avança uma posicao
            i++;
            //troca o item da posicao i com o item da posicao j
            aux2 = A[i];
            A[i] = A[j];
            A[j] = aux2;
            //j avanca uma posicao
            j++;
        }
        //se a chave da posicao j for maior ou igual à chave armazenada em aux
        if(A[j].Chave >= aux.Chave)
            //j avanca uma posicao, i fica parado
            j++;
    }
    //coloca o pivo que esta na ultima posicao na posicao i+1 que é sua posicao em ordem
    aux2 = A[i+1];
    A[i+1] = A[r];
    A[r] = aux2;
    //retorna a posicao do pivo
    return i+1;
    
    
}

void quickSort_ordena(TItem *A, int p, int r)
{
    //enquanto o vetor tiver comprimento > 1
    if (r>p){
        //particiona o vetor e recebe o pivo da particao
        int q = quickSort_particao(A, p, r);
        //executa a recursao a esquerda do pivo
        quickSort_ordena(A,p,q-1);
        //executa a recursao a direita do pivo
        quickSort_ordena(A,q+1,r);
        
    }
}

    void quickSort(TItem *A, int n)
    {
        quickSort_ordena(A, 0, n-1);
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