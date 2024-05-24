#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "garbage.h"
#include "shapebank.h"
#include "lista.h"

typedef void* Forma;

typedef struct Node {
    Forma forma;
    int nextIndex; 
    int prevIndex; 
} Node;

typedef struct Lista {
    int capacidade;
    Node* nodes;  
    int headIndex;
    int tailIndex;  
    int nextFreeIndex;  
} Lista;

LISTA createLista(int capacidade) {
    Lista* newList = (Lista*)malloc(sizeof(Lista));
    if (newList == NULL) {
        printf("ALOCACAO DE MEMORIA CAPOTOU!\n");
        exit(1);
    }
    newList->capacidade = 2 * capacidade;
    newList->nodes = (Node*)malloc(newList->capacidade * sizeof(Node));
    if (newList->nodes == NULL) {
        printf("ALOCACAO DE MEMORIA CAPOTOU!\n");
        free(newList); 
        exit(1);
    }
    
    for (int i = 0; i < newList->capacidade; i++) {
        newList->nodes[i].forma = NULL;
        newList->nodes[i].nextIndex = i + 1;  
        newList->nodes[i].prevIndex = -1; 
    }
    newList->nodes[newList->capacidade - 1].nextIndex = -1; 

    newList->headIndex = -1;  
    newList->tailIndex = -1;  
    newList->nextFreeIndex = 0;  

    return newList;
}

void insertNode(LISTA lista, Forma forma) {
    Lista* list = (Lista*)lista;
    if (list->nextFreeIndex == -1) {
        printf("Lista esta cheia, impossivel inserir\n");
        return;
    }
    int newIndex = list->nextFreeIndex;
    list->nodes[newIndex].forma = forma;
    list->nextFreeIndex = list->nodes[newIndex].nextIndex; 
    if (list->headIndex == -1) {  
        list->headIndex = newIndex;
        list->tailIndex = newIndex;
    } else {
        list->nodes[newIndex].prevIndex = list->tailIndex;
        list->nodes[list->tailIndex].nextIndex = newIndex;
        list->tailIndex = newIndex;
    }
}

Forma PercorreLista(LISTA lista) {
    Lista* list = (Lista*)lista;
    int currentIndex = list->headIndex;

    while (currentIndex != -1) {
        Forma forma = list->nodes[currentIndex].forma; 

        if (forma != NULL) {
            int referencia = GetRef(forma);
            if (referencia == 0) {
                removeNode(list, currentIndex);
                return forma;
            }
        }

        currentIndex = list->nodes[currentIndex].nextIndex;
    }
    return NULL;
}

void removeNode(LISTA list, int index) {
    Lista* lista = (Lista*)list;

    if (ListaVazia(lista)) {
        printf("Lista esta vazia, impossivel remover\n");
        exit(1); 
    }

    if (index < 0 || index >= lista->capacidade) {
        printf("Indice invalido, impossivel remover\n");
        exit(1); 
    }

    if (lista->headIndex == index) { 
        lista->headIndex = lista->nodes[index].nextIndex;
        if (lista->headIndex != -1) {
            lista->nodes[lista->headIndex].prevIndex = -1;
        }
    } else if (lista->tailIndex == index) {
        lista->tailIndex = lista->nodes[index].prevIndex;
        if (lista->tailIndex != -1) {
            lista->nodes[lista->tailIndex].nextIndex = -1;
        }
    } else {
        lista->nodes[lista->nodes[index].prevIndex].nextIndex = lista->nodes[index].nextIndex;
        lista->nodes[lista->nodes[index].nextIndex].prevIndex = lista->nodes[index].prevIndex;
    }

    lista->nodes[index].forma = NULL;
    lista->nodes[index].nextIndex = lista->nextFreeIndex; 
    lista->nextFreeIndex = index; 
}

bool ListaCheia(LISTA list) {
    Lista* lista = (Lista*)list;
    if (lista->nextFreeIndex == -1) {
        printf("lista esta cheia.\n");
        return true;
    }
    return false;
}

bool ListaVazia(LISTA list) {
    Lista* lista = (Lista*)list;
    if (lista->headIndex == -1) {
        printf("lista esta vazia.\n");
        return true;
    }
    return false;
}

