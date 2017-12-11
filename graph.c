#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

Grafo* createGraph(int nVertices, int nArestas, int grau_max){
    Grafo *grafo;
    grafo = (Grafo*) malloc(sizeof(Grafo));
    int i;
    if(grafo != NULL){
        grafo->size = nVertices;
        grafo->grau_max = grau_max;
        grafo->grau = (int*) calloc(nVertices,sizeof(int));

        grafo->positionArc = (int**) malloc(nVertices * sizeof(int*));
        for(i=0; i <= nVertices; i++)
            grafo->positionArc[i] = (int*) malloc(grau_max * sizeof(int));

        grafo->arestas = (Aresta*) malloc(sizeof(Aresta) * nArestas);
		grafo->vertices = (Vertice*) malloc(sizeof(Vertice) * nVertices);
	}
    return grafo;
}

void freeGraph(Grafo* grafo){
	int i;
    if(grafo != NULL){
		for(i=0; i <= grafo->size; i++)
            free(grafo->positionArc[i]);
        free(grafo->arestas);
		free(grafo->vertices);
        free(grafo->grau);
        free(grafo);
    }
}

int insertVertex(Grafo* grafo, Vertice vertice, int pos){
    if(grafo == NULL)
        return 0;
    grafo->vertices[pos].id = (char*) malloc(sizeof(char)*100);
    strcpy(grafo->vertices[pos].id, vertice.id);
    grafo->vertices[pos].x = vertice.x;
    grafo->vertices[pos].y = vertice.y;

    return 1;
}

int insertArc(Grafo* grafo, int orig, int dest, Aresta aresta, int pos){
    if(grafo == NULL)
        return 0;
    grafo->positionArc[orig][grafo->grau[orig]] = dest;
    
    grafo->arestas[pos].i = (char*) malloc(sizeof(char)*100);
    strcpy(grafo->arestas[pos].i, aresta.i);
    
    grafo->arestas[pos].j = (char*) malloc(sizeof(char)*100);
    strcpy(grafo->arestas[pos].j, aresta.j);
    
    grafo->arestas[pos].ldir = (char*) malloc(sizeof(char)*100);
    strcpy(grafo->arestas[pos].ldir, aresta.ldir);
    
    grafo->arestas[pos].lesq = (char*) malloc(sizeof(char)*100);
    strcpy(grafo->arestas[pos].lesq, aresta.lesq);
    
    grafo->arestas[pos].cmp = aresta.cmp;
    
    grafo->arestas[pos].tempo = aresta.tempo;
    
    grafo->arestas[pos].nome = (char*) malloc(sizeof(char)*100);
    strcpy(grafo->arestas[pos].nome, aresta.nome);
    
    grafo->grau[orig]++;

    return 1;
}

int searchMinor(int *dist, int *visitado, int size){
    int i, menor = -1, primeiro = 1;
    for(i=0; i < size; i++){
        if(dist[i] >= 0 && visitado[i] == 0){
            if(primeiro){
                menor = i;
                primeiro = 0;
            }else{
                if(dist[menor] > dist[i])
                    menor = i;
            }
        }
    }
    return menor;
}

void dijkstra(Grafo *grafo, int ini, int *ant, int *dist){
    int i, cont, size, ind, *visitado, u;
    cont = size = grafo->size;

    visitado = (int*) malloc(size *sizeof(int));
    for(i=0; i < size; i++){
        ant[i] = -1;
        dist[i] = -1;
        visitado[i] = 0;
    }

    dist[ini] = 0;
    while(cont > 0){
        u = searchMinor(dist, visitado, size);
        if(u == -1)
            break;

        visitado[u] = 1;
        cont--;

        for(i=0; i < grafo->grau[u]; i++){
            ind = grafo->positionArc[u][i];
            if(dist[ind] < 0){
                dist[ind] = dist[u] + 1;
                ant[ind] = u;
            }else{
                if(dist[ind] > dist[u] + 1){
                    dist[ind] = dist[u] + 1;
                    ant[ind] = u;
                }
            }
        }
    }
    free(visitado);
}
