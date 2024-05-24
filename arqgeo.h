#ifndef _ARQGEO2_
#define _ARQGEO2_

#include "garbage.h"
#include "lista.h"
/*
    ATENCAO, OS CHARS CORRESPONDENTES
    AS FORMAS SEMPRE SERAO MINUSCULOS.
    c, r, l e t. circulo, retangulo, 
    linha e texto respectivamente.
*/

/*
    Funcao que le o arqGeo, responsavel por interpretar
    corretamente todos os comandos, r, c, l, e ts.
    Recebe como parametro um arquivo com extensao .geo, e um arquivo com extensao .svg. 
    Imprime os resultados de cada comando no arqSvgInicial.
*/
void ComandosGeo(void* shapebank, GcCore gccore, FILE* arqGeo, FILE * arqSvgInicial);


/*
    Comando c:
    Parametros = inteiro correspondente a posicao
    da memoria, double x, y e r (ancora). strings
    corp e corb. (cor preenchimento e borda).
    Carrega o círculo na posição i da memória:
    (x,y) é o centro do círculo; r, seu raio.
*/

/*
    Comando r:
    Parametros = inteiro correspondente a posicao
    da memoria, double x, y (ancora), double h, w
    (altura e largura). strings corp e corb. 
    (cor preenchimento e borda).Carrega o retângulo 
    na posição i da memória: w é a largura do retângulo
    e h, a altura.
*/

/*
    Comando l:
    Parametros = inteiro correspondente a posicao
    da memoria, double (x1, y1),(x2, y2) (ancora), e 
    uma string cor. Carrega a linha na posição i da memória:
    com extremidades nos pontos (x1,y1) e
    (x2,y2), com a cor especifiicada.
*/

/*
    Comando t:
    Parametros = inteiro correspondente a posicao
    da memoria, double x e y, e um char minusculo i,
    determinante da ancora do texto. strings corp e corb. 
    (cor preenchimento e borda) Carrega o texto txto 
    na posição i da memória: nas coordenadas (x,y) e com a
    cores indicadas. O
    parâmetro a determina a posição da âncora
    do texto: i, no início; m, no meio, f, no
    fim. O texto txto é o último parâmetro do
    comando. Pode incluir espaços em branco e
    se estende até o final da linha.
*/

/*
    Comando ts:
    Paramtros = tres strings correspondetes
    aos atributos do texto : fFamily fWeight fSize.
    Muda o estilo dos textos (comando t) subsequentes.
    font family: sans (sans-serif), serif, cursive;
    font weight ( n: normal, b: bold, b+: bolder,
    l: | lighter)
*/

#endif