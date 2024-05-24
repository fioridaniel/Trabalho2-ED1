#ifndef LINHA__
#define LINHA__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
    Uma linha eh definida por duas coordenadas ancoras, que representam suas
    respectivas extremidades (x1, y1) e (x2, y2). Possui como atributos a cor da linha.
    e seu id. O id eh um numero inteiro responsavel por diferenciar
    as formas, pois nao eh possivel existir duas formas que possuem o mesmo id,
    tornando cada forma unica. O conjunto de operacoes da linha estao definidas a seguir.
*/


typedef void* LINHA;

// Inicializa um objeto linha com os parâmetros fornecidos.
LINHA inicializaLinha(int id, double x1, double y1, double x2, double y2, char* cor);

// Retorna o ID associado à linha especificada.
int getIdlinha(LINHA l);

// Retorna a coordenada X1 da linha especificada.
double getX1(LINHA l);

// Retorna a coordenada Y1 da linha especificada.
double getY1(LINHA l);

// Retorna a coordenada X2 da linha especificada.
double getX2(LINHA l);

// Retorna a coordenada Y2 da linha especificada.
double getY2(LINHA l);

// Retorna a cor da linha especificada.
char* getCorLIN(LINHA l);

// Define a coordenada X1 da linha especificada.
void setX1(LINHA l, double X1);

// Define a coordenada Y1 da linha especificada.
void setY1(LINHA l, double Y1);

// Define a coordenada X2 da linha especificada.
void setX2(LINHA l, double X2);

// Define a coordenada Y2 da linha especificada.
void setY2(LINHA l, double Y2);

// Define a cor da linha especificada.
void setCorLIN(LINHA l, char *cor);

// Retorna o tamanho do objeto Linha.
long int SizeLinha();

#endif