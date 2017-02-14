/* This program receives a file of processes arriving to a processor
    it uses a cyclic queue to manage the data. Each process has an arrival time
    number of priority and how many clocks to finish that process.

    The program then gives an output file showing how the process are going to be
    processed based on their priority index. The higher the priority index, the faster
    the process needs to be processes 

    Each processing cycle of the queue is divided in 3. It loads new processes, then on S it adds the
    process that came first into the processor at that round and then on L one clock is gone and decreased from
    the process that has higuest priority.

    At the end there is the solution for following input. 
    1 2 2
    1 5 2
    3 5 2
    4 1 1
    4 7 1
    5 3 1
    10 2 1
*/
//  Created by Lucas Tramasso on 10/17/14.
//  Copyright (c) 2014 Lucas Tramasso. All rights reserved.
//

#include <stdio.h>
#define M 10
typedef struct elemento{
    int tempoChegada;
    int prioridade;
    int clock;
}tipoElemento;
struct filaCircular{
    int primeiro;
    int ultimo;
    tipoElemento elementos[M];
};
typedef struct filaCircular tipoFC;
void inicializaFila(tipoFC *filaAux){ //Inicializa a fila
    int i;
    filaAux->primeiro = -1;
    filaAux->ultimo = -1;
    for(i=0;i<M;i++){
        filaAux->elementos[i].tempoChegada=0;
        filaAux->elementos[i].prioridade=0;
        filaAux->elementos[i].clock=0;
    }
}
int filaVazia(tipoFC *filaAux){
    if((filaAux->ultimo == -1)&&(filaAux->primeiro==-1))
        return 1; //Fila está vazia
    else return 0; //Fila não está vazia
    
}

int filaCheia(tipoFC *filaAux){
    if(((filaAux->ultimo +1)%M)==filaAux->primeiro)
        return 1; //Fila cheia
    else return 0; //Fila não está cheia
}

void insereFila(tipoFC *filaAux,int info1,int info2,int info3){ //Inserir elemento na fila
    if (filaCheia(filaAux) == 1){ //verifica se a fila está cheia
        printf(" --- Fila Cheia ---\n");
        return;
    }
    int posicao = (filaAux->ultimo +1)%M;
    if(filaVazia(filaAux) == 1){ //verifica se a fila está vazia
        filaAux->elementos[posicao].tempoChegada = info1; //info1 = tempoChegada
        filaAux->elementos[posicao].prioridade = info2;   //info2 = prioridade
        filaAux->elementos[posicao].clock = info3;        //info3 = clock
        filaAux->primeiro = posicao; //Atualiza o primeiro elemento da fila
        filaAux->ultimo = posicao;   //Atualiza o ultimo elemento da fila
    }else{
        filaAux->elementos[posicao].tempoChegada = info1; //info1 = tempoChegada
        filaAux->elementos[posicao].prioridade = info2;   //info2 = prioridade
        filaAux->elementos[posicao].clock = info3;        //info3 = clock
        filaAux->ultimo = posicao;   //Atualiza o ULTIMO elemento da fila
    }
}
tipoElemento removeFila(tipoFC *filaAux){ //Remove um elemento da fila
    tipoElemento removido;
    removido.tempoChegada = -1;
    removido.prioridade = -1;
    removido.clock = -1;
    if(filaVazia(filaAux)==1){   //Verifica se a fila está vazia
        printf(" --- Fila Vazia ---\n");
    }
    if(filaAux->primeiro == filaAux->ultimo){ //Verifica se a fila possui somente um elemento
        removido.tempoChegada = filaAux->elementos[filaAux->primeiro].tempoChegada;
        removido.prioridade = filaAux->elementos[filaAux->primeiro].prioridade;
        removido.clock = filaAux->elementos[filaAux->primeiro].clock;
        inicializaFila(filaAux); //Remove o único elemento da fila
    }else{
        removido.tempoChegada = filaAux->elementos[filaAux->primeiro].tempoChegada;
        removido.prioridade = filaAux->elementos[filaAux->primeiro].prioridade;
        removido.clock = filaAux->elementos[filaAux->primeiro].clock;
        filaAux->elementos[filaAux->primeiro].tempoChegada=0; //Remove o elemento
        filaAux->elementos[filaAux->primeiro].prioridade=0;
        filaAux->elementos[filaAux->primeiro].clock=0;
        filaAux->primeiro = (filaAux->primeiro +1)%M;  //Atualiza o primeiro da fila
    }
    
    return removido;
}

void imprimeFila(tipoFC *filaAux,FILE *arq){   //Imprime a fila
    int j = filaVazia(filaAux);
    if(j==1){       //Verifica se a fila está vazia
        fprintf(arq,"| - |");
        return;
    }
    int i=filaAux->primeiro;
    fprintf(arq,"|");
    while(i != filaAux->ultimo){     //Percorre a fila até o ultimo elemento
        fprintf(arq,"%d:%d,",filaAux->elementos[i].prioridade,filaAux->elementos[i].clock);
        i = (i+1)%M;
    }
        fprintf(arq,"%d:%d|",filaAux->elementos[i].prioridade,filaAux->elementos[i].clock);
    
}
void insereFilaSimples(tipoFC *filaAux,tipoFC *filaSimples,int info1){
   int i,j=0,k;
   for(i=filaAux->primeiro;i<=filaAux->ultimo;i = (i+1)%M)
       if(filaAux->elementos[i].prioridade > 0){
       if(filaAux->elementos[i].tempoChegada == info1){
           insereFila(filaSimples,filaAux->elementos[i].tempoChegada,filaAux->elementos[i].prioridade,filaAux->elementos[i].clock);
           j++;
           
       }
       }
    for(k=0;k<j;k++){
        removeFila(filaAux);
    }
    
}

int buscaPrioridade(tipoFC *filaAux){
        int i;
        int a = filaAux->primeiro;  //A é inicializado com o índice do primeiro elemento
        for(i=filaAux->primeiro;i<=filaAux->ultimo;i = (i+1)%M){  //Percorre toda a fila
            if(filaAux->elementos[i].prioridade > filaAux->elementos[a].prioridade){    //compara dois elementos
            if(filaAux->elementos[i].prioridade == filaAux->elementos[a].prioridade){
                    if(filaAux->elementos[i].clock<filaAux->elementos[a].clock){
                        a = i;
                    }
                }
                a = i;                                            // a recebe o maior elemento da comparaçao
            }
        }
        return a;
    }

void inserePrioridade(tipoFC *filaSimples, tipoFC *filaPrioridade){
    int i = filaVazia(filaSimples);
    if(i != 1){
        tipoElemento removido = removeFila(filaSimples);
    insereFila(filaPrioridade, removido.tempoChegada, removido.prioridade, removido.clock);
        }
    
}
void removePrioridade(tipoFC *filaAux){  //Remove o maior elemento da fila
    int busca = buscaPrioridade(filaAux);
    if(filaAux->primeiro == busca){  //Remove o primeiro da fila
        removeFila(filaAux);
        return;
    }
    if(filaAux->ultimo == busca){  //Remove o último da fila
        filaAux->ultimo = ((filaAux->ultimo+M)-1)%M;
        return;
    }
    int i = busca;
    do{                //Percorre a fila a partir do elemento que deseja deletar
        filaAux->elementos[i].tempoChegada = filaAux->elementos[(i+1)%M].tempoChegada;  //Realoca a fila
        filaAux->elementos[i].prioridade = filaAux->elementos[(i+1)%M].prioridade;
        filaAux->elementos[i].clock = filaAux->elementos[(i+1)%M].clock;
        i = (i+1)%M;
    }while(i!=filaAux->ultimo);
    filaAux->elementos[filaAux->ultimo].tempoChegada = 0;
      filaAux->elementos[filaAux->ultimo].prioridade = 0;
      filaAux->elementos[filaAux->ultimo].clock = 0;
    filaAux->ultimo = ((filaAux->ultimo+M)-1)%M; //Altera o índice do último
    return;
}


int main(){
    tipoFC filaComandos,filaSimples,filaPrioridade;
    inicializaFila(&filaComandos);
    inicializaFila(&filaPrioridade);
    inicializaFila(&filaSimples);
    int k = 1;
    int info1,info2,info3;
    FILE *arq,*arq2;
    arq = fopen("Comandos.txt","r");
    while(!feof(arq)){
        fscanf(arq,"%d %d %d",&info1,&info2,&info3);
        insereFila(&filaComandos, info1, info2, info3);
    }
    fclose(arq);
    arq2 = fopen("Solucao.txt","w");
    do{
        insereFilaSimples(&filaComandos, &filaSimples, k);
        fprintf(arq2,"\n|%d",k);
        fprintf(arq2,"|L|");
        imprimeFila(&filaSimples,arq2);
        imprimeFila(&filaPrioridade,arq2);
        inserePrioridade(&filaSimples, &filaPrioridade);
        fprintf(arq2,"\n|%d",k);
        fprintf(arq2,"|S|");
        imprimeFila(&filaSimples,arq2);
        imprimeFila(&filaPrioridade,arq2);
        fprintf(arq2,"\n|%d",k);
        fprintf(arq2,"|P|");
        imprimeFila(&filaSimples,arq2);
        int prioridade = buscaPrioridade(&filaPrioridade);
        filaPrioridade.elementos[prioridade].clock--;
        if(filaPrioridade.elementos[prioridade].clock == 0){
            removePrioridade(&filaPrioridade);
        }
            imprimeFila(&filaPrioridade,arq2);
        k++;
    }while(k<11);
    fclose(arq2);
    }

/* 

|1|L||2:2,5:2|| - |
|1|S||5:2||2:2|
|1|P||5:2||2:1|
|2|L||5:2||2:1|
|2|S|| - ||2:1,5:2|
|2|P|| - ||2:1,5:1|
|3|L||5:2||2:1,5:1|
|3|S|| - ||2:1,5:1,5:2|
|3|P|| - ||2:1,5:2|
|4|L||1:1,7:1||2:1,5:2|
|4|S||7:1||2:1,5:2,1:1|
|4|P||7:1||2:1,5:1,1:1|
|5|L||7:1,3:1||2:1,5:1,1:1|
|5|S||3:1||2:1,5:1,1:1,7:1|
|5|P||3:1||2:1,5:1,1:1|
|6|L||3:1||2:1,5:1,1:1|
|6|S|| - ||2:1,5:1,1:1,3:1|
|6|P|| - ||2:1,1:1,3:1|
|7|L|| - ||2:1,1:1,3:1|
|7|S|| - ||2:1,1:1,3:1|
|7|P|| - ||2:1,1:1|
|8|L|| - ||2:1,1:1|
|8|S|| - ||2:1,1:1|
|8|P|| - ||1:1|
|9|L|| - ||1:1|
|9|S|| - ||1:1|
|9|P|| - || - |
|10|L||2:1|| - |
|10|S|| - ||2:1|
|10|P|| - || - |
*/