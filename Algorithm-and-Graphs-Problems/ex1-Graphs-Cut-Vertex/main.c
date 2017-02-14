//
//  main.c
//  ex1
//
//  Created by Lucas Tramasso on 4/4/16.
//  Copyright © 2016 Lucas Tramasso. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int tag;
    struct node *prox;
}Tnode;

typedef struct info{
    int visit;
    int parent;
    int lower;
    int time;
    int isVc;
}Tinfo;
int findLower(int a,int b){
    
    return (a < b) ? a : b;
}


void imprime(Tinfo *vetor,int a){
    int i;
    for(i=0;i<a;i++){
        if(vetor[i].isVc == 1)
            printf("%d\n",i);
    }
}

void print(Tnode *graph,int size){
    
    int i;
    for(i=0;i<size;i++){
        Tnode *aux = graph[i].prox;
        while(aux != NULL){
            printf("%d ",aux->tag);
            aux = aux->prox;
        }
        printf("\n");
    }
    
}


void findCutVertex(Tnode *graph,int this,Tinfo *allInfo,int *time){

    int childCount = 0;
    allInfo[this].visit = 1;
    allInfo[this].time = (*time)++;
    allInfo[this].lower = (*time);

    

    Tnode *vertex = graph[this].prox;
    while(vertex != NULL){
            if(allInfo[vertex->tag].visit == 0){
            
                childCount++;
                allInfo[vertex->tag].parent = this;
                findCutVertex(graph, vertex->tag, allInfo,time);
                
                allInfo[this].lower = findLower(allInfo[this].lower, allInfo[vertex->tag].lower);
                
                //DESCOBRR SE EH UM VERTICE DE CORTE ABAIXO
                
                    if(allInfo[this].parent == -1 && childCount > 1){
                        allInfo[this].isVc = 1;
                    }
                    if(allInfo[this].parent != -1 && allInfo[vertex->tag].lower >= allInfo[this].time){
                        allInfo[this].isVc = 1;
                    }
            
            }else if(allInfo[this].parent != vertex->tag)
                allInfo[this].lower = findLower(allInfo[this].lower, allInfo[vertex->tag].time);
        
            vertex = vertex->prox;
   
    }
}

Tinfo *DFS(Tnode *graph,int S){
    Tinfo *allInfo;
    allInfo = (Tinfo*)malloc(S*sizeof(Tinfo));
    int i;
    
    int *time;
    time = (malloc(sizeof(int)));
    
    for (i=0;i<S;i++){
        allInfo[i].parent = -1;
        allInfo[i].visit = 0;
        allInfo[i].isVc = 0;
    }
    
    for (i=0;i<S;i++){
        if(allInfo[i].visit == 0){
            (*time) = 0;
            findCutVertex(graph, i, allInfo,time);
        }
    }
    
    return allInfo;

}

int main(){
    
    int i,N,M,a,b;
    scanf("%d %d",&N,&M);
    Tnode *graph;
    graph = (Tnode*)malloc(N*sizeof(Tnode));
    
    for (i=0;i<M;i++){
        scanf("%d %d",&a,&b);
        
        Tnode *node = (Tnode*)malloc(sizeof(Tnode));
        Tnode *node2 = (Tnode*)malloc(sizeof(Tnode));
        node->tag = b;
        node->prox = NULL;
        
        node2->tag = a;
        node2->prox = NULL;
        
        Tnode *aux = &graph[a];
        Tnode *aux2 = &graph[b];
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = node;
        
        while(aux2->prox != NULL)
            aux2 = aux2->prox;
        aux2->prox = node2;
            
        
    }
    
    //print(graph,N);
   
    Tinfo *answer = DFS(graph, N);

    imprime(answer, N);
    
    free(graph);
    free (answer);
    
}


