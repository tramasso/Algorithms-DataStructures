

//************************************************************************
// Ordenação - countingSort
// Autor: Lucas de Morais Tramasso
// Matricula: 86859
// Data: 26/03/2015
// Curso : BCT
// Prof: Jurandy
//************************************************************************
//

#include <math.h>
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
void LiberaChave(TChave **A)
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

TChave maiorChave(TItem *A, int n)
{
    TChave max;
    int i;
    
    max = 0;
    for (i = 0; i < n; i++)
        if (A[i].Chave > max)
            max = A[i].Chave;
    
    return max;
}

int numeroDigitos(TChave numero)
{
    return (int)ceil(log10(numero));
}

int retornaDigito(TChave numero, int indice)
{
    return (numero / (int)pow(10, indice)) % 10;
}

void Ordena(TItem *A, int n, int k) // Ajuste o parametro do seu metodo aqui!
{
    //variaveis que são utiizadas como contadores
    int p,j,i;
    TChave *C;
    TItem *B;
    //alocação dos vetores auxiliares, B é do tamanho de A ,C tem tamanho k+1
    //B é utilizado para alocar o vetor ordenado
    B = (TItem*)malloc((n)*sizeof(TItem));
    //C é utilizado para contar quantos de cada número existem no vetor A
    C = (TChave*)malloc((k+1)*sizeof(TChave));
    //loop para preencher todo o vetor C com o número zero
    for(p=0;p<=k;p++){
        C[p] = 0;
    }
    //loop que percorre A e incrementa a posicao de C que é a chave de A[j]
    for(j=0;j<n;j++){
        C[A[j].Chave]++;
    }
    //loop que percorre todo o vetor C e soma a posicao i com a posicao i-1
    for(i=1;i<=k;i++){
        C[i] = C[i] + C[i-1];
    }
    //loop que percorre todo o vetor A
    for(j=n-1;j>=0;j--){
        //o vetor B na posicao da chave de C[chave de A[j]-1] recebe o conteudo de A[j]
        B[C[A[j].Chave]-1] = A[j];
        //como um valor foi adicionado ao vetor B, decrementa C na posicao da chave de A[j]
        C[A[j].Chave] --;
    }
    //copia todo o vetor B que está ordenado para o vetor A
    for(p=0;p<n;p++){
        A[p]=B[p];
    }
    //Desaloca os vetores auxiliares
    Libera(&B);
    LiberaChave(&C);
    
    
}

int main()
{
    TItem *A;
    TChave k;
    int d, n;
    
    n = Carrega(&A);
    k = maiorChave(A, n);
    d = numeroDigitos(k);
    Ordena(A, n, k); // Ajuste o parametro do seu metodo aqui!
    Imprime(A, n);
    Libera(&A);
    
    return 0;
}