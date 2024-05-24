#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "texto.h"
#include "shapebank.h"


//typedef void* TEXTO;

typedef struct {
    int id;
    double x, y;
    char* corp, *corb, *txt;
    char tipo, a;
} Texto;

TEXTO inicializaTexto(int id, double x, double y, char* corp, char* corb, char* string, char a) {
    Texto* texto = (Texto*)malloc(sizeof(Texto));
    if (texto == NULL) {
        printf("FALHA AO ALOCAR MEMORIA PARA O TEXTO.\n");
        exit(1);
    }
    
    texto->id = id;
    texto->x = x;
    texto->y = y;

    // Alocar memória para corp e copiar a string
    texto->corp = (char*)malloc(strlen(corp) + 1);
    if (texto->corp == NULL) {
        printf("FALHA AO ALOCAR MEMORIA PARA corp.\n");
        free(texto);
        exit(1);
    }
    strcpy(texto->corp, corp);

    // Alocar memória para corb e copiar a string
    texto->corb = (char*)malloc(strlen(corb) + 1);
    if (texto->corb == NULL) {
        printf("FALHA AO ALOCAR MEMORIA PARA corb.\n");
        free(texto);
        exit(1);
    }
    strcpy(texto->corb, corb);

    // Alocar memória para string e copiar a string
    texto->txt = (char*)malloc(strlen(string) + 1);
    if (texto->txt == NULL) {
        printf("FALHA AO ALOCAR MEMORIA PARA string.\n");
        free(texto->corb);
        free(texto->corp);
        free(texto);
        exit(1);
    }
    strcpy(texto->txt, string);

    texto->a = a;
    texto->tipo = 't';
    return ((Texto*)texto);
}


int getIdtexto(TEXTO texto) {
    texto = GetFormaGarbage(texto);
    return ((Texto*)texto)->id;
}

double getXtexto(TEXTO texto) {
    texto = GetFormaGarbage(texto);
    return ((Texto*)texto)->x;
}

double getYtexto(TEXTO texto) {
    texto = GetFormaGarbage(texto);
    return ((Texto*)texto)->y;
}

char* getStringtexto(TEXTO texto) {
    texto = GetFormaGarbage(texto);
    return ((Texto*)texto)->txt;
}

char* getStringcorp(TEXTO texto) {
    texto = GetFormaGarbage(texto);
    return ((Texto*)texto)->corp;
}

char* getStringcorb(TEXTO texto) {
    texto = GetFormaGarbage(texto);
    return ((Texto*)texto)->corb;
}

char getStringA(TEXTO texto) {
    texto = GetFormaGarbage(texto);
    return ((Texto*)texto)->a;
}

void setXtexto(TEXTO texto, double x) {
    texto = GetFormaGarbage(texto);
    ((Texto*)texto)->x = x;
}

void setYtexto(TEXTO texto, double y) {
    texto = GetFormaGarbage(texto);
    ((Texto*)texto)->y = y;
}

void setStringtexto(TEXTO texto, char* txt) {
    texto = GetFormaGarbage(texto);
    Texto* t = (Texto*)texto;
    // Libera a string anterior de txt
    free(t->txt); 
    // Aloca memória para a nova string txt e a copia
    t->txt = (char*)malloc(strlen(txt) + 1);
    if (t->txt == NULL) {
        printf("FALHA AO ALOCAR MEMORIA PARA txt.\n");
        exit(1);
    }
    strcpy(t->txt, txt);
}

void setStringA(TEXTO texto, char a) {
    texto = GetFormaGarbage(texto);
    Texto* t = (Texto*)texto;
    t->a = a;
}

void setStringCorp(TEXTO texto, char* corp) {
    texto = GetFormaGarbage(texto);
    Texto* t = (Texto*)texto;
    // Libera a string anterior de corp
    free(t->corp); 
    // Aloca memória para a nova string corp e a copia
    t->corp = (char*)malloc(strlen(corp) + 1);
    if (t->corp == NULL) {
        printf("FALHA AO ALOCAR MEMORIA PARA corp.\n");
        exit(1);
    }
    strcpy(t->corp, corp);
}

void setStringCorb(TEXTO texto, char* corb) {
    texto = GetFormaGarbage(texto);
    Texto* t = (Texto*)texto;
    // Libera a string anterior de corb
    free(t->corb); 
    // Aloca memória para a nova string corb e a copia
    t->corb = (char*)malloc(strlen(corb) + 1);
    if (t->corb == NULL) {
        printf("FALHA AO ALOCAR MEMORIA PARA corb.\n");
        exit(1);
    }
    strcpy(t->corb, corb);
}

long int SizeTexto() {
    return sizeof(Texto);
}