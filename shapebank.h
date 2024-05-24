#ifndef _SHAPEBANK_
#define _SHAPEBANK_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "registrador.h"
#include "arqsvg.h"
#include "garbage.h"

typedef void* Forma;
typedef void* ShapeBank;

/*
    O shapebank eh uma colecao de itens, em que 
    cada bloco de memoria pode ou nao armazenar um item.
    Por convencao, o tamanho padrao do shapebank sera tratado
    como 100, caso quiser altera-lo, eh necessario utilizar
    o comando -nx N, onde N eh um inteiro correspondente ao tamanho desejado. 
*/

void* InicializaShapeBank(int nx);

/*
    Uma forma eh carregada na posicao id do shapebank.
*/
void DepositarNoshape(ShapeBank shapebank, Forma forma, int id);

/*
    Uma forma eh carregada na posicao mem do shapebank,
    porem os dados vem do registrador.
*/
void DepositarNoshape_Reg(ShapeBank shapebank, Forma forma, int mem, char tipo);

/*
    Copia a forma da posicao mem do shapebank,
    e retorna.
*/
Forma copiaDoshape(ShapeBank shapebank, int mem);

/*
    Remove a forma da posicao mem do shapebank.
*/
void removerFormaShape(ShapeBank shapebank, int mem);

/*
    Verifica o tipo da forma carregada
    na posicao mem do shapebank, printa 
    os atributos de cada forma, e passa
    essas informacoes pro arquivo svg final.
*/
void ShapeBankSvgFinal(Forma forma, char tipo_forma, FILE* fsvg);

/*
    Retorna o tipo da forma carregada
    na posicao mem do shapebank.
*/
char verificarTipoShape(ShapeBank shapebank, int mem);

/*
    Passa os atributos do objeto
    carregado na posicao mem do shapebank
    para o arquivo txt de saida.
*/
void ReportarTxtShape(ShapeBank shapebank, int mem, FILE* txt);

/*
    Recebe por parametro o objeto que guarda a forma, com
    seu respectivo tipo e o numero de referencias, e retorna
    o id daquela forma.
*/
int ElseifId(Forma forma);


#endif