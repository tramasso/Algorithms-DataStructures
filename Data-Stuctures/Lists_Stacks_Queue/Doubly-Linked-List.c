//************************************************************************
// Doubly Linked list - Sorted Insertion,Print numbers and removes numbers at any position
// Author: Lucas de Morais Tramasso
// Date: 09/05/2014
// Prof: Valério Rosset
//************************************************************************

#include <stdio.h>
#include <stdlib.h>
typedef struct elemento{ //Structure of one element of the list
    int info;
    struct elemento *prox;
    struct elemento *ant;
}tipoElemento;
typedef struct estruturaLDDE{ //List Structure with pointers to first and Left
    tipoElemento *primeiro;
    tipoElemento *ultimo;
    int tamanhoLista;
}tipoLDDE;

void inicializaLista(tipoLDDE *listaAux){ //Initialize the list
    listaAux->primeiro=NULL;
    listaAux->ultimo=NULL;
    listaAux->tamanhoLista = 0;
}
void insereElementoFinal(tipoLDDE *listaAux,int info){  //Function to insert at the end of the list
    tipoElemento *novo = (tipoElemento*)malloc(sizeof(tipoElemento));
    novo->info = info;
    if(listaAux->primeiro == NULL){
        novo->prox = NULL;
        novo->ant = NULL;
        listaAux->primeiro = novo;
        listaAux->ultimo = novo;
    }else{
        listaAux->ultimo->prox = novo;
        novo->ant = listaAux->ultimo;
        novo->prox = NULL;
        listaAux->ultimo = novo;
    }
    listaAux->tamanhoLista++;
}
void insereElementoInicio(tipoLDDE *listaAux,int info){ //Function to insert at the beginning of the list
    tipoElemento *novo = (tipoElemento*)malloc(sizeof(tipoElemento));
    novo->info = info;
    if(listaAux->primeiro == NULL){
        novo->prox = NULL;
        novo->ant = NULL;
        listaAux->primeiro = novo;
        listaAux->ultimo = novo;
    }else{
        listaAux->primeiro->ant = novo;
        novo->prox = listaAux->primeiro;
        novo->ant = NULL;
        listaAux->primeiro = novo;
    }
    listaAux->tamanhoLista++;
}
void insereElemento(tipoLDDE *listaAux){ /* Function to insert an element at its sorted position */
    tipoElemento *novo = (tipoElemento*)malloc(sizeof(tipoElemento));
    printf("Type a number to add:\n");
    scanf("%d",&novo->info);
    if(listaAux->primeiro == NULL){
        novo->prox = NULL;
        novo->ant = NULL;
        listaAux->primeiro = novo;
        listaAux->ultimo = novo;
    }else{
        tipoElemento *a;
        a = listaAux->primeiro;
        if(a->info > novo-> info){
            insereElementoInicio(listaAux,novo->info);
            return;
        }
        if(listaAux->ultimo->info < novo->info){
            insereElementoFinal(listaAux,novo->info);
            return;
        }
        while(a->info < novo->info){
            a = a->prox;
        }
        a->ant->prox = novo;
        novo->ant = a->ant;
        novo->prox = a;
        a->ant = novo;
        listaAux->tamanhoLista++;
    }
}
tipoElemento *buscaElemento(tipoLDDE *listaAux){ //Funcion that returns the position of a number
    if(listaAux->primeiro == NULL){
        printf("  --- Empty List ---\n");
        return NULL;
    }
    int b;
    printf("Enter a number to search/remove\n");
    scanf("%d",&b);
    tipoElemento *a;
    a = listaAux->primeiro;
    while(a != NULL){
        if(a->info == b){
            return a;
        }
        a = a->prox;
    }
    return NULL;
}

    
    
    
    

void removeElemento(tipoLDDE *listaAux){ //Function to remove a number at a given position
    if(listaAux->primeiro==NULL){
        printf("   --- Empty List ---\n");
        return;
    }
    tipoElemento *busca = buscaElemento(listaAux);
    if(listaAux->primeiro == busca){                   //Remove the first number
        listaAux->primeiro = listaAux->primeiro->prox;
        free(busca);
        listaAux->primeiro->ant = NULL;
        listaAux->tamanhoLista--;
        printf("\n   ---- Removed ! ----\n");
        return;
    }
    if(busca->prox == NULL){                           //Remove the last number
        listaAux->ultimo = listaAux->ultimo->ant;
        free(busca);
        listaAux->ultimo->prox = NULL;
        listaAux->tamanhoLista--;
        printf("\n   ---- Removed ! ----\n");
        return;
    }else{                                            // remove any other number
        busca->ant->prox = busca->prox;
        busca->prox->ant = busca->ant;
        free(busca);
        printf("\n   ---- Removed ! ----\n");
        return;
    }
    
    
}

void imprimeLista(tipoLDDE *listaAux){  //Prints the list
    if(listaAux->primeiro == NULL){
        printf("  --- Empty List ---\n");
        return;
    }
    tipoElemento *a;
    a = listaAux->primeiro;
    printf("\n\n      ------  List: ");
    while(a != NULL){ // Pointer to iterate over the whole list
        printf("%d, ",a->info);
        a = a->prox;
    }
    printf("\n\n");
}

int main(){
    tipoLDDE lista1;
    inicializaLista(&lista1);
    int a;
    do{
        printf("\n1 - Insert\n2 - Print\n3 - Search\n4 - Remove\n7 - End\n");
        scanf("%d",&a);
    
        if(a==1){
            insereElemento(&lista1);
        }
        if(a==2){
            imprimeLista(&lista1);
        }
        if(a==3){
            tipoElemento *b =  buscaElemento(&lista1);
            if(b == NULL){
                printf("  --- Not Found ---\n");
            }else{
                printf("Number %d was found !\n",b->info);
            }

        }

        if(a==4){
            removeElemento(&lista1);
        }
        
    }  while((a == 1) || (a == 2) || (a == 3) || (a == 4) || (a == 5));
    
    return 0;
}




















