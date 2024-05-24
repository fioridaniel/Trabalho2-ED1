#ifndef CIRCULO_H
#define CIRCULO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
    Um circulo eh definido por uma coordenada ancora, que representa o seu 
    centro em (xc, yc), e sua dimensao é definida pelo seu raio r.
    Alem disso, possui como atributos cor do preenchimento (corp), cor da
    borda (corb) e um id. O id eh um numero inteiro responsavel por diferenciar
    as formas, pois nao eh possivel existir duas formas que possuem o mesmo id,
    tornando cada forma unica. O conjunto de operacoes do circulo estao definidas a seguir.
*/
typedef void* CIRCULO;

// Inicializa um objeto circulo com os parametros fornecidos.
CIRCULO inicializaCirculo(int id, double x, double y, double r, char *corp, char *corb);

// Retorna o ID associado ao circulo especificado.
int getIdCirculo(CIRCULO cir);

// Retorna o raio do circulo especificado.
double getRaio(CIRCULO cir);

// Retorna a coordenada X do circulo especificado.
double getXc(CIRCULO cir);

// Retorna a coordenada Y do circulo especificado.
double getYc(CIRCULO cir);

// Retorna a cor de preenchimento do circulo especificado.
char* getCorpCIR(CIRCULO cir);

// Retorna a cor da borda do circulo especificado.
char* getCorbCIR(CIRCULO cir);

// Define a coordenada X do circulo especificado.
void setXc(CIRCULO cir, double xc);

// Define a coordenada Y do circulo especificado.
void setYc(CIRCULO cir, double yc);

// Define a cor de preenchimento do circulo especificado.
void setCorpCIR(CIRCULO cir, char* corp);

// Define a cor da borda do circulo especificado.
void setCorbCIR(CIRCULO cir, char* corb);

// Retorna o tamanho do objeto Circulo.
long int SizeCirculo();

#endif // CIRCULO_H