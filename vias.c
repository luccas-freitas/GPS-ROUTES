/*  
*   TRABALHO 5  -   DC UEL MAPS
*   LUCCAS DE FREITAS FERREIRA  -   201200560446
*   CONTINUAÇÃO DO TRABALHO ANTERIOR IMPLEMENTANDO A ESTRUTURA GRAFO
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "tree.h"
#include "hash.h"
#include "vias.h"
#define MAX 500

//DEFINIR NUMERO DE VERTICES DO ARQUIVO DE ENTRADA
int graphSize(FILE *outFile){
    char getString[MAX], *func;
    int total = 0;
    if(outFile){
        while(!feof(outFile)){
            fgets2(getString, MAX, outFile);
            if(!strcmp(getString,"#"))
                break;
            func = strtok(getString," ");
            if(!strcmp(func,"v"))
                total++;
        }    
    }else{
        printf("\nErro ao abrir o arquivo .VIAS\n");
    }
    return total;
}
//DEFINIR NUMERO DE ARESTAS DO ARQUIVO DE ENTRADA
int findArc(FILE *outFile){
    char getString[MAX], *func;
    int total = 0;
    if(outFile){
        while(!feof(outFile)){
            fgets2(getString, MAX, outFile);
            if(!strcmp(getString,"#"))
                break;
            func = strtok(getString," ");
            if(!strcmp(func,"e"))
                total++;
        }    
    }else{
        printf("\nErro ao abrir o arquivo .VIAS\n");
    }
    return total;
}
//PROCURA QUADRA USANDO HASH
void searchQuarter(Hash* hash, char* chave, Coordenada *cord){
    int i, pos, newPos; 
    if(hash == NULL)
        return;

    int nome = valueString(chave);
    pos = hashFunction1(nome, hash->size);
    for(i=0; i < hash->size; i++){
        newPos = duploHash(pos, nome, i, hash->size);
        if(hash->itens[newPos] == NULL)
            return;
        else if(valueString(hash->itens[newPos]->cep) == nome && hash->itens[newPos]->type == 1){
            cord->x = hash->itens[newPos]->x;
            cord->y = hash->itens[newPos]->y; 
        }
    }
}
//ENCONTRAR CASA OU COMERCIO PELO 'FONE'
void findPhone(Tree *root, char *fone, Hash *hash, Coordenada *cord){
    if(root == NULL)
        return;
    
    if(*root != NULL){
        Retangulo aux = (*root)->info;
        if((aux.type == 2 || aux.type == 3) && !strcmp(aux.tel, fone))
            searchQuarter(hash, aux.cep, cord);
        findPhone(&((*root)->esq), fone, hash, cord);
        findPhone(&((*root)->dir), fone, hash, cord);
    }
}
//ENCONTRAR CASA OU COMERCIO POR 'CEP/FACE/NUM'
void findCepFaceNum(Tree *root, Coordenada *cord, char *cep, char *face, char *num, Hash *hash){
    if(root == NULL)
        return;
    
    if(*root != NULL){
        Retangulo aux = (*root)->info;
        if((aux.type == 2 || aux.type == 3) && !strcmp(aux.cep, cep) && !strcmp(aux.face, face) && !strcmp(aux.num, num))
            searchQuarter(hash, aux.cep, cord);
        findCepFaceNum(&((*root)->esq), cord, cep, face, num, hash);
        findCepFaceNum(&((*root)->dir), cord, cep, face, num, hash);
    }
}
//ENCONTRAR CASA PELO 'NOME'
void findName(Tree *root, Coordenada *cord, char* nome, Hash *hash){
    if(root == NULL)
        return;
    
    if(*root != NULL){
        Retangulo aux = (*root)->info;
        if(aux.type == 2)
            if(!strcmp(aux.nome, nome))
                searchQuarter(hash, aux.cep, cord);
        findName(&((*root)->esq), cord, nome, hash);
        findName(&((*root)->dir), cord, nome, hash);
    }
}
//ENCONTRAR COMERCIO DO TIPO 'TP'
void findTP(Tree *root, Coordenada *cord, char *tp, Hash *hash){
    if(root == NULL)
        return;
    
    if(*root != NULL){
        Retangulo aux = (*root)->info;
        if(aux.type == 3)
            if(!strcmp(aux.tp, tp))
                searchQuarter(hash, aux.cep, cord);
        findTP(&((*root)->esq), cord, tp, hash);
        findTP(&((*root)->dir), cord, tp, hash);
    }
}
//ENCONTRAR VÉRTICE MAIS PRÓXIMO PARA PONTO DE ANCORAGEM
int findNearestPoint(Grafo *grafo, Coordenada *cord, Vertice *vertice){
    int i, pos;
    float errox = 9999.9;
    float erroy = 9999.9;
    for(i=0; i < grafo->size; i++){
        if(abs(grafo->vertices[i].x - cord->x) < errox){
            errox = abs(grafo->vertices[i].x - cord->x);
            vertice->x = grafo->vertices[i].x;
            vertice->y = grafo->vertices[i].y;
            pos = i;
        }
    }
    for(i=0; i < grafo->size; i++){
        if(grafo->vertices[i].x == vertice->x && abs(grafo->vertices[i].y - cord->y) < erroy){
            erroy = abs(grafo->vertices[i].y - cord->y);
            vertice->x = grafo->vertices[i].x;
            vertice->y = grafo->vertices[i].y;
            vertice->id = (char*) malloc(sizeof(char)*100);
            strcpy(vertice->id, grafo->vertices[i].id);
            pos = i;
        }
    }
    return pos;
}
//PRINTAR VIAS NO ARQUIVO.SVG
void printStreet(Grafo *grafo, int origem, int *visitado, int cont, FILE *outFile){
    visitado[origem] = cont;
    int i;
    for(i=0; i < grafo->grau[origem]; i++){
        if(!visitado[grafo->positionArc[origem][i]])
            printStreet(grafo, grafo->positionArc[origem][i], visitado, cont+1, outFile);   
        fprintf(outFile,"<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"3\" stroke=\"#55484E\"/>\n", grafo->vertices[origem].x, grafo->vertices[origem].y, grafo->vertices[grafo->positionArc[origem][i]].x, grafo->vertices[grafo->positionArc[origem][i]].y);                
    }
}
//TRACAR ROTA E GERAR ARQUIVO.SVG
void outSVG(Tree *root, Grafo *grafo, int origem, int destino, int nVertices, int *ant){
    int *visitado = (int*) malloc(sizeof(int) * nVertices);

    FILE* outFile = fopen("teste.html", "w+");
    fprintf(outFile, "<svg width=\"3000\" height=\"3000\">\n");
    getInfo(root, outFile); //PRINTAR CIDADE
    
    int i, cont=1;
    for(i=0; i <= nVertices; i++)
        fprintf(outFile, "<circle cx=\"%f\" cy=\"%f\" r=\"5\" style=\"fill: #55484E;\"/>\n", grafo->vertices[i].x, grafo->vertices[i].y);

    for(i=0; i <= nVertices; i++)  
        visitado[i] = 0;
    
    printStreet(grafo, origem, visitado, cont, outFile);    //PRINTAR RUAS

    int aux = destino;
    while(ant[aux] != -1){  //PRINTAR ROTA
        fprintf(outFile,"<circle cx=\"%f\" cy=\"%f\" r=\"5\" style=\"fill: #00ff00;\"/>\n", grafo->vertices[aux].x, grafo->vertices[aux].y);
        fprintf(outFile,"<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"3\" stroke=\"#00ff00\"/>\n", grafo->vertices[aux].x, grafo->vertices[aux].y, grafo->vertices[ant[aux]].x, grafo->vertices[ant[aux]].y);
        aux = ant[aux];
    }
    fprintf(outFile,"<circle cx=\"%f\" cy=\"%f\" r=\"5\" style=\"fill: #00ff00;\"/>\n", grafo->vertices[aux].x, grafo->vertices[aux].y);                    
    fprintf(outFile, "</svg>"); 
    
    fclose(outFile);
}
//CALCULAR DISTANCIA OU TEMPO
void calcPeso(Grafo *grafo, int *ant, int aux, char *consulta, int nArestas){
    int i;
    float cmp = 0.0;
    int tempo = 0;            
    if(!strcmp(consulta, "D")){
        while(ant[aux] != -1){
            for(i=0; i < nArestas; i++)
                if(!strcmp(grafo->arestas[i].i, grafo->vertices[aux].id) && !strcmp(grafo->arestas[i].j, grafo->vertices[ant[aux]].id))
                    cmp = cmp + grafo->arestas[i].cmp;
                    aux = ant[aux];
                }
        printf("Distancia: %f m.\n", cmp);
    }         
    if(!strcmp(consulta, "T")){
        while(ant[aux] != -1){
            for(i=0; i < nArestas; i++)
                if(!strcmp(grafo->arestas[i].i, grafo->vertices[aux].id) && !strcmp(grafo->arestas[i].j, grafo->vertices[ant[aux]].id))
                    tempo = tempo + grafo->arestas[i].tempo;
                    aux = ant[aux];
                }
        printf("Tempo: %d sec.\n", tempo);
    }         
}
//ENCONTRAR TODOS OS COMERCIOS DE TIPO 'TP'
void findAllTP(Tree *root, char *tp, Aresta *aresta){
    if(root == NULL)
        return;
    
    if(*root != NULL){
        Retangulo aux = (*root)->info;
        if(aux.type == 3)
            if(!strcmp(aux.tp, tp) && (!strcmp(aresta->ldir, aux.cep) || !strcmp(aresta->lesq, aux.cep))){
                printf("Nome: %s\n", aux.nome);
                printf("Endereco: %s %s %s\n", aux.cep, aux.face, aux.num);
                printf("Tel: %s\n", aux.tel);
                printf("\n##################################\n");
            }
        findAllTP(&((*root)->esq), tp, aresta);
        findAllTP(&((*root)->dir), tp, aresta);
    }
}
//ENCONTRAR RUA PELO NOME E DESTACAR COMERCIOS DO TIPO 'TP'
void findStreet(Grafo *grafo, Tree *root, char *nomerua, char *tp, int nArestas){
    Aresta *aresta = (Aresta*) malloc(sizeof(Aresta));
    int i;
    for(i=0; i < nArestas; i++)
        if(!strcmp(nomerua, grafo->arestas[i].nome)){
            aresta->i = (char*) malloc(sizeof(char) * 100);
            strcpy(aresta->i, grafo->arestas[i].i);

            aresta->j = (char*) malloc(sizeof(char) * 100);
            strcpy(aresta->j, grafo->arestas[i].j);
            
            aresta->ldir = (char*) malloc(sizeof(char) * 100);
            strcpy(aresta->ldir, grafo->arestas[i].ldir);

            aresta->lesq = (char*) malloc(sizeof(char) * 100);
            strcpy(aresta->lesq, grafo->arestas[i].lesq);
            
            aresta->cmp = grafo->arestas[i].cmp;
            aresta->tempo = grafo->arestas[i].tempo;
            
            aresta->nome = (char*) malloc(sizeof(char) * 100);
            strcpy(aresta->nome, grafo->arestas[i].nome);
            
            findAllTP(root, tp, aresta);
        }
}