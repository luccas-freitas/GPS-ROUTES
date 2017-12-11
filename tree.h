/*  
*   TRABALHO 4  -   MAPEAMENTO DA CIDADE DE BITNÓPOLIS
*   LUCCAS DE FREITAS FERREIRA  -   LEONARDO FIRMINO DE SOUZA
*   IMPLEMENTAÇÃO DE TABELA HASH USANDO LISTA ENCADEADA E DUPLOHASHING
*/

#ifndef _TREE__
#define _TREE__

//INFO ARMAZENADA NA ARVORE
typedef struct Retangulo{
    float x;    //ponto de ancoragem x
    float y;    //ponto de ancoragem y
    float h;    //altura
    float l;    //largura
    char *cor;  //cor

    //VARIAVEIS ADICIONAIS TRABALHO - 4 (HASH)
    int type; 
    /*	tipo = 0 (retangulo trabalho 3)
        tipo = 1 (quadra)
        tipo = 2 (casa)
        tipo = 3 (comercio)
        tipo = 4 (hidrante)
        tipo = 5 (semaforo)
        tipo = 6 (radio-base)   
    */
    char *num;
    char *face;
    char *cep;
    char *nome; //id
    char *tel;	//f
    char *tp;
}Retangulo;

typedef struct Node{
    Retangulo info;
    struct Node *esq;
    struct Node *dir;
}Node;

typedef struct Node* Tree;

int compare(Retangulo a, Retangulo b);
Tree* createTree();
void freeTree(Tree *root);
int insertNode(Tree* root, Retangulo valor);
int removeNode(Tree *root, Retangulo valor);
int isEmpty(Tree *root);
int height(Tree *root);
int getSize(Tree *root);
int check(Tree *root, Retangulo valor);
void preOrder(Tree *root);
void inOrder(Tree *root);
void posOrder(Tree *root);

#endif