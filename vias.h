/*  
*   TRABALHO 5  -   DC UEL MAPS
*   LUCCAS DE FREITAS FERREIRA  -   201200560446
*   CONTINUAÇÃO DO TRABALHO ANTERIOR IMPLEMENTANDO A ESTRUTURA GRAFO
*/
#ifndef _VIAS_
#define _VIAS_

#include "graph.h"
#include "tree.h"
#include "hash.h"

typedef struct Coordenada{
    float x;
    float y;
}Coordenada;

int graphSize(FILE *file);
int findArc(FILE *file);
void searchQuarter(Hash* hash, char* chave, Coordenada *cord);
void findPhone(Tree *root, char *fone, Hash *hash, Coordenada *cord);
void findCepFaceNum(Tree *root, Coordenada *cord, char *cep, char *face, char *num, Hash *hash);
void findName(Tree *root, Coordenada *cord, char* nome, Hash *hash);
void findTP(Tree *root, Coordenada *cord, char *tp, Hash *hash);
int findNearestPoint(Grafo *grafo, Coordenada *cord, Vertice *vertice);
void outSVG(Tree *root, Grafo *grafo, int origem, int destino, int nVertices, int *ant);
void calcPeso(Grafo *grafo, int *ant, int aux, char *consulta, int nArestas);
void findStreet(Grafo *grafo, Tree *root, char *nomerua, char *tp, int nArestas);
#endif