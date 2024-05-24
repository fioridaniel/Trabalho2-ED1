#ifndef _PILHA_
#define _PILHA_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "garbage.h"

typedef void *Item;
typedef void *Pilha;


/**
   Uma pilha e' uma colecao de itens que sao acessados segundo a disciplina LIFO
(Last In First Out). Isto e', itens sao acrescentados `a e retirados da colecao de
forma que o ultimo elemento acrescentado (topo da pilha) e' o primeiro a ser retirado.
Uma pilha sem itens e denominada pilha vazia.
   Uma pilha pode ser criada com uma capacidade maxima, i.e., um numero maximo de
itens que a pilha pode armazenar.
*/  

/**
   Cria uma pilha vazia que pode conter, no maximo, Capac elementos, ou -1 para pilha
   sem limitacao de capacidade.
   
*/
Pilha createPilha(int Capac);

/**
  Retorna verdadeiro se a pilha p esta' vazia;
  falso, caso contrario.
 */
bool isEmpty(Pilha p);

/**
  Retorna verdadeiro se a pilha p esta' cheia;
  falso, caso contrario.
 */
bool isFull(Pilha p);

/**
  Empilha no elemento i na pilha P.
  A pilha nao pode estar cheia. O caractere tipo 
  associa o tipo da forma que esta sendo empilhada.
  Pode assumir c, r, l e t, indicando circulo, retangulo
  linha e texto respectivamente.
*/
void push(Pilha p, Item i); 

/**
  Retira o elemento do topo da pilha p.
  A pilha nao pode estar vazia.
 */
Item pop(Pilha p);

/**
   Retorna o numero de elementos armazenados 
   na pilha. Retorna, -1 caso a pilha nao
   tenha tenha limitacao de capacidade.
 */
int size(Pilha p);

/**
   Libera todos os recursos alocados por criaPilha, ou
seja, p nao deve ser mais utilizada.
 */
void destroy(Pilha p);

/**
   Retorna o tipo da forma do ultimo 
   elemento empilhado da pilha. 
*/
char VerificaTipoStack(Pilha p);

/**
   Retorna a forma armazenada no
   ultimo Node empilhado.
*/
Item retornaItem(Pilha p);

/**
   Mostra na saída textual a
representação corrente da Pilha, informando
o número de elementos e os atributos de 
cada um dos elementos (do topo para base), 
sem desempilhá-lhos. Informa o tipo do elemento 
e seus atributos.
*/
void Prts(FILE* txt, Pilha p);

/**
   Informa os atributos do elemento a ser 
   empilhado na saida textual, bem como os
   atributos do elemento desempilhado.
*/
void PushPopTxt(FILE* txt, Pilha p);

#endif