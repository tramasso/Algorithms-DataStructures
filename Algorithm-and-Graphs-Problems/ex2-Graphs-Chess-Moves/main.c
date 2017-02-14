//
//  main.c
//  ex2
//
//  Created by Lucas Tramasso on 5/10/16.
//  Copyright © 2016 Lucas Tramasso. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int i;
    int j;
    struct node *prox;
}tNode;
typedef struct queue{
    tNode *first;
    tNode *last;
}tQueue;


void queueInit(tQueue *queue){
    queue -> first = NULL;
    queue -> last = NULL;
}
void queueInsert(tQueue *queue,int xCord,int yCord){
    tNode *new = (tNode*)malloc(sizeof(tNode));
    new -> i = xCord;
    new -> j = yCord;
    new -> prox = NULL;
    if(queue->first == NULL){
        queue->first = new;
        queue->last = new;
    }else{
        queue->last->prox = new;
        queue->last = new;
    }
}
/*void queuePrint(tQueue *queue,int *graph){
    tNode *aux;
    aux = queue->first;
    while(aux != NULL){
        printf("x: %d y: %d dist: %d\n",aux->i,aux->j,graph[aux->i*8 + aux->j]);
        aux = aux->prox;
        
    }
 
}*/

tNode *queueRemove(tQueue *queue){
    tNode *aux = queue->first;
    queue->first = queue->first->prox;
    return aux;
}



int BFS(int i,int j,int iLast,int jLast){
    int k=0;
    tNode *t;
    
    /* vetor que contem o tabuleiro */
    
    int board[64];
    for(k = 0;k < 64; k++)
            board[k] = -1;
    
    tQueue *queue = (tQueue*)malloc(sizeof(tQueue));
    
    queueInit(queue);
    board[(i*8)+j] = 0;
    queueInsert(queue,i,j);


    while(board[(iLast*8)+jLast] == -1){
 
        t = queueRemove(queue);

        /* Enfileira cada nó adjacente que está dentro do tabuleiro e ainda não foi visitado*/
        
        int ci = t->i;
        int cj = t->j;
        int v = ci*8+cj;
        int aux;
        
        aux = (ci-2)*8 + (cj+1);
        if(ci-2 >= 0 && cj+1 <= 7 && board[aux] == -1){ board[aux] = board[v] + 1; queueInsert(queue, ci-2, cj+1); }
        
        aux = (ci-1)*8 + (cj+2);
        if(ci-1 >= 0 && cj+2 <= 7 && board[aux] == -1){ board[aux] = board[v] + 1; queueInsert(queue, ci-1, cj+2); }
        
        aux = (ci+1)*8 + (cj+2);
        if(ci+1 <= 7 && cj+2 <= 7 && board[aux] == -1){ board[aux] = board[v] + 1; queueInsert(queue, ci+1, cj+2); }
        
        aux = (ci+2)*8 + (cj+1);
        if(ci+2 <= 7 && cj+1 <= 7 && board[aux] == -1){ board[aux] = board[v] + 1; queueInsert(queue, ci+2, cj+1); }
        
        aux = (ci+2)*8 + (cj-1);
        if(ci+2 <= 7 && cj-1 >= 0 && board[aux] == -1){ board[aux] = board[v] + 1; queueInsert(queue, ci+2, cj-1); }
        
        aux = (ci+1)*8 + (cj-2);
        if(ci+1 <= 7 && cj-2 >= 0 && board[aux] == -1){ board[aux] = board[v] + 1; queueInsert(queue, ci+1, cj-2); }
        
        aux = (ci-1)*8 + (cj-2);
        if(ci-1 >= 0 && cj-2 >= 0 && board[aux] == -1){ board[aux] = board[v] + 1; queueInsert(queue, ci-1, cj-2); }
        
        aux = (ci-2)*8 + (cj-1);
        if(ci-2 >= 0 && cj-1 >= 0 && board[aux] == -1){ board[aux] = board[v] + 1; queueInsert(queue, ci-2, cj-1); }
        
    
        
    };
    /* retorna a distancia da origem até a posicao desejada */
    
    return board[(iLast*8)+jLast];
}

int main(){
    char begin;
    char end;
    int b;
    int e;
    int a;
    scanf("%c%d %c%d",&begin,&b,&end,&e);
    
    int l = begin - 97;
    int xl = end - 97;
    

    a = BFS(b-1,l,e-1,xl);
    printf("%d\n",a);
    
    return 0;
}