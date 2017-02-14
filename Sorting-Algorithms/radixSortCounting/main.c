
//************************************************************************
// Ordenação - radixSort utilizando countingSort
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
void liberaChave(TChave **A)
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
    return (numero / (int)pow(10, indice)) % 10; //numero da forma d-1 d-2 .... 0
    
    //return ((numero %(int)pow(10, indice)))/((int)pow(10,indice-1)); numero da forma d d-1.....1

}

void Ordena(TItem *A, int n, int  d  ) // Ajuste o parametro do seu metodo aqui!
{
    int radCount;
    //realiza o procedimento de counting sort para cada digito da chave
    for(radCount = 0;radCount <= d-1;radCount++){
    //variaveis utilizadas como contadores
    int p,j,i,k=9;
        //vetores auxiliares
        TItem *B;
        TChave *C;
        //vetor B possui o mesmo tamamho de A e armazena o vetor A ordenado ao fim da execucao
        B = (TItem*)malloc((n)*sizeof(TItem));
        //vetor C possui tamamanho k+1 e mostra a quantidade de cada digito no vetor A
        C = (TChave*)malloc((k+1)*sizeof(TChave));
        //loop que atribui zero a todas as posicoes do vetor C
        for(p=0;p<=k;p++){
            C[p] = 0;
        }
        //loop que percorre todo o vetor A desde a primeira posicao
        for(j=0;j<n;j++){
            //incrementa C[digito d da chave de A[j]] para contar a quantidade de cada digito
            C[retornaDigito(A[j].Chave,radCount)]++;
        }
        //percorre todo o vetor C a partir da segunda posicao
        for(i=1;i<=k;i++){
            //soma o valor de C[i] com o valor de C[i-1]
            C[i] = C[i] + C[i-1];
        }
        //loop que percorre todo o vetor A do fim até o inicio
        for(j=n-1;j>=0;j--){
            //o vetor B na posicao C[digito d de A[j] -1] recebe o conteudo de A[j]
            B[C[retornaDigito(A[j].Chave,radCount)]-1] = A[j];
            //como um digito foi adicionado em B,decrementa a quantidade desse digito em C
            C[retornaDigito(A[j].Chave,radCount)] --;
        }
        //copia todo o vetor B que esta ordenado para A
        for(p=0;p<n;p++){
            A[p]=B[p];
        }
        //Desaloca os vetores
        Libera(&B);
        liberaChave(&C);
    }
    
    
}

int main()
{
    TItem *A;
    TChave k;
    int d, n;
    
    n = Carrega(&A);
    k = maiorChave(A, n);
    d = numeroDigitos(k);
    Ordena(A, n, d); // Ajuste o parametro do seu metodo aqui!
    Imprime(A, n);
    Libera(&A);
    
    return 0;
}