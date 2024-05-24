#include "retangulo.h"
#include "shapebank.h"


typedef struct {
    int id;
    double x, y, h, w;
    char* corp, *corb;
    char tipo;
} Retangulo;

RETANGULO inicializaRetangulo(int id, double x, double y, double w, double h, char* corb, char* corp) {
    Retangulo* ret = (Retangulo*)malloc(sizeof(Retangulo));
    if (ret == NULL) {
        printf("FALHA AO ALOCAR MEMORIA PARA O RETANGULO.\n");
        exit(1);
    }
    
    ret->id = id;
    ret->x = x;
    ret->y = y;
    ret->w = w;
    ret->h = h;

    // Alocar memória para corp e copiar a string
    ret->corp = (char*)malloc(strlen(corp) + 1);
    if (ret->corp == NULL) {
        printf("FALHA AO ALOCAR MEMORIA PARA corp.\n");
        free(ret);
        exit(1);
    }
    strcpy(ret->corp, corp);

    // Alocar memória para corb e copiar a string
    ret->corb = (char*)malloc(strlen(corb) + 1);
    if (ret->corb == NULL) {
        printf("FALHA AO ALOCAR MEMORIA PARA corb.\n");
        free(ret->corp);
        free(ret);
        exit(1);
    }
    strcpy(ret->corb, corb);

    ret->tipo = 'r';
    return ((Retangulo*)ret);
}

int getIdRetangulo(RETANGULO ret) {
    ret = GetFormaGarbage(ret);
    return ((Retangulo*)ret)->id;
}

double getH(RETANGULO ret) {
    ret = GetFormaGarbage(ret);
    return ((Retangulo*)ret)->h;
}

double getW(RETANGULO ret) {
    ret = GetFormaGarbage(ret);
    return ((Retangulo*)ret)->w;
}

double getX(RETANGULO ret) {
    ret = GetFormaGarbage(ret);
    return ((Retangulo*)ret)->x;
}

double getY(RETANGULO ret) {
    ret = GetFormaGarbage(ret);
    return ((Retangulo*)ret)->y;
}

char* getCorpRET(RETANGULO ret) {
    ret = GetFormaGarbage(ret);
    return ((Retangulo*)ret)->corp;
}

char* getCorbRET(RETANGULO ret) {
    ret = GetFormaGarbage(ret);
    return ((Retangulo*)ret)->corb;
}

void setX(RETANGULO ret, double X) {
    ret = GetFormaGarbage(ret);
    ((Retangulo*)ret)->x = X;
}

void setY(RETANGULO ret, double Y) {
    ret = GetFormaGarbage(ret);
    ((Retangulo*)ret)->y = Y;
}

void setW(RETANGULO ret, double W) {
    ret = GetFormaGarbage(ret);
    ((Retangulo*)ret)->w = W;
}

void setH(RETANGULO ret, double H) {
    ret = GetFormaGarbage(ret);
    ((Retangulo*)ret)->h = H;
}

void setCorpRET(RETANGULO ret, char* corp) {
    ret = GetFormaGarbage(ret);
    Retangulo* retangulo = (Retangulo*)ret;
    free(retangulo->corp); 
    retangulo->corp = (char*)malloc(strlen(corp) + 1);
    if (retangulo->corp == NULL) {
        printf("FALHA AO ALOCAR MEMORIA PARA corp.\n");
        exit(1);
    }
    strcpy(retangulo->corp, corp);
    printf("teste %s\n", retangulo->corp);
}

void setCorbRET(RETANGULO ret, char* corb) {
    ret = GetFormaGarbage(ret);
    Retangulo* retangulo = (Retangulo*)ret;
    free(retangulo->corb); 
    retangulo->corb = (char*)malloc(strlen(corb) + 1);
    if (retangulo->corb == NULL) {
        printf("FALHA AO ALOCAR MEMORIA PARA corb.\n");
        exit(1);
    }
    strcpy(retangulo->corb, corb);
    printf("teste %s\n", retangulo->corb);
}

long int SizeRetangulo() {
    return sizeof(Retangulo);
}