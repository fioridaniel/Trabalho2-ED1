#ifndef _REGISTRADOR2_
#define _REGISTRADOR2_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "shapebank.h"

/*
    Os registradores sao bancos de informacoes, no qual cada
    registrador armazena um item e seu atributos. 
    
    Informacoes do shapebank conseguem ser carregadas para o 
    registrador, e vice versa, assim como informacoes do 
    registrador podem ser passadas para as pilhas e vice versa. 
*/

/*
    Nesse projeto, Forma serve para acessar as informacoes
    de qualquer uma das formas (circulo, retangulo, linha e texto).
    As formas estao associadas a um char identificador do tipo da
    forma, em que os chars c, r, l e t (SO PODEM SER MINUSCULOS) estao
    associados a circulo, retangulo, linha e texto respectivamente.
*/
typedef void* Forma;

/*
    Copia a forma armazenada na posicao do registrador 
    mem, e a retorna
*/
Forma CopiaDoRegistrador(int mem);

/*
    Libera a forma armazenada no registrador
    de posicao mem, e retorna o tipo da forma
    que estava armazenada nele.
*/
//char FreeRegistrador(int mem);

/*
    Deposita uma forma na posicao mem 
    do registrador.
*/
void CarregaRegistrador(Forma estrutura, int mem);

/*
    Retorna o tipo da forma armazenada
    na posicao mem do registrador.
*/
char VerificarTipoRegistrador(int mem);


#endif