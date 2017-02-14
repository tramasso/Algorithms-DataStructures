//************************************************************************
// Ordenação - heapSort
// Autor: Lucas de Morais Tramasso
// Matricula: 86859
// Data: 17/03/2015
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

void heapRefaz(TItem *A, int esq, int dir)
{
    int i=esq,j; //inicializa o indice i no nó pai atual
    j = (2*i)+1; //inicializa o indice j no filho da esq do nó pai atual
    TItem chave = A[esq]; //armazena o pai em uma chave
    while(dir>=j){      //loop enquanto os filhos estiverem dentro do vetor sendo analizado
        if(dir > j){    //se o j estiver dentro do vetor sendo analizado e não for o ultimo
            if(A[j+1].Chave > A[j].Chave){ //compara os dois filhos e verifica qual é maior
                j++;                       //como o filho da direita é maior, j++
            }
        }
        if(chave.Chave >= A[j].Chave) // se o pai armazenado for maior que o maior filho
            break;                    //interrompe o loop
            A[i] = A[j];              //se o pai for menor que o maior filho, troca o pai e filho
            i=j;                      //atualiza o contador
            j = (2*i)+1;              //atualiza o contador
        
    }
    A[i] = chave;                     //posição i vai receber o pai armazenado
    
}

void heapConstroi(TItem *A, int n)
{
    int esq;
    for(esq =(n/2)-1; esq>=0;esq--){ //loop da metade do vetor até zero
        heapRefaz(A, esq, n-1);      //heapRefaz da metade do vetor até zero
        //como os nós de n/2 até n-1 são folhas, o loop inicia do n/2-1 e vai até 0
    }
}

void heapSort(TItem *A, int n)
{
    heapConstroi(A, n);  //constrói o heap
    TItem aux;
    int i;
    for(i=n-1;i>=0;i--){  //loop que percorre desde a ultima posição até a primeira prosição do vet
        aux = A[0];       //variavel aux recebe o primeiro valor do vetor para efetuar a troca
        A[0] = A[i];      //primeira pos do vetor recebe o ultimo item do vetor
        A[i] = aux;       //finalmente o ultimo recebe o primeiro que estava armazenado em aux
        heapRefaz(A, 0, i-1); //refaz o heap
    }
}

int main()
{
    TItem *A;
    int n;
    
    n = Carrega(&A);
    heapRefaz(A, 0, n-1);
    Imprime(A, n);
    heapConstroi(A, n);
    Imprime(A, n);
    heapSort(A, n);
    Imprime(A, n);
    Libera(&A);
    
    return 0;
}