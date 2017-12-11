#ifndef _GRAPH_
#define _GRAPH_

typedef struct Aresta{
	char *i;
	char *j;
	char *ldir;
	char *lesq;
	float cmp;
	int tempo;
	char *nome;
} Aresta;

typedef struct Vertice{
	char *id;
	float x;
	float y;
} Vertice;

typedef struct Grafo{
    int size;
    int grau_max;
    int** positionArc;
    Vertice* vertices;
    Aresta* arestas;
    int* grau;
} Grafo;

Grafo* createGraph(int nVertices, int nArestas, int grau_max);
void freeGraph(Grafo* grafo);
int insertVertex(Grafo* grafo, Vertice vertice, int pos);
int insertArc(Grafo* grafo, int orig, int dest, Aresta aresta, int pos);
void dijkstra(Grafo *grafo, int ini, int *antecessor, int *distancia);

#endif