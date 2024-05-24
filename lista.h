#ifndef _LISTA_
#define _LISTA_

typedef void* LISTA;
typedef void* NO;

/*
    Uma lista eh uma colecao de itens que podem ser acessados 
    de maneira livre. Isso quer dizer que nao existe restricao
    quanto ao elemento que voce deseja acessar. Em outras palavras, 
    você pode acessar qualquer elemento da lista independentemente
    da sua posição dentro da coleção.
*/

/*
    Cria uma lista com a capacidade especificada.
*/
LISTA createLista(int capacidade);

/*
    Insere a forma recebida como parametro 
    na proxima posicao livre da lista.
*/
void insertNode(LISTA list, Forma forma);

/*
    Remove o node da posicao index da lista.
*/
void removeNode(LISTA lista, int index);

/*
    Percorre a lista, em busca dos itens que 
    possuem referencia zero. Assim que encontrados,
    a funcao retorna o item em questao.
*/
Forma PercorreLista(LISTA lista);

/*
    Retorna verdadeiro caso
    a lista esteja cheia. Falso
    caso contrario.
*/
bool ListaCheia(LISTA lista);

/*
    Retorna verdadeiro caso
    a lista esteja vazia. Falso
    caso contrario.
*/
bool ListaVazia(LISTA lista);

#endif