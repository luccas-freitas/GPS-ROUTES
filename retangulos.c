/*  
*   TRABALHO 4  -   MAPEAMENTO DA CIDADE DE BITNÓPOLIS
*   LUCCAS DE FREITAS FERREIRA  -   LEONARDO FIRMINO DE SOUZA
*   IMPLEMENTAÇÃO DE TABELA HASH USANDO LISTA ENCADEADA E DUPLOHASHING
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"
#include "hash.h"
#include "retangulos.h"
#define MAX 500

//VARIAVEIS PARA INVOCACAO POR PARAMETRO
char fileName[MAX];
char dirSaida[MAX];
char *solicingaux;
//FGETS MODIFICADA PARA CONCATENAR COM \0
char *fgets2(char* str, int size, FILE* stream){
	char *result = fgets(str, size, stream);
	if(result){
		while (isspace(str[strlen(str) - 1])){
			str[strlen(str) - 1] = '\0';
		}
	}
	return result;
}
//RECURSAO PARA PERCORRER ARVORE E GERAR SVG
void getInfo(Tree *root, FILE *file){
    if(root == NULL)
        return;
    if(*root != NULL){
        //Retangulo (*root)->info = (*root)->info;
        getInfo(&((*root)->esq), file);

        if((*root)->info.type == 0){   //RETANGULO COMUM
            fprintf(file,"\n<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:%s;\"/>", 
            (*root)->info.x, (*root)->info.y, (*root)->info.h, (*root)->info.l, (*root)->info.cor);
        }
        else if((*root)->info.type == 1){  //QUADRA
            fprintf(file,"\n<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:#cc5200;\"/>", 
            (*root)->info.x, (*root)->info.y, (*root)->info.h, (*root)->info.l);
        }
        //else if((*root)->info.type == 2) //CASA
            //algo pra verificar cep
        //else if((*root)->info.type == 3) //COMERCIO
            //algo pra verificar cep
        else if((*root)->info.type == 4){  //HIDRANTE
            fprintf(file,"\n<circle cx=\"%f\" cy=\"%f\" r=\"8\" fill=\"red\"/>", (*root)->info.x, (*root)->info.y);
            fprintf(file, "\n<text x=\"%f\" y=\"%f\" fill=\"white\"> H </text>", (*root)->info.x, (*root)->info.y);
        }

        else if((*root)->info.type == 5){  //SEMAFORO
            fprintf(file,"\n<circle cx=\"%f\" cy=\"%f\" r=\"8\" fill=\"green\"/>", (*root)->info.x, (*root)->info.y);
            fprintf(file, "\n<text x=\"%f\" y=\"%f\" fill=\"red\"> S </text>", (*root)->info.x, (*root)->info.y);
        }

        else if((*root)->info.type == 6){  //RADIO-BASE
            fprintf(file,"\n<circle cx=\"%f\" cy=\"%f\" r=\"8\" fill=\"yellow\"/>", (*root)->info.x, (*root)->info.y);
            fprintf(file, "\n<text x=\"%f\" y=\"%f\" fill=\"black\"> (:c:) </text>", (*root)->info.x, (*root)->info.y);
        }

        getInfo(&((*root)->dir), file);
    }
}
//FUNÇAO DE PROCESSAMENTO DO NOME DO ARQUIVO
void processaNome(){
    char *caminho, *auxcaminho; // tratamento para captar o nome do arquivo de entrada, que será usado para criação dos arquivos de saida
    caminho = strtok(fileName, "/");
    while(caminho != NULL){
        auxcaminho = caminho;
        caminho = strtok(NULL, "/");
    }
    solicingaux = strtok(auxcaminho,".");
}
//GERAR ARQUIVO DE SAIDA SVG
void makeSVG(Tree* root, char *sufix){
    char saida1[MAX]; // pega o nome tratado, e adciona .svg para criação das imagens 
    if(sufix != NULL){  //caso haja sufixo
        int i=0, aux = strlen(solicingaux), j = 0;
        while(j != strlen(solicingaux)){        //procura o segundo "-", caso haja. (conflito com os nomes dos arquivos.ops)
            if(solicingaux[j] == '-'){
                aux = j;
                i++;
            }
            j++;
        }
        if(i == 2)
            solicingaux[aux] = '\0';
        strtok(solicingaux,".svg");
        strcat(solicingaux, "-");
        strcat(solicingaux, sufix);
    }
    strcat(solicingaux,".svg");// concatena a extenção ao arquivo

    strcpy(saida1,dirSaida);
    strcat(saida1,"\\");
    strcat(saida1,solicingaux);
    
    FILE* file = fopen(saida1, "w+"); // abre o arquivo para escrita do svg            
    Retangulo retangulos;
    if(file){
        fprintf(file,"<svg height=\"3000\" width=\"3000\">");
        if(root == NULL)
            return;
        if(*root != NULL){
             getInfo(root, file);
        }
        fprintf(file,"\n</svg>");
    }else
        printf("\nErro ao abrir o arquivo.\n");

    fclose(file);
    printf("\nArquivo SVG gerado.\n");
}
//AREA DE BUSCA PARA REMOÇÃO
int removeRetangulo(Tree *root, Retangulo retangulo, FILE *file){
    if(root == NULL)
        return 0;
    if(*root != NULL){
        Retangulo aux = (*root)->info;
        if(aux.x >= retangulo.x && aux.y >= retangulo.y){
            if(aux.x + aux.h <= retangulo.h && aux.y + aux.l <= retangulo.l){
                fprintf(file, "Objeto removido: (%f, %f) ", (*root)->info.x, (*root)->info.y);
                fprintf(file, "\r\n");
                return removeNode(root, aux);
            }
        }
        removeRetangulo(&((*root)->esq), retangulo, file);
        removeRetangulo(&((*root)->dir), retangulo, file);
    }
}
//AREA DE BUSCA PARA ALTERAR COR
int changeColor(Tree *root, char *cor1, char *cor2, Retangulo retangulo, int num, FILE *file){
    if(root == NULL)
        return 0;
    if(*root != NULL){
        Retangulo aux = (*root)->info;
        if(aux.x >= retangulo.x && aux.y >= retangulo.y){
            if(aux.x + aux.h <= retangulo.h && aux.y + aux.l <= retangulo.l){
                if(strcmp(aux.cor, cor1) == 0){
                    fprintf(file, "(%f, %f)\n", (*root)->info.x, (*root)->info.y);
                    fprintf(file, "\r\n");
                    strcpy((*root)->info.cor, cor2);
                    num++;
                }
            }
        }
        changeColor(&((*root)->esq), cor1, cor2, retangulo, num, file);
        changeColor(&((*root)->dir), cor1, cor2, retangulo, num, file);
    }else
        return num+=num;
}
//ALTERAR COR DE TODOS OS RETANGULOS
int changeAll(Tree *root, char *cor1, char *cor2, int num){
    if(root == NULL)
        return 0;
    if(*root != NULL){
        if(strcmp((*root)->info.cor, cor1) == 0){
            strcpy((*root)->info.cor, cor2);
            num++;
        }
        changeAll(&((*root)->esq), cor1, cor2, num);
        changeAll(&((*root)->dir), cor1, cor2, num);
    }else
        return num+=num;
}

//FUNÇÕES ADICIONAIS PARA O TRABALHO 4 - (HASH)

//MQ?
void procuraMoradores(Hash* hash, char* chave, FILE *file){
    int i, pos, newPos;
    
    if(hash == NULL)
        return;

    int nome = valueString(chave);
    pos = hashFunction1(nome, hash->size);
    for(i=0; i < hash->size; i++){
        newPos = duploHash(pos, nome, i, hash->size);
        if(hash->itens[newPos] == NULL)
            return;

        else if(valueString(hash->itens[newPos]->cep) == nome && hash->itens[newPos]->type == 2){
            fprintf(file, "CEP: %s\n", hash->itens[newPos]->cep);fprintf(file, "\r\n");
            fprintf(file, "FACE: %s\n", hash->itens[newPos]->face);fprintf(file, "\r\n");
            fprintf(file, "NUM: %s\n", hash->itens[newPos]->num);fprintf(file, "\r\n");
            fprintf(file, "NOME: %s\n", hash->itens[newPos]->nome);fprintf(file, "\r\n");
            fprintf(file, "TEL: %s\n", hash->itens[newPos]->tel);fprintf(file, "\r\n");
            fprintf(file, "\n###########################\n");fprintf(file, "\r\n");
            fprintf(file, "\r\n");
        }
    }
}
//MR?
void moradoresRegiao(Tree *root, Hash* hash, Retangulo retangulo, FILE *file){
    if(root == NULL)
        return;
    
    if(*root != NULL){
        Retangulo aux = (*root)->info;

        if(aux.x >= retangulo.x && aux.y >= retangulo.y){
            if(aux.x + aux.h <= retangulo.h && aux.y + aux.l <= retangulo.l){
                if(aux.type == 1){
                    char *cep = malloc(sizeof(char) * 50);
                    strcpy(cep, aux.cep);
                    procuraMoradores(hash, cep, file);
                }
            }
        }
        moradoresRegiao(&((*root)->esq), hash, retangulo, file);
        moradoresRegiao(&((*root)->dir), hash, retangulo, file);
    }
}
//ET?
void procuraQuadra(Hash* hash, char* chave, Retangulo retangulo, FILE *file){
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
            if(hash->itens[newPos]->x >= retangulo.x && hash->itens[newPos]->y >= retangulo.y){
                    if(hash->itens[newPos]->x + hash->itens[newPos]->h <= retangulo.h && hash->itens[newPos]->y + hash->itens[newPos]->l <= retangulo.l){
                        fprintf(file, "Coordenada: (%f, %f)\n", hash->itens[newPos]->x, hash->itens[newPos]->y);
                        fprintf(file, "\r\n");
                        fprintf(file, "Dimensoes: (%f, %f)\n", hash->itens[newPos]->h, hash->itens[newPos]->l);
                        fprintf(file, "\r\n");
                        fprintf(file, "CEP: %s\n", hash->itens[newPos]->cep);fprintf(file, "\r\n");
                        fprintf(file, "\n###########################\n");fprintf(file, "\r\n");
                    }            
            }
        }
    }
}
//ET?
void comercioQuadra(Tree *root, Hash* hash, Retangulo retangulo, char *tp, FILE *file){
    if(root == NULL)
        return;
    
    if(*root != NULL){
        Retangulo aux = (*root)->info;
        if(!strcmp(aux.tp, tp)){
            char *cep = malloc(sizeof(char) * 50);
            strcpy(cep, aux.cep);
            procuraQuadra(hash, cep, retangulo, file);
        }
        comercioQuadra(&((*root)->esq), hash, retangulo, tp, file);
        comercioQuadra(&((*root)->dir), hash, retangulo, tp, file);
    }
}
//ED?
void procuraComercio(Hash* hash, char* chave, char *tp, FILE *file){
    int i, pos, newPos;
    
    if(hash == NULL)
        return;

    int nome = valueString(chave);
    pos = hashFunction1(nome, hash->size);
    for(i=0; i < hash->size; i++){
        newPos = duploHash(pos, nome, i, hash->size);
        if(hash->itens[newPos] == NULL)
            return;
        else if(valueString(hash->itens[newPos]->cep) == nome && hash->itens[newPos]->type == 3){
            if(!strcmp(tp, hash->itens[newPos]->tp)){   //SE FOR O TIPO PASSADO
                fprintf(file, "CEP: %s\n", hash->itens[newPos]->cep);fprintf(file, "\r\n");
                fprintf(file, "FACE: %s\n", hash->itens[newPos]->face);fprintf(file, "\r\n");
                fprintf(file, "NUM: %s\n", hash->itens[newPos]->num);fprintf(file, "\r\n");
                fprintf(file, "TIPO: %s\n", hash->itens[newPos]->tp);fprintf(file, "\r\n");
                fprintf(file, "NOME: %s\n", hash->itens[newPos]->nome);fprintf(file, "\r\n");
                fprintf(file, "TEL: %s\n", hash->itens[newPos]->tel);fprintf(file, "\r\n");
                fprintf(file, "\n###########################\n");fprintf(file, "\r\n");
                fprintf(file, "\r\n");
            }
            else if(!strcmp(tp,"*")){       //SE FOR * PRINTA TODOS
                fprintf(file, "CEP: %s\n", hash->itens[newPos]->cep);fprintf(file, "\r\n");
                fprintf(file, "FACE: %s\n", hash->itens[newPos]->face);fprintf(file, "\r\n");
                fprintf(file, "NUM: %s\n", hash->itens[newPos]->num);fprintf(file, "\r\n");
                fprintf(file, "TIPO: %s\n", hash->itens[newPos]->tp);fprintf(file, "\r\n");
                fprintf(file, "NOME: %s\n", hash->itens[newPos]->nome);fprintf(file, "\r\n");
                fprintf(file, "TEL: %s\n", hash->itens[newPos]->tel);fprintf(file, "\r\n");
                fprintf(file, "\n###########################\n");fprintf(file, "\r\n");
                fprintf(file, "\r\n");
            }
        }
    }
}
//ED?
void comercioRegiao(Tree *root, Hash* hash, Retangulo retangulo, char *tp, FILE *file){
    if(root == NULL)
        return;
    
    if(*root != NULL){
        Retangulo aux = (*root)->info;

        if(aux.x >= retangulo.x && aux.y >= retangulo.y){
            if(aux.x + aux.h <= retangulo.h && aux.y + aux.l <= retangulo.l){
                if(aux.type == 1){
                    char *cep = malloc(sizeof(char) * 50);
                    strcpy(cep, aux.cep);
                    procuraComercio(hash, cep, tp, file);
                }
            }
        }
        comercioRegiao(&((*root)->esq), hash, retangulo, tp, file);
        comercioRegiao(&((*root)->dir), hash, retangulo, tp, file);
    }
}
//ED?
void comerciosTotal(Tree *root, char *tp, FILE *file){
    if(root == NULL)
        return;
    if(*root != NULL){
        Retangulo aux = (*root)->info;
        if(aux.type == 3){
            if(!strcmp(tp, aux.tp)){   //SE FOR O TIPO PASSADO
                fprintf(file, "CEP: %s\n", aux.cep);fprintf(file, "\r\n");
                fprintf(file, "FACE: %s\n", aux.face);fprintf(file, "\r\n");
                fprintf(file, "NUM: %s\n", aux.num);fprintf(file, "\r\n");
                fprintf(file, "TIPO: %s\n", aux.tp);fprintf(file, "\r\n");
                fprintf(file, "NOME: %s\n", aux.nome);fprintf(file, "\r\n");
                fprintf(file, "TEL: %s\n", aux.tel);fprintf(file, "\r\n");
                fprintf(file, "\n###########################\n");fprintf(file, "\r\n");
                fprintf(file, "\r\n");
            }
            else if(!strcmp(tp,"*")){       //SE FOR * PRINTA TODOS
                fprintf(file, "CEP: %s\n", aux.cep);fprintf(file, "\r\n");
                fprintf(file, "FACE: %s\n", aux.face);fprintf(file, "\r\n");
                fprintf(file, "NUM: %s\n", aux.num);fprintf(file, "\r\n");
                fprintf(file, "TIPO: %s\n", aux.tp);fprintf(file, "\r\n");
                fprintf(file, "NOME: %s\n", aux.nome);fprintf(file, "\r\n");
                fprintf(file, "TEL: %s\n", aux.tel);fprintf(file, "\r\n");
                fprintf(file, "\n###########################\n");fprintf(file, "\r\n");
                fprintf(file, "\r\n");
            }
        }
        comerciosTotal(&((*root)->esq), tp, file);
        comerciosTotal(&((*root)->dir), tp, file);
    }
}
//HQ?
void hidranteQuadra(Tree *root, Retangulo retangulo, FILE *file){
    if(root == NULL)
        return;
    if(*root != NULL){
        Retangulo aux = (*root)->info;
        if(!strcmp(retangulo.cep,aux.nome)){
            if(aux.x + aux.h <= retangulo.l + aux.x && aux.y + aux.l <= retangulo.l + aux.y){
                if(aux.type == 4){
                    fprintf(file, "ID: %s\n", aux.nome);fprintf(file, "\r\n");
                    fprintf(file, "Coordenada-(%f, %f)-\n", aux.x, aux.y);fprintf(file, "\r\n");
                    fprintf(file, "\r\n");    
                }
            }
        }
        hidranteQuadra(&((*root)->esq), retangulo, file);
        hidranteQuadra(&((*root)->dir), retangulo, file);
    }
}
//QT?
void buscaTorreArea(Tree *root, Retangulo retangulo, FILE *file){
    if(root == NULL)
        return;
    if(*root != NULL){
        Retangulo aux = (*root)->info;
        if(aux.type == 6){
            if(aux.x >= retangulo.x && aux.y >= retangulo.y){
                if(aux.x <= retangulo.x + retangulo.h && aux.y <= retangulo.y + retangulo.l){
                    fprintf(file, "CEP: %s\n", retangulo.cep);fprintf(file, "\r\n");
                    fprintf(file, "Ancoragem: (%f, %f)\n", retangulo.x, retangulo.y);fprintf(file, "\r\n");
                    fprintf(file, "Dimensoes: (H %f, L %f)\n", retangulo.h, retangulo.l);fprintf(file, "\r\n");
                    fprintf(file, "\n###########################\n");fprintf(file, "\r\n");
                    fprintf(file, "\r\n");
                }
        
            }
        }
        buscaTorreArea(&((*root)->esq), retangulo, file);
        buscaTorreArea(&((*root)->dir), retangulo, file);   
    }
}
//QT?
void quadraTorre(Tree *root, FILE *file){//quadras com torres de celular
    Tree *rootAux = root;
    if(root == NULL)  
        return;
    if(*root != NULL){
        Retangulo aux = (*root)->info;
        if(aux.type == 1)
            buscaTorreArea(rootAux, aux, file);

        quadraTorre(&((*root)->esq), file);
        quadraTorre(&((*root)->dir), file);
    }
}
//H?
void hidrante(Tree *root, Retangulo retangulo, FILE *file){
    if(root == NULL)
        return;
    if(*root != NULL){
        Retangulo aux = (*root)->info;
        if(aux.x >= retangulo.x && aux.y >= retangulo.y){
            if(aux.x + aux.h <= retangulo.h && aux.y + aux.l <= retangulo.l){
                if(aux.type == 4){
                    fprintf(file, "ID: %s\n", aux.nome);fprintf(file, "\r\n");
                    fprintf(file, "(%f, %f)\n", aux.x, aux.y);fprintf(file, "\r\n");
                    fprintf(file, "\r\n");
                }
            }
        }
        hidrante(&((*root)->esq), retangulo, file);
        hidrante(&((*root)->dir), retangulo, file);
    }
}
//S?
void semaforo(Tree *root, Retangulo retangulo, FILE *file){
    if(root == NULL)
        return;
    if(*root != NULL){
        Retangulo aux = (*root)->info;
        if(aux.x >= retangulo.x && aux.y >= retangulo.y){
            if(aux.x + aux.h <= retangulo.h && aux.y + aux.l <= retangulo.l){
                if(aux.type == 5){
                    fprintf(file, "ID: %s\n", aux.nome);fprintf(file, "\r\n");
                    fprintf(file, "(%f, %f)\n", aux.x, aux.y);fprintf(file, "\r\n");
                    fprintf(file, "\r\n");
                }
            }
        }
        semaforo(&((*root)->esq), retangulo, file);
        semaforo(&((*root)->dir), retangulo, file);
    }
}