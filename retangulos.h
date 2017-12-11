/*  
*   TRABALHO 4  -   MAPEAMENTO DA CIDADE DE BITNÓPOLIS
*   LUCCAS DE FREITAS FERREIRA  -   LEONARDO FIRMINO DE SOUZA
*   IMPLEMENTAÇÃO DE TABELA HASH USANDO LISTA ENCADEADA E DUPLOHASHING
*/

#ifndef _TREE__
#define _TREE__

//FGETS MODIFICADA PARA CONCATENAR COM \0
char *fgets2(char* str, int size, FILE* stream);
//RECURSAO PARA PERCORRER ARVORE E GERAR SVG
void getInfo(Tree *root, FILE *file);
//FUNÇAO DE PROCESSAMENTO DO NOME DO ARQUIVO
void processaNome();
//GERAR ARQUIVO DE SAIDA SVG
void makeSVG(Tree* root, char *sufix);
//AREA DE BUSCA PARA REMOÇÃO
int removeRetangulo(Tree *root, Retangulo retangulo, FILE *file);
//AREA DE BUSCA PARA ALTERAR COR
int changeColor(Tree *root, char *cor1, char *cor2, Retangulo retangulo, int num, FILE *file);
//ALTERAR COR DE TODOS OS RETANGULOS
int changeAll(Tree *root, char *cor1, char *cor2, int num);
//IMPRIME OS MORADORES DE UMA QUADRA
void procuraMoradores(Hash* hash, char* chave, FILE *file);
//IMPRIME OS MORADORES DE UMA DADA REGIAO
void moradoresRegiao(Tree *root, Hash *hash, Retangulo retangulo, FILE *file);
//IMPRIME QUAIS SAO AS QUADRAS QUE TEM UM ESTABELECIMENTO DO TIPO TP DENTRO DE UMA REGIAO
void procuraQuadra(Tree *root, char *chave, Retangulo retangulo, FILE *file);
//FUNCAO RECURSIVA AUXILIAR DA PROCURAQUADRA
void comercioQuadra(Tree *root, Hash* hash, Retangulo retangulo, char *tp, FILE *file);
//IMPRIME OS DADOS DO ESTABELECIMENTO DO TIPO TP DENTRO DE UMA REGIAO
void procuraComercio(Hash* hash, char* chave, char *tp);
//FUNCAO RECURSIVA AUXILIAR DA PROCURACOMERCIO
void comercioRegiao(Tree *root, Hash* hash, Retangulo retangulo, char *tp, FILE *file);
//FUNCAO PROCURA COMERCIO SEM REGIAO DELIMITADA
void comerciosTotal(Tree *root, char *tp, FILE *file);
//QUAIS HIDRANTES EXISTEM DENTRO DA REGIAO
void hidrante(Tree *root, Retangulo retangulo, FILE *file);
//QUAIS SEMAFOROS EXISTEM DENTRO DA REGIAO
void semaforo(Tree *root, Retangulo retangulo, FILE *file);
//HIDRANTES EXISTENTES DENTRO DE UMA MARGEM LARG DAS FACES
void hidranteQuadra(Tree *root, Retangulo retangulo, FILE *file);
//QUAIS QUADRAS TEM UMA TORRE DE CELULAR
void quadraTorre(Tree *root, FILE *file);
//FUNCAO AUXILIAR DA BUSCATORREAREA
void buscaTorreArea(Tree *root, Retangulo retangulo, FILE *file);

#endif