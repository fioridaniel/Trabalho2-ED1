#ifndef ARQSVG__
#define ARQSVG__


/*
  Provê operações para escrita de arquivos básicos no formato SVG.

  O arquivo deve ser criado por abreEscritaSvg. A seguir, círculos,
retângulos, linhas e textos podem ser acrescentados ao arquivo.

  Por fim, o arquivo deve ser fechado por meio da operacao fechaSvg.
Note que nao existem operacoes para modificacao de um arquivo existente.

  Para mais detalhes sobre o formato SVG, consulte a especificação do
formato ou tutoriais, como:

     https://developer.mozilla.org/pt-BR/docs/Web/SVG/Tutorial
 */

typedef void* ArqSvg;

/*
  Cria o arquivo "fn" para escrita. Substitui o arquivo, caso exista.
  Retorna NULL, caso nao tenha sido possivel criar arquivo.
 */
ArqSvg abreEscritaSvg(char *fn);

/*
   Insere uma circunferencia com centro em (xc,yc) de raio r. Atributos de formatacao
(cores, largura de bordas, etc) podem ser informados pela string deco (atribuir NULL, 
caso nao queira atribuir decoracao).
 */
void escreveCirculoSvg(ArqSvg fsvg, double xc, double yc, double r, char *deco);

/*
   Insere um retangulo com canto inferior esquerdo  em (x,y), de largura larg e altura alt. 
Atributos de formatacao (cores, largura de bordas, etc) podem ser informados pela string 
deco (atribuir NULL, caso nao queira atribuir decoracao).
 */
void escreveRetanguloSvg(ArqSvg fsvg, double x, double y, double larg, double alt, char *deco);

/*
   Insere uma linha com extremidades em (x1,y1) e (x2,y2). 
Atributos de formatacao (cores, largura de bordas, etc) podem ser informados pela string 
deco (atribuir NULL, caso nao queira atribuir decoracao).
 */
void escreveLinhaSvg(ArqSvg fsvg, double x1, double y1, double x2, double y2, char *deco);


/*
  Insere no arquivo svg o texto txt na coordenada (x,y).
Atributos de formatacao (cores, fonte, etc) podem ser informados pela string 
deco (atribuir NULL, caso nao queira atribuir decoracao).
 */
void escreveTextoSvg(ArqSvg fsvg, double x, double y, char *txt, char *decoTxt);

/* Fecha o arquivo fsvg. */
void fechaSvg(ArqSvg fsvg);

#endif