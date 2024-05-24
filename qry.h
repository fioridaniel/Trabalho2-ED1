#ifndef _QRY_
#define _QRY_

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "leArquivo.h"
#include "registrador.h"
#include "shapebank.h"
#include "pilha.h"
#include "garbage.h"
#include "lista.h"

typedef void* ShapeBank;

/*
    ATENCAO: PARAMETRO PARA INDICAR
    UMA STACK, SO PODE SER EM LETRA MAIUSCULA, 
    A, B, C ou D. PARAMETRO PARA INDICAR UM 
    REGISTRADOR, SO PODE ASSUMIR ESSES VALORES
    EM MINUSCULO (r1, r2, r3, r4 ou r5).
*/

/*
    Funcao que le o arqQry, responsavel por interpretar
    corretamente todos os comandos, ld, sto, push ... etc.
    Recebe como parametro o arquivo com extensao .qry, e em algumas funcoes
    coloca dados de saida no arqTxtSaida
*/
void lerQry(ShapeBank shapebank, GcCore gccore, FILE* arqQry, FILE * arqTxtSaida, int tamSt, int gc);

/*
    Funcao responvasel por receber a string que
    identifica o registrador, (r1, r2, r3, r4, r5)
    e retorna o inteiro associado a ele.
*/
int getRg(char rg[]);

/*
    Retorna o inteiro associado ao
    identificador da stack.
*/
int getSt(char st);

/*
    Comando ld:
    Parametros = string relacionada ao registrador 
    (r1, r2, r3, r4, ou r5), e um inteiro mem
    correspondente a posicao do shapebank. 
    Cria uma copia da figura armazenada na posicao 
    mem do shapebank, e deposita no registrador selecionado.
*/

/*
    Comando sto:
    Parametros = string relacionada ao registrador 
    (r1, r2, r3, r4, ou r5) e um inteiro mem
    correspondente a posicao do shapebank. Cria uma 
    Cria uma copia da figura armazenada no registrador
    selecionado, e deposita na posicao mem do shape.
*/

/*
    Comando push:
    Parametros = string relacionada ao registrador 
    (r1, r2, r3, r4, ou r5) e um char relacionado a 
    stack (A, B, C ou D). Empilha na stack selecionada
    uma copia da forma do registrador rg. Alem disso, 
    os atributos da forma empilhada vao para a saida textual.
*/

/*
    Comando pop:
    Parametros = string relacionada ao registrador 
    (r1, r2, r3, r4, ou r5) e um char relacionado a 
    stack (A, B, C ou D). Desempilha uma forma da 
    stack st, e carrega no registrador rg. Os atributos
    da forma desempilha vao para a saida txt.
*/

/*
    Comando mvs:
    Parametros = dois chars relacionados a 
    stack (A, B, C ou D). Desempilha sequencialmente as 
    figuras da pilha st1 empilhando-as na pilha st2
*/

/*
    Comando ca:
    Parametros = duas strings relacionadas ao registrador 
    (r1, r2, r3, r4, ou r5), um double referente a um x
    e outro a um y, e duas stirngs referentes a cor da 
    borda (corb) e cor do preenchimento (corp). Modifica 
    os atributos de posição, cor de borda, cor de preenchimento
    da figura que está no registrador rg1 e coloca o resultado 
    no registrador rg2 (rg1 e rg2 podem ser os mesmos registradores). 
    Os valores dx e dy deslocam a figura nos eixos x e y. Os valores 
    de dx, dy, corb, corp podem ser substituídos por -, indicando que 
    o respectivo atributo não deve ser modificado.
*/

/*
    Comando del:
    Parametros = Inteiro mem correspondente a 
    posicao do shapebank. Remove a figura da posicao
    mem do shapebank, e reporta os atributos no txt
    de saida.
*/

/*
    Comando prts:
    Parametros = char relacionado a 
    stack (A, B, C ou D). Informa os atributos
    de todos os elementos da stack selecionada,
    (do topo para a base) bem como o numero 
    de elementos. Reporta os atributos no txt
    de saida.
*/

/*
    Comando tp:
    Parametros = char relacionado a 
    stack (A, B, C ou D), inteiro mem 
    correspondente a posicao do shapebank,
    dois doubles, (um x e um y), e uma 
    string texto. Verifica se a pilha st está vazia. 
    Caso afirmativo, armazena na posição mem do
    Shape Bank, o texto “VAZIA” concatenado
    com txt. O texto produzido possui
    coordenada (x,y), ancora ‘i’, cor borda:
    #550000, cor preenchimento: #FF0000
*/

#endif