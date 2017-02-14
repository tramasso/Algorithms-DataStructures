//************************************************************************
// Binary Search Tree
// Author: Lucas de Morais Tramasso
// Data: 04/11/2015
// Prof: Jurandy
//************************************************************************
//

#include <stdio.h>
#include <stdlib.h>

typedef int TChave;

typedef struct {
    TChave Chave;
    /* Other variables */
} TItem;

typedef struct SNo *TArvBin; // Node pointer

typedef struct SNo {  //Node Structure
    TItem Item;
    TArvBin Esq, Dir;
} TNo;

TArvBin Inicializa()
{
    return NULL; //Initialize
}

TArvBin Pesquisa(TArvBin No, TChave x) //Search for the value x on the tree 
{
    if(No == NULL){
        
        return NULL;
    }
    if(x == No->Item.Chave){
        
        return No;
    }
    if(x > No->Item.Chave){
       
        return Pesquisa(No->Dir, x);
    }else{
        
        return Pesquisa(No->Esq, x);
    }
}
TArvBin insereNo(TItem x){
    TArvBin novo = (TArvBin)malloc(sizeof(TNo));  //Creates a new node
    novo->Item = x;
    novo->Dir = NULL;
    novo->Esq = NULL;
    return novo;
}

int Insere(TArvBin *pNo, TItem x) //Insert in the Tree
{
    if(*pNo == NULL){
       
        *pNo = insereNo(x);
        return 1;
    }
    if(x.Chave == (*pNo)->Item.Chave){
        
        return 0;
    }
    if(x.Chave > (*pNo)->Item.Chave){
        
        return Insere(&(*pNo)->Dir, x);
    }else{
        
        return Insere(&(*pNo)->Esq, x);
    }
    
}
void Libera(TArvBin *pNo)  //Free a node
{
    TArvBin No;
    No = *pNo;
    if (No != NULL) {
        Libera(&No->Esq);
        Libera(&No->Dir);
        free(No);
        (*pNo) = NULL;
    }
}

int Remove(TArvBin *pNo, TChave x)
{
    if(*pNo == NULL){
        
        return 0;
    }
    if(x > (*pNo)->Item.Chave){
        
        return Remove(&(*pNo)->Dir, x);
    }else if(x < (*pNo)->Item.Chave){
        
        return Remove(&(*pNo)->Esq, x);
    }else{
        
        if((*pNo)->Dir == NULL && (*pNo)->Esq == NULL){
            //Remove a node without kids
            (*pNo) = NULL;
        }else if((*pNo)->Dir == NULL){
            //remove a node with a left kid
            TArvBin aux = (*pNo);
            (*pNo) = (*pNo)->Esq;
            aux->Esq = NULL;
            free(aux);
            aux = NULL;
        }else if ((*pNo)->Esq == NULL){
            //remove node with right kid
            TArvBin aux2 = (*pNo);
            (*pNo)=(*pNo)->Dir;
            aux2->Dir = NULL;
            free(aux2);
            aux2 = NULL;
        }else{
            //remove node that has two kids and adds the next value to its place
            TArvBin aux3 = (*pNo)->Dir;
            if(aux3->Esq == NULL){
                (*pNo)->Item = aux3->Item;
                (*pNo)->Dir = aux3->Dir;
                free(aux3);
            }else{

                TArvBin aux4 = aux3;
                aux3 = aux3->Esq;
                    while (aux3->Esq != NULL) {  
                        aux3 = aux3->Esq; 
                        aux4 = aux4->Esq;
                    }
                    (*pNo)->Item = aux3->Item;
                    aux4->Esq = aux3->Dir;
                    free(aux3);
                    free(aux4);
                
            }
            
        }
        return 1;
    }
}


void Carrega(TArvBin *pNo) //Insert  X numbers to a tree
{
    int i, n;
    TItem x;
    scanf("%d", &n);
    for (i = 0; i < n ; i++) {
        scanf("%d", &x.Chave);
        Insere(pNo, x);
    }
}


void Imprime(TArvBin No)  //Print the tree in parentheses representation
{
    if (No != NULL) {
        printf("(C%d", No->Item.Chave);
        Imprime(No->Esq);
        Imprime(No->Dir);
        printf(")");
    }
    else
        printf("()");
}

int main()
{

    /* Main function to test the tree, if the value is note on the tree insert it else remove it */
    /* First enter how many numbers are going to be entered then enter the numbers */
    TArvBin Raiz;
    TItem x;
    Raiz = Inicializa();
    Carrega(&Raiz);
    scanf("%d", &x.Chave);
    if (Pesquisa(Raiz, x.Chave) == NULL)
        Insere(&Raiz, x);
    else
        Remove(&Raiz, x.Chave);
    Imprime(Raiz);
    Libera(&Raiz);
    return 0;
}
