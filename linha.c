#include "linha.h"
#include "shapebank.h"

typedef struct {
    int id;
    double x1, y1, x2, y2;
    char* cor;    
    char tipo;
} Linha;

LINHA inicializaLinha(int id, double x1, double y1, double x2, double y2, char* cor) {
    Linha* l = (Linha*)malloc(sizeof(Linha));
    if (l == NULL) {
        printf("falha ao alocar memoria para a linha...saindo do programa.\n");
        exit(1);
    }

    l->id = id;
    l->x1 = x1;
    l->y1 = y1;
    l->x2 = x2;
    l->y2 = y2;

    // Alocar memória para a cor e copiar a string
    l->cor = (char*)malloc(strlen(cor) + 1);
    if (l->cor == NULL) {
        // Lidar com falha de alocação de memória
        free(l);
        exit(1);
    }
    strcpy(l->cor, cor);

    l->tipo = 'l';
    return((Linha*)l);
}

int getIdlinha(LINHA l) {
    l = GetFormaGarbage(l);
    return((Linha*)l)->id;
}

double getX1(LINHA l) {
    l = GetFormaGarbage(l);
    return((Linha*)l)->x1;

}

double getY1(LINHA l) {
    l = GetFormaGarbage(l);
    return((Linha*)l)->y1;
}

double getX2(LINHA l) {
    l = GetFormaGarbage(l);
    return((Linha*)l)->x2;
}

double getY2(LINHA l) {
    l = GetFormaGarbage(l);
    return((Linha*)l)->y2;
}

char* getCorLIN(LINHA l) {
    l = GetFormaGarbage(l);
    return((Linha*)l)->cor;
}

void setX1(LINHA l, double X1) {
    l = GetFormaGarbage(l);
    ((Linha*)l)->x1 = X1;
}

void setY1(LINHA l, double Y1) {
    l = GetFormaGarbage(l);
    ((Linha*)l)->y1 = Y1;
}

void setX2(LINHA l, double X2) {
    l = GetFormaGarbage(l);
    ((Linha*)l)->x2 = X2;
}

void setY2(LINHA l, double Y2) {
    l = GetFormaGarbage(l);
    ((Linha*)l)->y2 = Y2;
}

void setCorLIN(LINHA l, char *cor) {
    l = GetFormaGarbage(l);
    Linha* linha = (Linha*)l;
    free(linha->cor);
    linha->cor = (char*)malloc(strlen(cor) + 1);
    if (linha->cor == NULL) {
        printf("FALHA AO ALOCAR MEMORIA PARA cor.\n");
        exit(1);
    }
    strcpy(linha->cor, cor);
}

long int SizeLinha() {
    return sizeof(Linha);
}