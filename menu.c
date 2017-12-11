/*  
*   TRABALHO 5  -   DC UEL MAPS
*   LUCCAS DE FREITAS FERREIRA  -   201200560446
*   CONTINUAÇÃO DO TRABALHO ANTERIOR IMPLEMENTANDO A ESTRUTURA GRAFO
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tree.h"
#include "hash.h"
#include "graph.h"
#include "vias.h"
#include "retangulos.h"
#define MAX 500

//TRATAR ARQUIVO .OPS
void Menu(FILE *file, Tree *raiz, Hash *hash, Grafo *grafo, int nVertices, int nArestas){
	Retangulo retangulos;   //RETANGULO AUXILIAR PARA EXECUTAR OPERAÇÕES
    char *sufix;
    int iniBat = 0;  //VERIFICAR
    int numRecol=0, numInsert = 0;
    int para;
	char *func, getString[MAX];

    Vertice *origem = (Vertice*) malloc(sizeof(Vertice));
    Vertice *destino = (Vertice*) malloc(sizeof(Vertice));
    Coordenada *inicio = (Coordenada*) malloc(sizeof(Coordenada));
    Coordenada *chegada = (Coordenada*) malloc(sizeof(Coordenada));

    FILE *out = fopen("output.txt","w+");

    if(file){
        while(!feof(file)){
            //BUFFER DE ENTRADA
            fgets2(getString, MAX, file);
	    	if(!strcmp(getString,"#"))
                break;
            
            func = strtok(getString," ");
            
            //INSERIR RETANGULO NA ARVORE
            if(!strcmp(func,"r")){
                retangulos.x = atof(strtok(NULL," "));
                retangulos.y = atof(strtok(NULL," "));
                retangulos.h = atof(strtok(NULL," "));
                retangulos.l = atof(strtok(NULL," "));
                retangulos.cor = strtok(NULL,"\0");

                retangulos.num = "\0";
                retangulos.face = "\0";
                retangulos.cep = "\0";
                retangulos.nome = "\0";
                retangulos.tel = "\0";
                retangulos.tp = "\0";
                retangulos.type = 0;

                insertNode(raiz, retangulos);
                numInsert++;
            }
            //GERAR SVG PARCIAL
            else if(!strcmp(func,"o")){
                sufix = strtok(NULL,"\0");
                makeSVG(raiz, sufix);
            }
            //AREA DE BUSCA PRA DELEÇÃO
            else if(!strcmp(func,"d")){
                retangulos.x = atof(strtok(NULL," "));
                retangulos.y = atof(strtok(NULL," "));
                retangulos.h = atof(strtok(NULL," "));
                retangulos.l = atof(strtok(NULL,"\0"));
                retangulos.cor = NULL;

                while(para)
                    para = removeRetangulo(raiz, retangulos, out);
                printf("\nArea de busca removida.\n");
            }
            //AREA DE BUSCA PRA MUDANÇA DE COR
            else if(!strcmp(func,"c")){
                char* cor1 = strtok(NULL, " ");
                char* cor2 = strtok(NULL, " ");
                char* aux = strtok(NULL, " ");
                if(aux != NULL){
                    retangulos.x = atof(aux);
                    retangulos.y = atof(strtok(NULL," "));
                    retangulos.h = atof(strtok(NULL," "));
                    retangulos.l = atof(strtok(NULL,"\0"));
                    retangulos.cor = NULL;
 
                    numRecol += changeColor(raiz, cor1, cor2, retangulos, numRecol, out);
                    printf("\nArea de busca recolorida.\n");
                }
                else{
                    numRecol += changeAll(raiz, cor1, cor2, numRecol);
                    printf("\nTodos os retangulos foram recoloridos.\n");
                }
            }

            //FUNÇÕES ADICIONAIS - TRABALHO 4 (HASH)

            //INSERIR QUADRA
            else if(!strcmp(func, "q")){
                retangulos.x = atof(strtok(NULL," "));
                retangulos.y = atof(strtok(NULL," "));
                retangulos.h = atof(strtok(NULL," "));
                retangulos.l = atof(strtok(NULL," "));
                retangulos.cep = strtok(NULL,"\0");

                retangulos.num = "\0";
                retangulos.face = "\0";
                retangulos.cor = "\0";
                retangulos.nome = "\0";
                retangulos.tel = "\0";
                retangulos.tp = "\0";

                retangulos.type = 1;  //quadra
                insertNode(raiz, retangulos);

                insertHash(hash, retangulos);
                numInsert++;
            }
            //INSERIR CASA
            else if(!strcmp(func, "m")){
                retangulos.cep = strtok(NULL," ");
                retangulos.face = strtok(NULL," ");
                retangulos.num = strtok(NULL," ");
                retangulos.nome = strtok(NULL," ");
                retangulos.tel = strtok(NULL,"\0");

                retangulos.x = 0;
                retangulos.y = 0;
                retangulos.h = 0;
                retangulos.l = 0;
                retangulos.cor = "\0";
                retangulos.tp = "\0";

                retangulos.type = 2;
                insertNode(raiz, retangulos);
                insertHash(hash, retangulos);
                numInsert++;
            }
            //INSERIR COMERCIO
            else if(!strcmp(func, "e")){
                retangulos.cep = strtok(NULL," ");
                retangulos.face = strtok(NULL," ");
                retangulos.num = strtok(NULL," ");
                retangulos.tp = strtok(NULL," ");
                retangulos.nome = strtok(NULL," ");
                retangulos.tel = strtok(NULL,"\0");
               	
               	retangulos.x = 0;
                retangulos.y = 0;
                retangulos.h = 0;
                retangulos.l = 0;
                retangulos.cor = "\0";

                retangulos.type = 3;
                insertNode(raiz, retangulos);
                insertHash(hash, retangulos);
                numInsert++;
            }
            //INSERIR HIDRANTE
            else if(!strcmp(func, "h")){
                retangulos.nome = strtok(NULL, " ");
                retangulos.x = atof(strtok(NULL, " "));
                retangulos.y = atof(strtok(NULL, "\0"));

                retangulos.h = 0;
                retangulos.l = 0;
                retangulos.cor = "\0";
                retangulos.num = "\0";
                retangulos.face = "\0";
                retangulos.cep = "\0";
                retangulos.tel = "\0";
                retangulos.tp = "\0";

                retangulos.type = 4;
                insertNode(raiz, retangulos);
                numInsert++;
            }
            //INSERIR SEMAFORO
            else if(!strcmp(func, "s")){
                retangulos.nome = strtok(NULL," ");
                retangulos.x = atof(strtok(NULL, " "));
                retangulos.y = atof(strtok(NULL, "\0"));

                retangulos.h = 0;
                retangulos.l = 0;
                retangulos.cor = "\0";
                retangulos.num = "\0";
                retangulos.face = "\0";
                retangulos.cep = "\0";
                retangulos.tel = "\0";
                retangulos.tp = "\0";

                retangulos.type = 5;
				insertNode(raiz, retangulos);
                numInsert++;
            }
            //INSERIR RADIO-BASE
            else if(!strcmp(func, "t")){
                retangulos.nome = strtok(NULL, " ");
                retangulos.x = atof(strtok(NULL, " "));
                retangulos.y = atof(strtok(NULL, "\0"));

                retangulos.h = 0;
                retangulos.l = 0;
                retangulos.cor = "\0";
                retangulos.num = "\0";
                retangulos.face = "\0";
                retangulos.cep = "\0";
                retangulos.tel = "\0";
                retangulos.tp = "\0";
                retangulos.type = 6;
                insertNode(raiz, retangulos);
                numInsert++;
            }

            //FUNCOES UTILIZANDO HASH

            //IMPRIMIR MORADORES DE UMA QUADRA
            else if(!strcmp(func, "mq?")){
            	char *cep = strtok(NULL, "\0");
            	fprintf(out, "Moradores da Quadra %s:", cep);fprintf(out, "\r\n");
            	procuraMoradores(hash, cep, out);
            }
            //IMPRIMIR MORADORES DE UMA REGIÃO
            else if(!strcmp(func, "mr?")){
            	Retangulo aux;
            	aux.x = atof(strtok(NULL," "));
                aux.y = atof(strtok(NULL," "));
                aux.h = atof(strtok(NULL," "));
                aux.l = atof(strtok(NULL,"\0"));
                fprintf(out, "Moradores da Regiao:");fprintf(out, "\r\n");
                moradoresRegiao(raiz, hash, aux, out);
            }
            //IMPRIME QUADRAS QUE POSSUEM COMERCIO DO TIPO 'TP' (* MOSTRA TODOS OS COMERCIOS)
            else if(!strcmp(func, "et?")){
                Retangulo aux;
                char* tp = strtok(NULL, " ");
                char* test = strtok(NULL, " ");
                fprintf(out, "Quadras que possuem estabelecimentos do tipo %s dentro da regiao:\n\n", tp);fprintf(out, "\r\n");
                if(test != NULL){
                    aux.x = atof(test);
                    aux.y = atof(strtok(NULL," "));
                    aux.h = atof(strtok(NULL," "));
                    aux.l = atof(strtok(NULL,"\0"));

                    comercioQuadra(raiz, hash, aux, tp, out);
                }
                else{
                    comerciosTotal(raiz, tp, out);
                }
            }
            //IMPRIME DADOS DE COMERCIO DE TIPO 'TP' EM UMA REGIAO (OPCIONAL), (* MOSTRA TODOS OS COMERCIOS)
            else if(!strcmp(func, "ed?")){
                Retangulo aux;
                char* tp = strtok(NULL, " ");
                char* test = strtok(NULL, " ");
                fprintf(out, "\nEstabelecimentos do tipo %s dentro da regiao:\n\n", tp); fprintf(out, "\r\n");
                if(test != NULL){
                    aux.x = atof(test);
                    aux.y = atof(strtok(NULL," "));
                    aux.h = atof(strtok(NULL," "));
                    aux.l = atof(strtok(NULL,"\0"));

                    comercioRegiao(raiz, hash, aux, tp, out);
                }
                else{
                    comerciosTotal(raiz, tp, out);
                }
            }
            //QUAIS HIDRANTES EXISTEM NA REGIAO (ID E COORDENADA)
            else if(!strcmp(func, "h?")){
				Retangulo aux;
            	aux.x = atof(strtok(NULL," "));
                aux.y = atof(strtok(NULL," "));
                aux.h = atof(strtok(NULL," "));
                aux.l = atof(strtok(NULL,"\0"));
                fprintf(out, "Hidrantes existentes na regiao buscada:\n");fprintf(out, "\r\n");
                hidrante(raiz, aux, out);
            }
            //QUAIS SEMAFOROS EXISTEM NA REGIAO (ID E COORDENADA)
            else if(!strcmp(func, "s?")){
				Retangulo aux;
            	aux.x = atof(strtok(NULL," "));
                aux.y = atof(strtok(NULL," "));
                aux.h = atof(strtok(NULL," "));
                aux.l = atof(strtok(NULL,"\0"));
                fprintf(out, "Semaforos existentes na regiao buscada:\n");fprintf(out, "\r\n");
                semaforo(raiz, aux, out);
            }
            //QUAIS HIDRANTES ESTAO DENTRO DE UMA LARGURA NA QUADRA
            else if(!strcmp(func, "hq?")){
                Retangulo aux;
                aux.cep = strtok(NULL," ");
                aux.l = atof(strtok(NULL,"\0"));
                fprintf(out, "Hidrantes existentes no cep %s:\n", aux.cep);fprintf(out, "\r\n");
                hidranteQuadra(raiz, aux, out);
            }
            //QUAIS QUADRAS POSSUEM BASE-RADIO
            else if(!strcmp(func, "qt?")){
                fprintf(out, "Quadras que possuem torres sobre sua área:\n");fprintf(out, "\r\n");
                quadraTorre(raiz, out);
            }

            //FUNÇÕES ADICIONAIS - TRABALHO 5 (GRAFO)

            //PERCORRER GRAFO - FONE -> CEP/FACE/NUM
            else if(!strcmp(func,"pfe?")){
                char *sufix;
                char *consulta = strtok(NULL, " ");
                char *saida = strtok(NULL, " ");
                if(!strcmp(saida, "p"))
                    sufix = strtok(NULL, " ");
                
                char *fone = strtok(NULL, " ");
                char *cep = strtok(NULL, " ");
                char *face = strtok(NULL, " ");
                char *num = strtok(NULL, "\0");

                findPhone(raiz, fone, hash, inicio);    //PONTO DE SAIDA
                int pos1 = findNearestPoint(grafo, inicio, origem);
                
                findCepFaceNum(raiz, chegada, cep, face, num, hash); //PONTO DE CHEGADA
                int pos2 = findNearestPoint(grafo, chegada, destino);
                
                int ant[nVertices]; int dist[nVertices];  //ENCONTRAR MENOR CAMINHO
                dijkstra(grafo, pos1, ant, dist);
                
                outSVG(raiz, grafo, pos1, pos2, nVertices, ant);    //CALCULAR ROTA
                calcPeso(grafo, ant, pos2, consulta, nArestas);
            }
            //PERCORRER GRAFO - NOME1 -> NOME2
            else if(!strcmp(func,"pnn?")){
                char *sufix;
                char *consulta = strtok(NULL, " ");
                char *saida = strtok(NULL, " ");
                if(!strcmp(saida, "p"))
                    sufix = strtok(NULL, " ");
                
                char *nome1 = strtok(NULL, " ");
                char *nome2 = strtok(NULL, "\0");

                findName(raiz, inicio, nome1, hash);  //PONTO DE SAIDA
                int pos1 = findNearestPoint(grafo, inicio, origem);

                findName(raiz, chegada, nome2, hash); //PONTO DE CHEGADA
                int pos2 = findNearestPoint(grafo, chegada, destino);

                int ant[nVertices]; int dist[nVertices];  //ENCONTRAR MENOR CAMINHO
                dijkstra(grafo, pos1, ant, dist);
                
                outSVG(raiz, grafo, pos1, pos2, nVertices, ant);    //CALCULAR ROTA
                calcPeso(grafo, ant, pos2, consulta, nArestas);
            }
            //PERCORRER GRAFO - CEP/FACE/NUM -> TP *****VERIFICAR COMO IR NO MAIS PROXIMO*****
            else if(!strcmp(func,"pet?")){
                char *sufix;
                char *consulta = strtok(NULL, " ");
                char *saida = strtok(NULL, " ");
                if(!strcmp(saida, "p"))
                    sufix = strtok(NULL, " ");
                
                char *cep = strtok(NULL, " ");
                char *face = strtok(NULL, " ");
                char *num = strtok(NULL, " ");
                char *tp = strtok(NULL, "\0");

                findCepFaceNum(raiz, inicio, cep, face, num, hash); //PONTO DE SAIDA
                int pos1 = findNearestPoint(grafo, inicio, origem);

                findTP(raiz, chegada, tp, hash);    //PONTO DE CHEGADA
                int pos2 = findNearestPoint(grafo, chegada, destino);

                int ant[nVertices]; int dist[nVertices];  //ENCONTRAR MENOR CAMINHO
                dijkstra(grafo, pos1, ant, dist);
                
                outSVG(raiz, grafo, pos1, pos2, nVertices, ant);    //CALCULAR ROTA
                calcPeso(grafo, ant, pos2, consulta, nArestas);
            }
            //LISTAR COMERCIO DO TIPO 'TP' AO LONGO DA RUA
            else if(!strcmp(func,"qer?")){
                char *sufix;
                char *consulta = strtok(NULL, " ");
                char *saida = strtok(NULL, " ");
                if(!strcmp(saida, "p"))
                    sufix = strtok(NULL, " ");
                
                char *nomerua = strtok(NULL, " ");
                char *tp = strtok(NULL, "\0");

                findStreet(grafo, raiz, nomerua, tp, nArestas);
            }
        }
    }else{
        printf("\nErro ao abrir o arquivo .OPS\n");
    }
    fclose(out);
}
//TRATAR ARQUIVO .VIAS
void Menu2(FILE *file, Grafo *grafo, int nVertices){
    int i = 0, j = 0;
    int orig, dest;
    char getString[MAX], *func;
    Vertice vertice;
    Aresta aresta;
    
    if(file){
        while(!feof(file)){
            fgets2(getString, MAX, file);
            if(!strcmp(getString,"#"))
                break;
            
            func = strtok(getString," ");
            //INSERIR VERTICE
            if(!strcmp(func,"v")){
                vertice.id = strtok(NULL, " ");
                vertice.x = atof(strtok(NULL," "));
                vertice.y = atof(strtok(NULL,"\0"));
                
                insertVertex(grafo, vertice, i);
                i++;
            }
            //INSERIR ARESTA
            if(!strcmp(func,"e")){
                aresta.i = strtok(NULL," ");    //ORIGEM
                aresta.j = strtok(NULL," ");   //DESTINO
                aresta.ldir = strtok(NULL," ");
                aresta.lesq = strtok(NULL," ");
                aresta.cmp = atof(strtok(NULL," "));
                aresta.tempo = atoi(strtok(NULL," "));
                aresta.nome = strtok(NULL,"\0");
                
                for(i=0; i <= nVertices; i++){
                    if(!strcmp(grafo->vertices[i].id, aresta.i)){
                        orig = i;
                        break;
                    }
                }
                for(i=0; i <= nVertices; i++){
                    if(!strcmp(grafo->vertices[i].id, aresta.j)){
                        dest = i;
                        break;
                    }
                }
                insertArc(grafo, orig, dest, aresta, j);
                j++;
            }
        }
    }else{
        printf("\nErro ao abrir o arquivo .VIAS\n");
    }
}