#include "circulo.h"
#include "shapebank.h"

typedef struct {
    int id;
    double x, y, r;
    char *corp, *corb;
    char tipo;
} Circulo;

CIRCULO inicializaCirculo(int id, double x, double y, double r,char *corp, char *corb) {
    Circulo* cir = (Circulo*)malloc(sizeof(Circulo));    
    if (cir == NULL) {
        printf("FALHA AO ALOCAR MEMORIA PARA O CIRCULO.\n");
        exit(1);
    }
    
    cir->id = id;
    cir->x = x;
    cir->y = y;
    cir->r = r; 

    // Alocar memória para corp e copiar a string
    cir->corp = (char*)malloc(strlen(corp) + 1);
    if (cir->corp == NULL) {
        printf("FALHA AO ALOCAR MEMORIA PARA corp.\n");
        free(cir);
        exit(1);
    }
    strcpy(cir->corp, corp);

    // Alocar memória para corb e copiar a string
    cir->corb = (char*)malloc(strlen(corb) + 1);
    if (cir->corb == NULL) {
        printf("FALHA AO ALOCAR MEMORIA PARA corb.\n");
        free(cir->corp);
        free(cir);
        exit(1);
    }
    strcpy(cir->corb, corb);

    cir->tipo = 'c';
    return ((Circulo*)cir);
}

int getIdCirculo(CIRCULO cir) {
    cir = GetFormaGarbage(cir);
    return ((Circulo*)cir)->id;
}

double getRaio(CIRCULO cir) {
    cir = GetFormaGarbage(cir);
    return ((Circulo*)cir)->r;
}

double getXc(CIRCULO cir) {
    cir = GetFormaGarbage(cir);
    return ((Circulo*)cir)->x;
} 

double getYc(CIRCULO cir) {
    cir = GetFormaGarbage(cir);
    return ((Circulo*)cir)->y;
}

char* getCorpCIR(CIRCULO cir) {
    cir = GetFormaGarbage(cir);
    return ((Circulo*)cir)->corp;
}

char* getCorbCIR(CIRCULO cir) {
    cir = GetFormaGarbage(cir);
    return ((Circulo*)cir)->corb;
}

void setXc(CIRCULO cir, double xc) {
    cir = GetFormaGarbage(cir);
    ((Circulo*)cir)->x = xc;
}

void setYc(CIRCULO cir, double yc) {
    cir = GetFormaGarbage(cir);
    ((Circulo*)cir)->y = yc;
}

void setCorpCIR(CIRCULO cir, char* corp) {
    cir = GetFormaGarbage(cir);
    Circulo* circle = (Circulo*)cir;
    // Libera a string anterior de corp
    free(circle->corp);
    // Aloca memória para a nova string corp e a copia
    circle->corp = (char*)malloc(strlen(corp) + 1);
    if (circle->corp == NULL) {
        printf("FALHA AO ALOCAR MEMORIA PARA corp.\n");
        exit(1);
    }
    strcpy(circle->corp, corp);
}

void setCorbCIR(CIRCULO cir, char* corb) {
    cir = GetFormaGarbage(cir);
    Circulo* circle = (Circulo*)cir;
    // Libera a string anterior de corb
    free(circle->corb);
    // Aloca memória para a nova string corb e a copia
    circle->corb = (char*)malloc(strlen(corb) + 1);
    if (circle->corb == NULL) {
        printf("FALHA AO ALOCAR MEMORIA PARA corb.\n");
        exit(1);
    }
    strcpy(circle->corb, corb);
}

long int SizeCirculo() {
    return sizeof(Circulo);
}


