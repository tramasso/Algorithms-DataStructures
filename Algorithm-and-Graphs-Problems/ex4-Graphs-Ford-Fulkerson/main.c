//
//  main.c
//  ex4
//
//  Created by Lucas Tramasso on 6/2/16.
//  Copyright © 2016 Lucas Tramasso. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define min(a,b)  (a < b ? a : b)

typedef struct node{
    int c;
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
void queueInsert(tQueue *queue,int c){
    tNode *new = (tNode*)malloc(sizeof(tNode));
    new -> c = c;
    new -> prox = NULL;
    if(queue->first == NULL){
        queue->first = new;
        queue->last = new;
    }else{
        queue->last->prox = new;
        queue->last = new;
    }
}

tNode *queueRemove(tQueue *queue){
    tNode *aux = queue->first;
    if(queue->first == queue->last){
        queueInit(queue);
    }else{
        
  
    queue->first = queue->first->prox;
    }
    return aux;
}

int bfs(int **resGraph,int begin,int end,int *parents,int N){
    
    int *visited;
    visited = (int*)calloc(N,sizeof(int));
    
    tQueue *queue = (tQueue*)malloc(sizeof(tQueue));
    queueInit(queue);
    queueInsert(queue, begin);
    
    visited[begin] = 1;
    parents[begin] = -1;
    
    while(queue->first != NULL){
        tNode *a = queueRemove(queue);
        int aux = a->c;
        int i;
        
        for(i=0;i<N;i++){
            if(visited[i] == 0 && resGraph[aux][i] > 0){
                queueInsert(queue, i);
                parents[i] = aux;
                visited[i] = 1;
            }
        }
    }
    return (visited[end] == 1);
}

int fordFulkerson(int **graph,int **resGraph,int begin,int end,int N){
    int i,j,max = 0,parents[N];
    
    while(bfs(resGraph,begin,end,parents,N) == 1){

        int thisPath = INT_MAX;
        for(j=end;j!=begin;j = parents[j]){
            i = parents[j];
            thisPath = min(thisPath,resGraph[i][j]);
        }
        for(j=end;j!=begin;j = parents[j]){
            i = parents[j];
            resGraph[j][i] += thisPath;
            resGraph[i][j] -= thisPath;
        }
        
        max += thisPath;
    }
    
    return max;
    
}

int main(){
    int M,N;
    
    scanf("%d %d",&N,&M);
    
    int **graph, **resGraph;
    
    graph = (int**)malloc(N*sizeof(int*));
    resGraph = (int**)malloc(N*sizeof(int*));
    
    int i,j;
    for(j=0;j<N;j++){
        graph[j] = (int*)malloc(N*sizeof(int));
        resGraph[j] = (int*)malloc(N*sizeof(int));
        for(i=0;i<N;i++){
            graph[j][i]=0;
            resGraph[j][i]=0;
        }
        
    }
    
    
    int u,v,c;
    
    for(i=0;i<M;i++){
        scanf("%d %d %d",&u,&v,&c);
        graph[u][v] = c;
        resGraph[u][v] = c;
        
    }
    
    int a = fordFulkerson(graph, resGraph, 0, N-1, N);
    
    printf("%d",a);
    
    return 0;
    
    
}