
//************************************************************************
// Red-Black Tree Insertion 
// Autor: Lucas de Morais Tramasso
// Matricula: 86859
// Data: 21/05/2015
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

typedef struct SNo *TArvBin;

typedef struct SNo {
    TItem Item;
    TArvBin Esq, Dir;
    int cor; //0 negro,1 rubro
} TNo;

int EhNegro(TArvBin No){
    return (No == NULL) || (No->cor == 0);
    
}
int EhRubro(TArvBin No){
    return (No != NULL) && (No ->cor == 1);
    
}
int AlturaNegra(TArvBin No)
{
    if(No == NULL){
        return 0;
    }
        int he=0,hd=0;
            he = AlturaNegra(No->Esq); //calcula a altura recursivamente
            hd = AlturaNegra(No->Dir);
            if(he >= hd){      //condiçao para retornar a maior altura
                if(EhNegro(No)){
                    return 1+he; //so incrementa a altura se o no for negro
                }else{
                    return he;
                }
            }else{
                if(EhNegro(No)){
                    return 1+hd; //so incrementa a altura se o no for negro
                }else{
                    return hd;
                }
        }
    }

TArvBin insereNo(TItem x){
    TArvBin novo = (TArvBin)malloc(sizeof(TNo));
    novo->Item = x;
    novo->Dir = NULL;
    novo->Esq = NULL;
    novo->cor = 1;
    return novo;
}

int ArvoreARN(TArvBin No)
{
    if(No == NULL){
        return 1; //arvore vazia eh por definicao uma rubro negra
    }
    ArvoreARN(No->Esq);
    ArvoreARN(No->Dir);
    if(AlturaNegra(No->Dir) == AlturaNegra(No->Esq)){
        if(EhRubro(No) && (EhRubro(No->Esq)||EhRubro(No->Dir)))
            return 0; // duplo vermelho
        return 1; //altura negra ok! sem duplo vermelho!
        }else{
        return 0; //altura negra falhou !
    }
}
void inverteCores(TArvBin No){
    if(No != NULL){
        No->cor = !No->cor;
    }
    
}
void TrocaCores(TArvBin No)
{   //troca a cor do pai e de seus dois filhos
    inverteCores(No);
    inverteCores(No->Dir);
    inverteCores(No->Esq);
}

void RotacaoDireita(TArvBin *pA)

{
    TArvBin pB = (*pA)->Esq;
    (*pA)->Esq = pB->Dir;
    pB->Dir = (*pA);
    (*pA) = pB;
}


void RotacaoEsquerda(TArvBin *pA)
{
    TArvBin pB = (*pA)->Dir;
    (*pA)->Dir = pB->Esq;
    pB->Esq = (*pA);
    (*pA) = pB;
}

void BalancaNo(TArvBin *pA, TArvBin *pB, TArvBin *pC)
{
    TArvBin pD;
    //balancaNo so deve ser executado de pA e pB sao rubros(duplo vermelho) e pC nao é null
    if((EhRubro(*pA)) && (EhRubro(*pB)) && ((pC) != NULL)){

        if((*pC)->Dir == *pA){
            pD = (*pC)->Esq; //se pa é filho direito o tio é filho esquerdo
        }else{
            pD = (*pC)->Dir;//se pa é filho esquerdo o tio é filho direito
        }
        
            //caso 1: tio rubro
                if(EhRubro(pD)){
                    TrocaCores(*pC);
                        return;
                }
            //caso 2a pai é filho esquerdo e o filho é filho direito
                if ((*pC)->Esq == *pA && (*pA)->Dir == *pB ) {
                        inverteCores(*pB);
                        inverteCores(*pC);
                        RotacaoEsquerda(pA);
                        RotacaoDireita(pC);
                    return;
                }
            //caso 3a pai e filho sao filhos esquerdos
                if ((*pC)->Esq == *pA && (*pA)->Esq == *pB) {
                        inverteCores(*pA);
                        inverteCores(*pC);
                        RotacaoDireita(pC);
                    return;
                }
            //caso 2b pai é filho direito e filho é filho esquerdo
                if((*pC)->Dir == *pA && (*pA)->Esq == *pB) {
                        inverteCores(*pB);
                        inverteCores(*pC);
                        RotacaoDireita(pA);
                        RotacaoEsquerda(pC);
                    return;
                }
            //caso 3b pai e filho sao filhos direitos
                if((*pC)->Dir == *pA && (*pA)->Dir == *pB){
                        inverteCores(*pA);
                        inverteCores(*pC);
                        RotacaoEsquerda(pC);
                    return;
                }
    }
}


TArvBin Inicializa()
{
    return NULL;
}



void insereRec(TArvBin *pNo,TArvBin *pPai, TItem x)
{
        if(*pNo == NULL){
            //Se o no atual for nulo
            *pNo = insereNo(x);
        }
        if(x.Chave == (*pNo)->Item.Chave){
            //se x for igual a chave do no atual
            return;
        }
        if(x.Chave > (*pNo)->Item.Chave){
            //se x for maior que a chave do no atual
            insereRec(&(*pNo)->Dir,pNo, x); //insere na direita com o no atual sendo o pai
            BalancaNo(pNo,&(*pNo)->Dir,pPai); //balanceamento
        }else{
            //se x for menor que a chave do no atual
            insereRec(&(*pNo)->Esq,pNo,x); //insere na esquerda com o no atual sendo o pai
            BalancaNo(pNo,&(*pNo)->Esq,pPai); //balanceamento
        }
}
void Insere(TArvBin *pNo, TItem x){ //funcao para chamar a inserçao recursiva
    insereRec(pNo,NULL, x);
    (*pNo)->cor = 0; //forca a raiz a ser negra
}

void Carrega(TArvBin *pNo)
{
    int i, n;
    TItem x;
    
    scanf("%d", &n);
    for (i = 0; i < n ; i++) {
        scanf("%d", &x.Chave);
        Insere(pNo, x);
    }
}

void Libera(TArvBin *pNo)
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

void Imprime(TArvBin No)
{
    if (No != NULL) {
        if (EhNegro(No))
            printf("(N%d", No->Item.Chave);
        else
            printf("(R%d", No->Item.Chave);
        Imprime(No->Esq);
        Imprime(No->Dir);
        printf(")");
    }
    else
        printf("()");
}

int main()
{
    TArvBin Raiz;
    Raiz = Inicializa();
    Carrega(&Raiz);
    if (ArvoreARN(Raiz)) {
        printf("%d\n", AlturaNegra(Raiz));
        Imprime(Raiz);
    }
    Libera(&Raiz);
    
    return 0;
}