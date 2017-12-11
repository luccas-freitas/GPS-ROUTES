/*  
*   TRABALHO 4  -   MAPEAMENTO DA CIDADE DE BITNÓPOLIS
*   LUCCAS DE FREITAS FERREIRA  -   LEONARDO FIRMINO DE SOUZA
*   IMPLEMENTAÇÃO DE TABELA HASH USANDO LISTA ENCADEADA E DUPLOHASHING
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sd.h"
#include "tree.h"
#include "hash.h" //inclui os Protótipos

//HASH USANDO DUPLO HASHING
Hash* createHash(int size){
    Hash* hash = (Hash*) malloc(sizeof(Hash));
    if(hash != NULL){
        int i;
        hash->size = size;
        hash->itens = (Retangulo**) malloc(size * sizeof(Retangulo*));
        if(hash->itens == NULL){
            free(hash);
            return NULL;
        }
        hash->qtd = 0;
        for(i=0; i < hash->size; i++)
            hash->itens[i] = NULL;
    }
    return hash;
}

int getQtd(Hash *hash){
    return hash->qtd;
}

int valueString(char *str){
    int i, valor = 7;
    int tam = strlen(str);
    for(i=0; i < tam; i++)
        valor = 31 * valor + (int) str[i];
    return (valor & 0x7FFFFFFF);
}

int hashFunction1(int chave, int size){
    double A = 0.6180339887; // constante: 0 < A < 1
    double val = chave * A;
    val = val - (int) val;
    return (int) (size * val);
}

int hashFunction2(int chave, int size){
    int num_bits = 10;
    int parte1 = chave >> num_bits;
    int parte2 = chave & (size-1);
    return (parte1 ^ parte2);
}

int duploHash(int H1, int chave, int i, int size){
    int H2 = hashFunction2(chave, size) + 1;
    return ((H1 + i*H2) & 0x7FFFFFFF) % size;
}

int insertHash(Hash* hash, Retangulo retangulos){
    if(hash == NULL || hash->qtd == hash->size)
        return 0;

    int i, pos, newPos;
    int chave = valueString(retangulos.cep);
    pos = hashFunction1(chave, hash->size);    //H1
    for(i=0; i < hash->size; i++){
        newPos = duploHash(pos,chave,i,hash->size);
        if(hash->itens[newPos] == NULL){
            Retangulo* novo;
            novo = (Retangulo*) malloc(sizeof(Retangulo));
            if(novo == NULL)
                return 0;
            //*novo = retangulos;
                novo->x = retangulos.x;
                novo->y = retangulos.y;
                novo->h = retangulos.h;
                novo->l = retangulos.l;

                novo->cor = malloc(sizeof(char) * 50);
                strcpy(novo->cor, retangulos.cor);

                novo->num = malloc(sizeof(char) * 50);
                strcpy(novo->num, retangulos.num);

                novo->face = malloc(sizeof(char) * 50);
                strcpy(novo->face, retangulos.face);

                novo->cep = malloc(sizeof(char) * 50);
                strcpy(novo->cep, retangulos.cep);

                novo->nome = malloc(sizeof(char) * 50);
                strcpy(novo->nome, retangulos.nome);

                novo->tel = malloc(sizeof(char) * 50);
                strcpy(novo->tel, retangulos.tel);

                novo->tp = malloc(sizeof(char) * 50);
                strcpy(novo->tp, retangulos.tp);

                novo->type = retangulos.type;

            hash->itens[newPos] = novo;
            hash->qtd++;
            return 1;
        }
    }
    return 0;
}

int searchHash(Hash* hash, char* chave, Retangulo* retangulos){
    if(hash == NULL)
        return 0;

    int i, pos, newPos;
    int nome = valueString(chave);
    pos = hashFunction1(nome,hash->size);
    for(i=0; i < hash->size; i++){
        newPos = duploHash(pos,nome,i,hash->size);
        if(hash->itens[newPos] == NULL)
            return 0;

        if(valueString(hash->itens[newPos]->cep) == nome){
            *retangulos = *(hash->itens[newPos]);
            return 1;
        }
    }
    return 0;
}

void freeHash(Hash* hash){
    if(hash != NULL){
        int i;
        for(i=0; i < hash->size; i++){
            if(hash->itens[i] != NULL)
                free(hash->itens[i]);
        }
        free(hash->itens);
        free(hash);
    }
}

//HASH USANDO LISTA ENCADEADA

hashList* createHashList(int size){
    hashList* hash = (hashList*) malloc(sizeof(hashList));
    if(hash != NULL){
        hash->size = size;
        hash->itens = (void**) malloc(size * sizeof(Retangulo *));

        //tratamento de erro na alocação
        if(hash->itens == NULL){
            free(hash);
            return NULL;
        }

        int i;
        hash->qtd = 0;
        for(i=0; i < hash->size; i++)
            hash->itens[i] = NULL;
    }
    return hash;
}

int insertHashList(hashList* hash, void *info, char *chave){
    if(hash == NULL || hash->qtd == hash->size)
        return 0;
    
    int posAux, pos;
    posAux = valueString(chave);
    pos = hashFunction1(posAux, hash->size);
                                                        
    List list;
    if(hash->itens[pos] == NULL){
        list = createList();

        insertList(list, info);
    }
    else{
      list = hash->itens[pos];
      insertList(list, info);
    }

    hash->itens[pos] = (List) list;
    hash->qtd++;

    return 1;
}

void *searchHashList(hashList* hash, char *chave){
    if(hash == NULL)
        return 0;
    
    int posAux, pos;
    posAux = valueString(chave);
    pos = hashFunction1(posAux, hash->size);
    
    if(hash->itens[pos] == NULL)
        return 0;
                
    return (List) hash->itens[pos];
}

void freeHashList(hashList* hash){
    if(hash != NULL){
        int i;
        for(i=0; i<hash->size; i++){
            if(hash->itens[i] != NULL)
                free(hash->itens[i]);
        }
        free(hash->itens);
        free(hash);
    }
}


