/*  
*   TRABALHO 4  -   MAPEAMENTO DA CIDADE DE BITNÓPOLIS
*   LUCCAS DE FREITAS FERREIRA  -   LEONARDO FIRMINO DE SOUZA
*   IMPLEMENTAÇÃO DE TABELA HASH USANDO LISTA ENCADEADA E DUPLOHASHING
*/

#ifndef _HASH_
#define _HASH_

//DUPLO-HASHING
typedef struct Hash{
    int qtd, size;
    Retangulo **itens;
} Hash;

Hash* createHash(int TABLE_SIZE);
int getQtd(Hash *hash);
int valueString(char *str);
int hashFunction1(int chave, int TABLE_SIZE);
int hashFunction2(int chave, int TABLE_SIZE);
int duploHashing(int pos, int chave, int i, int TABLE_SIZE);
int insertHash(Hash* hash, Retangulo retangulos);
int searchHash(Hash* hash, char* chave, Retangulo* retangulos);
void freeHash(Hash* hash);

//HASH USANDO LISTA ENCADEADA
typedef struct hashList{
    int qtd, size;
    void **itens;
} hashList;

hashList* createHashList(int TABLE_SIZE);
int insertHashList(hashList* hash, void *info, char *chave);
void *searchHashList(hashList* hash, char *chave);
void freeHashList(hashList* hash);

#endif