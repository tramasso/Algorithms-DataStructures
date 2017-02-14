#define T 5
#include <stdio.h>
void insertionSort(int vet[T]){
int i,j,chave;
    //i e j são contadores e chave é o valor a ser movimentado na iteração
    for(i = 1; i<T;i++){
    //loop que percorre todo o vetor
        chave = vet[i];
        
        j = i-1;
        while((j>=0) && (chave < vet[j])){
    //while utilizado para mover j e comparar a chave com o valor atual de j
                vet[j+1] = vet[j];
                vet[j] = chave;
                j--;
    //Troca os valores já que a chave é menor que j
            }	
		}	
	}