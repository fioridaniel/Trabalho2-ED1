#ifndef RETANGULO__
#define RETANGULO__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
    Um retangulo eh definido pela suas coordenadas ancora, localizadas
    no canto inferior esquerdo em (x, y). Suas dimensoes sao representadas 
    pela largura w, e altura h. possui como atributos cor do preenchimento 
    (corp), cor da borda (corb) e um id. O id eh um numero inteiro responsavel por diferenciar
    as formas, pois nao eh possivel existir duas formas que possuem o mesmo id,
    tornando cada forma unica. O conjunto de operacoes do retangulo estao definidas a seguir.
*/

typedef void* RETANGULO;

// Inicializa um objeto retangulo com os parametros fornecidos.
RETANGULO inicializaRetangulo(int id, double x, double y, double w, double h, char* corb, char* corp);

// Retorna o ID associado ao retangulo especificado.
int getIdRetangulo(RETANGULO ret);

// Retorna a altura do retangulo especificado.
double getH(RETANGULO ret);

// Retorna a largura do retangulo especificado.
double getW(RETANGULO ret);

// Retorna a coordenada X do retangulo especificado.
double getX(RETANGULO ret);

// Retorna a coordenada Y do retangulo especificado.
double getY(RETANGULO ret);

// Retorna a cor de preenchimento do retangulo especificado.
char* getCorpRET(RETANGULO ret);

// Retorna a cor da borda do retangulo especificado.
char* getCorbRET(RETANGULO ret);

// Define a coordenada X do retangulo especificado.
void setX(RETANGULO ret, double X);

// Define a coordenada Y do retangulo especificado.
void setY(RETANGULO ret, double Y);

// Define a largura do retangulo especificado.
void setW(RETANGULO ret, double W);

// Define a altura do retangulo especificado.
void setH(RETANGULO ret, double H);

// Define a cor de preenchimento do retangulo especificado.
void setCorpRET(RETANGULO ret, char* corp);

// Define a cor da borda do retangulo especificado.
void setCorbRET(RETANGULO ret, char* corb);

// Retorna o tamanho do objeto Retangulo.
long int SizeRetangulo();

#endif