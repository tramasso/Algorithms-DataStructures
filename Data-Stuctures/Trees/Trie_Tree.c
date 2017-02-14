

//************************************************************************
// AVL Tree
// Autor: Lucas de Morais Tramasso
// Data: 04/14/2015
// Prof: Jurandy
//************************************************************************


#include <stdio.h>
#include <stdlib.h>

typedef int TChave;

typedef struct {
    TChave Chave;
    /* Any other variables */
} TItem;

typedef struct SNo *TArvBin;

typedef struct SNo {
    TItem Item;
    TArvBin Esq, Dir;
} TNo;

TArvBin Carrega()  //Function to Load a tree in parentheses representation
{
    char c;
    TArvBin No;
    scanf("%c", &c);
    if (c == '(') {
        scanf("%c", &c);
        if (c == 'C') {
            No = (TArvBin) malloc(sizeof(TNo));
            scanf("%d", &No->Item.Chave);
            No->Esq = Carrega();
            No->Dir = Carrega();
            scanf("%c", &c);
        }
        else if (c == ')')
            No = NULL;
    }
    return No;
}

void Libera(TArvBin *pNo) //Free a node
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

void Imprime(TArvBin No)  //Print the tree
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

int Altura(TArvBin No) //Calculate node height
{
    int he=0,hd=0;
    if(No == NULL){
        return -1;
    }else{
        he = Altura(No->Esq);
        hd = Altura(No->Dir);
        if(he >= hd)
            return 1+he;
        else
            return 1+hd;
    }
}

int FB(TArvBin No)  //Calculates Balancing factor
{
    if(No == NULL) 
        return 0; 
    else
        return Altura(No->Esq) - Altura(No->Dir); //returns left height - right height
    
}

int ArvoreAVL(TArvBin No) //Check if a tree is an AVL tree
{
    if(No==NULL)
        return 1; // null tree is AVL
    else if(abs(FB(No) <= 1)){   //if Balancing factor is 0,1 or -1
        if(ArvoreAVL(No->Esq) && ArvoreAVL(No->Dir)){ //if left and right branches are AVL
            return 1; //then it's AVL
        }else
            return 0; //if left or right branches are not AVL
    }else
        return 0; //then its not AVL
}


void LL(TArvBin *pA)  //LEFT LEFT ROTATION
{
    TArvBin pB = (*pA)->Esq; 
    (*pA)->Esq = pB->Dir; 
    pB->Dir = (*pA); 
    (*pA) = pB; 
    
}

void RR(TArvBin *pA) //RIGHT RIGHT ROTATION
{
    //Similar to LL rotation
    TArvBin pB = (*pA)->Dir; 
    (*pA)->Dir = pB->Esq; 
    pB->Esq = (*pA);
    (*pA) = pB;
}

void LR(TArvBin *pA)  //LEFT RIGHT ROTATION
{
    TArvBin pB = (*pA)->Esq; 
    TArvBin pC = pB->Dir; 
    pB->Dir = pC->Esq; 
    pC->Esq = pB; 
    (*pA)->Esq = pC->Dir; 
    pC ->Dir = (*pA); 
    (*pA) = pC; 
}

void RL(TArvBin *pA) //RIGHT LEFT ROTATION
{
    //Similar to LR ROTATION
    TArvBin pB = (*pA)->Dir; 
    TArvBin pC = pB->Esq; 
    pB->Esq = pC->Dir; 
    pC->Dir = pB; 
    (*pA)->Dir = pC->Esq; 
    pC ->Esq = (*pA); 
    (*pA) = pC; 
}
int balancaEsq(TArvBin *pA){  //Function to balance the left branch
    TArvBin pB = (*pA)->Esq; /
    if (FB(pB)>0) { 
        LL(pA); /
    }
    if (FB(pB) < 0){ 
        LR(pA); 
    }
    return 1;
}
int balancaDir(TArvBin *pA){ //Function to balance the right branch
    TArvBin pB = (*pA)->Dir; 
    if (FB(pB)<0) { 
        RR(pA); 
    }
    if (FB(pB) > 0){ 
        RL(pA); 
    }
    return 1;
}

int BalancaNo(TArvBin *pNo) //Balances a node
{
    if (FB((*pNo)) > 1) {  //if the factor is > 1
        balancaEsq(&((*pNo))); //do the left balance
    }
    if (FB((*pNo)) < -1) {  //if the balancing factor is < -1
        balancaDir(&((*pNo))); //do the right balance
        }
    return 1;
}


void BalancaArvore(TArvBin *pNo) //Balance whole tree
{
    if (*pNo != NULL) {
        BalancaArvore(&(*pNo)->Esq);
        BalancaArvore(&(*pNo)->Dir);
        BalancaNo(pNo);
    }
}

int main()
{
    TArvBin Raiz;
    TItem x;
    //get a tree in parentheses notation, check if avl if its not balances the tree
    Raiz = Carrega();
    printf("%d\n", Altura(Raiz));
    if (!ArvoreAVL(Raiz)) {
        BalancaArvore(&Raiz);
        printf("%d\n", Altura(Raiz));
        Imprime(Raiz);
    }
    Libera(&Raiz);
    
    return 0;
}