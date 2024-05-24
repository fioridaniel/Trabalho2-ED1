#ifndef _TEXTO_
#define _TEXTO_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
    Um texto eh definido pela sua coordenada ancora em (x,y), e por um 
    caractere 'a', que define se a coordenada ancora estara no inicio, 
    meio, ou fim do texto. Respectivamente i, m e f. O texto possui como atributos
    cor do preenchimento (corp), cor da borda (corb), uma string que 
    armazena o texto, e um id. O id eh um numero inteiro responsavel por diferenciar
    as formas, pois nao eh possivel existir duas formas que possuem o mesmo id,
    tornando cada forma unica. O conjunto de operacoes do texto estao definidas a seguir.
*/

typedef void* TEXTO;

// Inicializa um objeto texto com os parametros fornecidos.
TEXTO inicializaTexto(int id, double x, double y, char* corp, char* corb, char* string, char a);

// Retorna o ID associado ao texto especificado.
int getIdtexto(TEXTO texto);

// Retorna a coordenada X associada ao texto especificado.
double getXtexto(TEXTO texto);

// Retorna a coordenada Y associada ao texto especificado.
double getYtexto(TEXTO texto);

// Retorna a string associada ao texto especificado.
char* getStringtexto(TEXTO texto);

// Retorna a cor de preenchimento associada ao texto especificado.
char* getStringcorp(TEXTO texto);

// Retorna a cor da borda associada ao texto especificado.
char* getStringcorb(TEXTO texto);

// Retorna o caractere 'a' associado ao texto especificado.
char getStringA(TEXTO texto);

// Define a coordenada X do texto especificado.
void setXtexto(TEXTO texto, double x);

// Define a coordenada Y do texto especificado.
void setYtexto(TEXTO texto, double y);

// Define a string do texto especificado.
void setStringtexto(TEXTO texto, char* txt);

// Define a cor de preenchimento do texto especificado.
void setStringCorp(TEXTO texto, char* corp);

// Define a cor da borda do texto especificado.
void setStringCorb(TEXTO texto, char* corb);

// Define o caractere 'a' do texto especificado.
void setStringA(TEXTO texto, char a);

// Retorna o tamanho do objeto Texto.
long int SizeTexto();

#endif