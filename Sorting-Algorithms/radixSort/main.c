
//************************************************************************
// Ordenação - radixSort utilizando insertionSort
// Autor: Lucas de Morais Tramasso
// Matricula: 86859
// Data: 26/03/2015
// Curso : BCT
// Prof: Jurandy
//************************************************************************
//


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
int potencia(int n,int exp){
    int i;
    for(i=0;i<exp;i++){
        n*=exp;
    }
    return n;
}

void insertionSort(TItem *A, int n,int d)
{
    //variaveis i e j sao contadores, aux1 e aux2 armazenam um digito de determinada chave
    int i,j,aux1,aux2;
    //chave é o valor movido nas iteracoes
    TItem chave;
    //percorre todo o vetor A
    for(i=1;i<n;i++){
        //armazena A na posicao i na variavel chave
        chave = A[i];
        //percorre o vetor da posicao i-1 até o inicio do vetor
        for(j=i-1;j>=0;j--){
            //pega o dígito da posição d do número armazenado em chave;
            aux1 = (((chave.Chave)%(int)pow(10,d))/((int)pow(10,d-1)));
            //pega o dígito da posição d do número armazenado no vetor na posição j
            aux2 = ((A[j].Chave)%((int)pow(10,d)))/((int)pow(10,d-1));
            //se o digito d da chave armazenada em chave for menor que o digito d da chave de A[j]
            if(aux1<aux2){
                //troca a chave com a A[j]
                A[j+1]=A[j];
                A[j]=chave;
            }
        }
        
    }
    
    
}
void radixSort(TItem *A,int n,int d){
    int i;
    //realiza o insertion sort para cada digito do numero a partir do ultimo dígito
    for(i=1;i<=d;i++){
        insertionSort(A,n,i);
    }
}

int main()
{
    TItem *A;
    int n,d;
    scanf("%d",&d);
    n = Carrega(&A);
    radixSort(A, n,d);
    Imprime(A,n);
    Libera(&A);
    
    return 0;
}
