/*  
*   TRABALHO 5  -   DC UEL MAPS
*   LUCCAS DE FREITAS FERREIRA  -   201200560446
*   CONTINUAÇÃO DO TRABALHO ANTERIOR IMPLEMENTANDO A ESTRUTURA GRAFO
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "vias.h"
#include "tree.h"
#include "retangulos.h"
#include "hash.h"
#include "graph.h"
#include "menu.h"
#define MAX 500

char fileName[MAX];
char dirSaida[MAX];
int main(int argc, char* argv[]){
    Tree* raiz = createTree();
    Hash* hash = createHash(8797);
    int i;
	char fileName2[MAX];
    for(i=1; i<argc; i++){
        if(strcmp("-id\0", argv[i]) == 0){// comando para imprimir os dados dos alunos 
            printf("\nLUCCAS DE FREITAS FERREIRA\t-\t201200560446\n"); 
        }else if(strcmp("-f\0", argv[i]) == 0){// nome do arquivo de teste .OPS, pode incluir o caminho
            strcpy(fileName, argv[++i]); 
        }else if(strcmp("-g\0", argv[i]) == 0){// nome do arquivo de teste .VIAS, pode incluir o caminho
            strcpy(fileName2, argv[++i]); 
        }else if(strcmp("-o\0", argv[i]) == 0){// diretorio do arquivo de saida
            strcpy(dirSaida, argv[++i]);
        }else printf("\nErro.");
    }

    //PROCESSAMENTO DO ARQUIVO.OPS E ARQUIVO.VIAS
    FILE* file = fopen(fileName,"r");   processaNome();
    FILE* file2 = fopen(fileName2,"r");
    int nVertices = graphSize(file2);   rewind(file2);
    int nArestas = findArc(file2);  rewind(file2);

    Grafo* grafo = createGraph(nVertices, nArestas, 3);	//até 4 arestas em cada vértice
    Menu2(file2, grafo, nVertices); //ADICIONAR RUAS (GRAFO)
    Menu(file, raiz, hash, grafo, nVertices, nArestas); //ADICIONAR CIDADE (ARVORE E HASH)

    fclose(file);
    fclose(file2);
    freeGraph(grafo);
    freeHash(hash);
    freeTree(raiz);

    printf("log de resultados gerado na pasta do programa.\n");
    printf("(Confira output.txt)\n");
    return 0;
}