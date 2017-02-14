//************************************************************************
// Ordenação - mergeSort
// Autor: Lucas de Morais Tramasso
// Matricula: 86859
// Data: 13/03/2015
// Curso : BCT
// Prof: Jurandy
//************************************************************************
//

#include <stdio.h>
#include <stdlib.h>

typedef int TChave;

typedef struct {
    TChave Chave;
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

void mergeSort_intercala(TItem *A, int p, int q, int r)
{
    int i,m,n,j,k;
    TItem *aux;             //vetor auxiliar de mesmo tamanho que o original
    aux = (TItem*)malloc((r-p+1)*sizeof(TItem)); //aloca o vetor
    for(i=p;i<=q;i++){       //percorre  o vetor auxiliar até a metade
        aux[i-p] = A[i];   //copia a primeira metade para o vetor
    }
    for(n=q+1;n<=r;n++){
        aux[r-p+1-n+q] = A[n]; //copia para o vetor aux a segunda metade de forma reversa
    }
    m=p;        //contador posicionado no início do vetor aux
    j=r;        //contador posicionado no fim do vetor aux
    
    for(k=p;k<=r;k++){    //percorre todo o vetor original informando a posicao a ser preenchida
        if(aux[m-p].Chave<aux[j-p].Chave){      //se chave do início for menor que a do fim
            A[k] = aux[m-p];  //adiciona o primeiro de volta no vetor original(em ordem)
            m++;                        //incrementa o contador
        }else{
            A[k] = aux[j-p];  //adiciona o último numero de volta ao vetor original
            j--;                        //decrementa o fim do vetor aux
        }
    }
    Libera(&aux);
}

void mergeSort_ordena(TItem *A, int p, int r)
{
     int q;
    if(r > p){
        q = (r+p)/2;
        mergeSort_ordena(A, p, q);       //recursão do mergesort,metade da esqueda do vetor
        mergeSort_ordena(A, q+1, r);     //metade da direita do vetor
        mergeSort_intercala(A, p, q, r); //intercala as duas metades
        

    }
}

void mergeSort(TItem *A, int n)
{
    mergeSort_ordena(A, 0, n-1);
}

int main()
{
    TItem *A;
    int n;
    
    n = Carrega(&A);
    mergeSort(A, n);
    Imprime(A, n);
    Libera(&A);
    
    return 0;
}