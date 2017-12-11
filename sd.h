/*  
*   TRABALHO 4  -   MAPEAMENTO DA CIDADE DE BITNÓPOLIS
*   LUCCAS DE FREITAS FERREIRA  -   LEONARDO FIRMINO DE SOUZA
*   IMPLEMENTAÇÃO DE TABELA HASH USANDO LISTA ENCADEADA E DUPLOHASHING
*/

#ifndef _SIMPLES_DINAMICA_
#define _SIMPLES_DINAMICA_
             
typedef struct No* No;
typedef struct List* List;
typedef void* Item;

List createList();

int length(List);

No insertList(List, Item);

void removeElemento(List, No);

Item get(List, No);

No insertBefore(List, No, Item);

No insertAfter(List, No, Item);

No getFirst(List);

No getNext(List, No);

No getLast(List);

No getPrevious(List, No);

#endif
