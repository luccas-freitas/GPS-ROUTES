/*  
*   TRABALHO 4  -   MAPEAMENTO DA CIDADE DE BITNÓPOLIS
*   LUCCAS DE FREITAS FERREIRA  -   LEONARDO FIRMINO DE SOUZA
*   IMPLEMENTAÇÃO DE TABELA HASH USANDO LISTA ENCADEADA E DUPLOHASHING
*/

#include <stdio.h>
#include <stdlib.h>
#include "sd.h"

struct No{
    No prox;
    Item info;
};

struct List{
    No ini;
    No fim;
    int length;

};


List createList(){
     List list = malloc(sizeof(List));
     list->ini = NULL;
     list->fim = NULL;
     list->length=0;

     return list;
}

int length(List list){
    return list->length;
}

No insertList(List list, Item info){
    No node = (No) malloc(sizeof(struct No)); //Aloca espaco para o novo No.
    No anterior = getLast(list); //Salva seu antecessor.

    node->info = (Item)info;    //Salva a info.
    node->prox = NULL;  //Seta seu sucessor como nulo.
    
    if(length(list)) //Se a lista estiver vazia, insere na primeira posicao.
        list->ini = node; 

    if(anterior != NULL) //Se houver anterior, o ponteiro "prox" do anterior aponta para o novo No.
        anterior->prox = node;

    list->fim = node; //Caso nao esteja vazia, insere na ultima posicao.
    list->length++; //Aumenta o tamanho da lista.
    
    return node;    //Retorna o novo No.
}

void removeElemento(List list, No node){
    No aux = node; //Auxiliar salva o elemento a ser removido.
    No anterior = getPrevious(list, node); //Auxiliar salva o antecessor a ser removido.
    No proximo = getNext(list, node); //Auxiliar salva o sucessor a ser removido.
    
    if(anterior != NULL){ //Se diferente de vazio, seu ponteiro "prox" aponta pro No proximo.
        anterior->prox = proximo;     
    }else{ //Se for vazio, ele sera o primeiro elemento.
        list->ini = proximo;
    }

    if(proximo == NULL){
        list->fim = anterior;
    }

    list->length--; //Diminui o tamanho da lista.
    free(node); //Remove elemento.
}

Item get(List list, No node){
    No aux = NULL; //No auxiliar vazio.
    for(aux = getFirst(list); aux != NULL; aux = getNext(list, aux)){//Enquanto No for diferente de nulo
        if(aux == node) //Se o no for igual ao procurado
            return aux->info; //Retorne a info do no.
    }
}

No insertBefore(List list, No node, Item info){
    No anterior = getPrevious(list, node); //No auxiliar recebe o anterior da posicao P.
    No aux  = malloc(sizeof(No)); //Aloca espaco para o novo No.

    if(anterior != NULL) //Se o anterior for nao-nulo.
        anterior->prox = aux;  //O ponteiro "prox" do No anterior recebe o novo No.
    
    aux->prox = node; //O ponteiro "prox" do novo No recebe o No da posicao P.
    aux->info = (Item)info; //Novo No recebe a info.

    list->length++; //Aumenta o tamanho da lista.  
    return aux;    //Retorna o novo No.
}

No insertAfter(List list, No node, Item info){
    No proximo = getNext(list,node); //Auxiliar proximo recebe o sucessor de P.
    No aux = malloc(sizeof(No)); //Aloca espaco para o novo No.

    node->prox = aux; //O ponteiro "prox" de P recebe o novo No.
    aux->prox = proximo; //O ponteiro "prox" do novo No recebe seu sucessor.
    aux->info = (Item)info;    //Novo No recebe a info.

    list->length++; //Aumenta o tamanho da lista.
    return aux;    //Retorna o novo No.
}

No getFirst(List list){
    return list->ini;   //Retorna o primeiro elemento.
}

No getNext(List list, No node){
    No aux = NULL;
    for(aux = getFirst(list); aux != NULL; aux = aux->prox) //Enquanto a posicao for diferente de nulo
        if(aux == node)  //Se a posicao procurada for igual a aux
            return aux->prox; //Retorna seu sucessor
}

No getLast(List list){
    return list->fim;   //Retorna o ultimo elemento.
}

No getPrevious(List list, No node){
    No aux = NULL;
    for(aux = getFirst(list); aux != NULL; aux = aux->prox) //Enquanto a posicao for diferente de nulo
        if(aux == getPrevious(list,node))  //Se a posicao procurada for igual a aux
            return getPrevious(list,node);  //Retorna seu antecessor
}