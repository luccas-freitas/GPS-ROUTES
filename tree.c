/*  
*   TRABALHO 4  -   MAPEAMENTO DA CIDADE DE BITNÓPOLIS
*   LUCCAS DE FREITAS FERREIRA  -   LEONARDO FIRMINO DE SOUZA
*   IMPLEMENTAÇÃO DE TABELA HASH USANDO LISTA ENCADEADA E DUPLOHASHING
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

//IMPRIMIR INFORMAÇOES CONTIDAS NA ARVORE
void printInfo(Tree *root){ //RETANGULO COMUM
    if((*root)->info.type == 0){
        printf("tipo: %d RETANGULO\n",(*root)->info.type);  
        printf("(x,y): %f, %f\n",(*root)->info.x, (*root)->info.y); 
        printf("(h,l): %f, %f\n",(*root)->info.h, (*root)->info.l);
        printf("COR: %s\n",(*root)->info.cor);
    }
    else if((*root)->info.type == 1){    //QUADRA
        printf("tipo: %d QUADRA\n",(*root)->info.type);  
        printf("(x,y): %f, %f\n",(*root)->info.x, (*root)->info.y); 
        printf("(h,l): %f, %f\n",(*root)->info.h, (*root)->info.l);
        printf("CEP: %s\n",(*root)->info.cep);
    }
    else if((*root)->info.type == 2){    //CASA
        printf("tipo: %d CASA\n",(*root)->info.type);  
        printf("CEP: %s\n",(*root)->info.cep); 
        printf("FACE: %s\n",(*root)->info.face); 
        printf("NUM: %s\n",(*root)->info.num);
        printf("NOME: %s\n",(*root)->info.nome);
        printf("TEL: %s\n",(*root)->info.tel);
    }
    else if((*root)->info.type == 3){    //COMERCIO
        printf("tipo: %d COMERCIO\n",(*root)->info.type);  
        printf("CEP: %s\n",(*root)->info.cep); 
        printf("FACE: %s\n",(*root)->info.face); 
        printf("NUM: %s\n",(*root)->info.num);
        printf("TP: %s\n",(*root)->info.tp);
        printf("NOME: %s\n",(*root)->info.nome);
        printf("TEL: %s\n",(*root)->info.tel);
    }
    else if((*root)->info.type == 4){    //HIDRANTE
        printf("tipo: %d HIDRANTE\n",(*root)->info.type);  
        printf("ID: %s\n",(*root)->info.nome);
        printf("(x,y): %f, %f\n",(*root)->info.x, (*root)->info.y); 
    }    
    else if((*root)->info.type == 5){    //SEMAFORO
        printf("tipo: %d SEMAFORO\n",(*root)->info.type);  
        printf("ID: %s\n",(*root)->info.nome);
        printf("(x,y): %f, %f\n",(*root)->info.x, (*root)->info.y);  
    }    
    else if((*root)->info.type == 6){    //RADIO-BASE
        printf("tipo: %d RADIO-BASE\n",(*root)->info.type);  
        printf("ID: %s\n",(*root)->info.nome);
        printf("(x,y): %f, %f\n",(*root)->info.x, (*root)->info.y);  
    }
    printf("\n");
}

//COMPARAR RETANGULO A PARTIR DE SUA POSIÇAO NO PLANO CARTESIANO
int compare(Retangulo a, Retangulo b){
    if(a.x > b.x)
        return 1;
    if(a.x == b.x && a.y > b.y)
        return 1;
    if(a.x == b.x && a.y == b.y)
        return -1;
    return 0;
}

//CRIAR ARVORE
Tree* createTree(){
    Tree* root = (Tree*) malloc(sizeof(Tree));
    if(root != NULL)
        *root = NULL;
    return root;
}

//LIBERAR NÓ EM CADA REMOÇÃO
void freeNode(Node* no){
    if(no == NULL)
        return;
    freeNode(no->esq);
    freeNode(no->dir);
    free(no);
    no = NULL;
}

//LIBERAR ÁRVORE AO FIM DE CADA APLICAÇÃO
void freeTree(Tree* root){
    if(root == NULL)
        return;
    freeNode(*root);//libera cada nó
    free(root);//libera a root
}

//INSERIR NÓ DE FORMATO esquerda < (X,Y) < direita
int insertNode(Tree* root, Retangulo valor){
    if(root == NULL)
        return 0;
    Node* novo;
    novo = (Node*) malloc(sizeof(Node));
    if(novo == NULL)
        return 0;
    novo->info.x = valor.x;
    novo->info.y = valor.y;
    novo->info.h = valor.h;
    novo->info.l = valor.l;

    novo->info.cor = malloc(sizeof(char) * 50);
    strcpy(novo->info.cor, valor.cor);

    novo->info.num = malloc(sizeof(char) * 50);
    strcpy(novo->info.num, valor.num);

    novo->info.face = malloc(sizeof(char) * 50);
    strcpy(novo->info.face, valor.face);

    novo->info.cep = malloc(sizeof(char) * 50);
    strcpy(novo->info.cep, valor.cep);

    novo->info.nome = malloc(sizeof(char) * 50);
    strcpy(novo->info.nome, valor.nome);

    novo->info.tel = malloc(sizeof(char) * 50);
    strcpy(novo->info.tel, valor.tel);

    novo->info.tp = malloc(sizeof(char) * 50);
    strcpy(novo->info.tp, valor.tp);

    novo->info.type = valor.type;

    novo->dir = NULL;
    novo->esq = NULL;
    if(*root == NULL)
        *root = novo;
    else{
        Node* atual = *root;
        Node* ant = NULL;
        while(atual != NULL){
            ant = atual;
            if(compare(valor, atual->info) == -1){   //compara coordenada (x,y)
                valor.x += 1.432;
                valor.y += 0.297;
                //free(novo);
                //return 0;//elemento já existe
            }

            if(compare(valor, atual->info) == 1) //compara coordenada (x,y)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        if(compare(valor, ant->info) == 1)   //compara coordenada (x,y)
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return 1;
}

//SE ENCONTRADO, REMOVE O NÓ EXISTENTE
Node* remove_atual(Node* atual) {
    Node *no1, *no2;
    if(atual->esq == NULL){
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->esq;
    while(no2->dir != NULL){
        no1 = no2;
        no2 = no2->dir;
    }
    if(no1 != atual){
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
}

//RECURSÃO DA FUNÇÃO AUXILIAR REMOVE_ATUAL PARA PERCORRER ARVORE
int removeNode(Tree *root, Retangulo valor){
    if(root == NULL)
        return 0;
    Node* ant = NULL;
    Node* atual = *root;
    while(atual != NULL){
        if(compare(valor, atual->info) == -1){ //compara coordenada (x,y)
            if(atual == *root)
                *root = remove_atual(atual);
            else{
                if(ant->dir == atual)
                    ant->dir = remove_atual(atual);
                else
                    ant->esq = remove_atual(atual);
            }
            return 1;
        }
        ant = atual;
        if(compare(valor, atual->info) == 1) //compara coordenada (x,y)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

//VERIFICAR SE ÁRVORE ESTÁ VAZIA
int isEmpty(Tree *root){
    if(root == NULL)
        return 1;
    if(*root == NULL)
        return 1;
    return 0;
}

//RETORNAR NUMERO DE NÓS DA ÁRVORE
int getSize(Tree *root){
    if (root == NULL)
        return 0;
    if (*root == NULL)
        return 0;
    int alt_esq = getSize(&((*root)->esq));
    int alt_dir = getSize(&((*root)->dir));
    return(alt_esq + alt_dir + 1);
}

//RETORNAR PROFUNDIDADE DA ÁRVORE
int height(Tree *root){
    if (root == NULL)
        return 0;
    if (*root == NULL)
        return 0;
    int alt_esq = height(&((*root)->esq));
    int alt_dir = height(&((*root)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

//FUNÇÃO LÓGICA PARA VERIFICAR SE RETANGULO EXISTE
int check(Tree *root, Retangulo valor){
    if(root == NULL)
        return 0;
    Node* atual = *root;
    while(atual != NULL){
        if(compare(valor, atual->info) == -1){ //compara coordenada (x,y)
            return 1;
        }
        if(compare(valor, atual->info) == 1) //compara coordenada (x,y)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

//IMPRESSAO DOS ELEMENTOS DA ARVORE EM PRÉ-ORDEM
void preOrder(Tree *root){
    if(root == NULL)
        return;
    if(*root != NULL){
        printInfo(root);
        preOrder(&((*root)->esq));
        preOrder(&((*root)->dir));
    }
}

//IMPRESSAO DOS ELEMENTOS DA ARVORE EM ORDEM
void inOrder(Tree *root){
    if(root == NULL)
        return;
    if(*root != NULL){
        inOrder(&((*root)->esq));
        printInfo(root);
        inOrder(&((*root)->dir));
    }
}

//IMPRESSAO DOS ELEMENTOS DA ARVORE EM PÓS-ORDEM
void posOrder(Tree *root){
    if(root == NULL)
        return;
    if(*root != NULL){
        posOrder(&((*root)->esq));
        posOrder(&((*root)->dir));
        printInfo(root);
    }
}