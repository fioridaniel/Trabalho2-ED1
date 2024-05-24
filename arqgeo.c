#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "arqsvg.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "arqgeo.h"
#include "leArquivo.h"
#include "arqsvg.h"
#include "shapebank.h"

#define MAX_SIZE 10000

void ComandosGeo(void* shapebank, GcCore gccore, FILE* arqGeo, FILE * arqSvgInicial) {

    char decoFormatada[1000];
    int id;
    double raio, xc, yc, x, y, w, h, x1, Py1, x2, y2;
    char corp[300], corb[300], txt[300], comando[10], tipo, a;
    Forma forma;
    FILE* fsvg = arqSvgInicial;

    LISTA lista = RetornaLista(gccore);

    char linha[MAX_SIZE];
    char aux[MAX_SIZE];

    while(leLinha(arqGeo, linha, 1000) == true) {
        aux[0] = '\0'; // Esvazia a variavel aux e comando a cada iteracao
        comando[0] = '\0';
        strcpy(aux, linha);
        sscanf(aux, "%s", comando);
        printf("comando: %s\n", comando);
        char fFamily[50] = "arial", fWeight[50] = "normal", fSize[50] = "16";

        if (strcmp(comando, "c") == 0) {

                sscanf(aux, "%c %d %lf %lf %lf %s %s", &tipo, &id, &xc, &yc, &raio, corb, corp);
                sprintf(decoFormatada, " fill=\"%s\" stroke=\"%s\"", corp, corb);
                forma = CriaStructCirculo(id, xc, yc, raio, corp, corb);
                escreveCirculoSvg(fsvg, xc, yc, raio, decoFormatada);
                
            } else if (strcmp(comando, "r") == 0) {
                
                sscanf(aux, "%c %d %lf %lf %lf %lf %s %s", &tipo,  &id, &x, &y, &w, &h, corb, corp);
                sprintf(decoFormatada, " fill=\"%s\" stroke=\"%s\"", corp, corb);
                forma = CriaStructRetangulo(id, x, y, w, h, corb, corp);
                escreveRetanguloSvg(fsvg, x, y, w, h, decoFormatada);
                

            } else if (strcmp(comando, "l") == 0) {
                
                sscanf(aux, "%c %d %lf %lf %lf %lf %s", &tipo, &id, &x1, &Py1, &x2, &y2, corp);
                forma = CriaStructLinha(id, x1, Py1, x2, y2, corp);
                escreveLinhaSvg(fsvg, x1, Py1, x2, y2, corp);
                

            } else if (strcmp(comando, "t") == 0) {
                
                sscanf(aux, "%c %d %lf %lf %s %s %c %s", &tipo, &id, &x, &y, corb, corp, &a, txt);
                sprintf(decoFormatada, " fill=\"%s\" stroke=\"%s\" font-size=\"%s\" font-weight=\"%s\" font-family=\"%s\"", corp, corb, fSize, fWeight, fFamily);
                forma = CriaStructTexto(id, x, y, corp, corb, txt, a);
                escreveTextoSvg(fsvg, x, y, txt, decoFormatada);  
                

            } else if (strcmp(comando, "ts") == 0) {

                sscanf(aux, "%s %s %s", fFamily, fWeight, fSize);
                continue;
            
            } else if (*comando == '\n') {
                break;
            }
            
            else {
                printf("Comando nao encontrado....");
                exit(1);
            }

            DepositarNoshape(shapebank, forma, id);
            IncrementSize(gccore, tipo);
            insertNode(lista, forma);
        }
    }