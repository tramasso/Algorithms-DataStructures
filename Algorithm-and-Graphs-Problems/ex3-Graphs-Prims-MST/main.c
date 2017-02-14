//
//  main.c
//  ex3
//
//  Created by Lucas Tramasso on 5/11/16.
//  Copyright © 2016 Lucas Tramasso. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node{
    int tag;
    int dist;
    struct node *prox;
}tNode;

typedef struct graph{
    struct node *first;
    struct node *last;
}tGraph;

void graphInit(tGraph *graph,int m){
    int i;
    for(i=0;i<m;i++){
        graph[i].first = NULL;
        graph[i].last = NULL;
    }
}
void addNode(tGraph *graph,int pos,int tag,int dist){
    tNode *node = (tNode*)malloc(sizeof(tNode));
    node->dist = dist;
    node->tag = tag;
    node->prox = NULL;
    
    if(graph[pos].first == NULL){
        graph[pos].first = node;
        graph[pos].last = node;
    }else{
        graph[pos].last->prox = node;
        graph[pos].last = graph[pos].last->prox;
    }
    
}

int sum(int *info,int m){
    int i;
    int sum = 0;
    for(i=0;i<m;i++){
        sum += info[i];
    }
    return sum;
}

int findLower(int *info,int *isRemoved,int m){
    int i;
    int min = INT_MAX, minIndex = 0;
    for(i=0;i<m;i++){
        if(isRemoved[i] == 0 && info[i] < min){
            min = info[i];
            minIndex = i;
        }
    }
    return minIndex;
}

int mstPrim(tGraph *graph, int *info,int m){
    int aux,i;
    info[0] = 0;
    
    /* vetor que  armazena nós já analisados */
    int *isRemoved = (int*)calloc(m,sizeof(int));
    
    tNode *node;
    
    for(i=0;i<m;i++){
        aux = findLower(info, isRemoved,m); /* encontra o menor numero da lista que ainda não foi removido */
        isRemoved[aux] = 1; /* marca ele como removido */
        node = graph[aux].first; /* aponta para sua lista de adjacentes */
        
        /* percorre a lista verificando as distancias */
        while(node != NULL){
                if(isRemoved[node->tag] == 0 && node->dist < info[node->tag]){
                    info[node->tag] = node->dist;
                }
            node = node->prox;
        }
    }
    return sum(info, m);
}



int main(){
    int m,n,i,maxDist = 0;
    int u,v,w;
    
    scanf("%d %d",&m,&n);
    
    tGraph *graph = (tGraph*)malloc(m*sizeof(tGraph));
    graphInit(graph, m);

    int *info = (int*)malloc(m*sizeof(int));

    for (i=0;i<n;i++){
        scanf("%d %d %d",&u,&v,&w);
        addNode(graph, u, v, w);
        addNode(graph, v, u, w);
        maxDist += w;
        if(i < m){
            info[i] = INT_MAX;
        }
    }

    int a = mstPrim(graph, info, m);
    printf("%d\n",maxDist-a);

    return 0;

}

