#include "pilha.h"

//typedef void* Pilha
//typedef void* Item

/*
Quando você passa um argumento para uma função em C, por padrão, é feita uma cópia do valor desse argumento.
Isso significa que qualquer alteração feita dentro da função não afetará o valor original fora dela. 
Isso é chamado de passagem por valor.
Por outro lado, ao passar um ponteiro para uma função, você está passando o endereço de memória da variável original. 
Isso permite que a função modifique o valor da variável original, pois ela está operando diretamente na localização de memória onde a variável original está armazenada. 
Isso é chamado de passagem por referência.
*/


//É PRECISO ATUALIZAR OS PARAMETROS DAS FUNÇOES PARA FAZER AS PASSAGENS POR REFERENCIA

//TALVEZ USAR O PARAMETRO PILHA p COMO UM IDENTIFICADOR DA PILHA, DO TIPO INT, ASSIM, TEREI StPilha[p - 1] = cabeça da pilha p - 1.

typedef struct Node {
    Item forma;
    struct Node* next;
} Node;

typedef struct StPilha {
    int capacidade;
    struct Node *topo;
} StPilha;

Pilha createPilha(int Capac) {
    StPilha* pilha = (StPilha*)malloc(sizeof(StPilha));

    if(Capac == -1)
    {
        Capac = 10000;
    }

    pilha->capacidade = Capac;
    pilha->topo = NULL;
    return pilha;
}

bool isEmpty(Pilha p) {
    StPilha* pilha = (StPilha*)p;

    if(pilha->topo == NULL) {
       // printf("Pilha esta vazia.\n");
        return true;
    } else {
        //printf("Pilha nao esta vazia.\n");
        return false;
    }
}

bool isFull(Pilha p) {
    int cont = 0;
    StPilha* pilha = (StPilha*)p;
    Node* aux = (Node*)pilha->topo;

    while(aux != NULL) {
        aux = aux->next;
        cont++;
    }
    if(cont == pilha->capacidade) {
        //printf("Pilha esta cheia.\n");
        return true;
    } else {
        //printf("Pilha nao esta cheia.\n");
        return false;
    }
}

void push(Pilha p, Item i) { //colocar muito bem documentado no tad, informar quais tipo de char pode.
    StPilha* pilha = (StPilha*)p;
    
    if (isFull(p)) {
        printf("Pilha cheia. Impossível inserir.\n");
        return;
    }

    Node* novo = (Node*)malloc(sizeof(Node));

    if(novo == NULL) {
        printf("Erro ao alocar memoria...saindo\n");
        exit(1);
    }

    novo->forma = i;
    novo->next = pilha->topo;
    pilha->topo = novo;
    printf("Elemento depositado com sucesso na pilha.\n");
}

Item pop(Pilha p) {
    StPilha* pilha = (StPilha*)p;

    if (isEmpty(p)) {
        printf("Pilha vazia. Impossível remover.\n");
        return NULL; // Indicate error or empty stack
    }

    Node* aux = pilha->topo;
    Item item = aux->forma; // Store the value to be returned
    pilha->topo = aux->next;
    free(aux);
    printf("Item retirado com sucesso.\n"); // Print appropriate message
    return item;
}

int size(Pilha p) {
    StPilha* pilha = (StPilha*)p;
    Node* aux = pilha->topo;
    int cont = 0;

    while(aux != NULL) {
        aux = aux->next;
        cont++;
    }
    return cont;
}

char VerificaTipoStack(Pilha p) {
    StPilha* pilha = (StPilha*)p;

    Node* aux = pilha->topo;
    return GetTipoGarbage(aux->forma);
}

Item retornaItem(Pilha p) {
    StPilha* pilha = (StPilha*)p;

    Node* aux = pilha->topo;
    return aux->forma;
}

void destroy(Pilha p) {
    StPilha* pilha = (StPilha*)p;

    Node* aux = pilha->topo;
    Node* proximo;

    while(aux != NULL) {
        proximo = aux->next;
        free(aux);
        aux = proximo;
    }
    free(pilha);
}

void Prts(FILE* txt, Pilha p) {
    StPilha* pilha = (StPilha*)p;
    Node* aux = pilha->topo;
    Item forma;
    char tipo;

    while(aux != NULL) { 
    forma = aux->forma;
    tipo = GetTipoGarbage(forma);

    if (tipo == 'c') {
            
        int id = getIdCirculo(forma);
        char *corp = getCorpCIR(forma);
        char *corb = getCorbCIR(forma);
        double xc = getXc(forma);
        double yc = getYc(forma);
        double r = getRaio(forma);
        printf("tipo: %c id: %d corp: %s corb: %s xc: %lf yc: %lf r: %lf\n", tipo, id, corp, corb, xc, yc, r);
        fprintf(txt, "tipo: %c id: %d corp: %s corb: %s xc: %lf yc: %lf r: %lf\n", tipo, id, corp, corb, xc, yc, r);

        } else if (tipo == 'r') {

        int id = getIdRetangulo(forma);
        char *corp = getCorpRET(forma);
        char *corb = getCorbRET(forma);
        double X = getX(forma);
        double Y = getY(forma);
        double W = getW(forma);  
        double H = getH(forma);
        printf("tipo: %c id: %d corp: %s corb: %s x: %lf y: %lf w: %lf h:%lf\n", tipo, id, corp, corb, X, Y, W, H);
        fprintf(txt, "tipo: %c id: %d corp: %s corb: %s x: %lf y: %lf w: %lf h:%lf\n", tipo, id, corp, corb, X, Y, W, H);

        } else if (tipo == 'l') {

        int id = getIdlinha(forma);
        char *corp = getCorLIN(forma);
        double X1 = getX1(forma);
        double Y1 = getY1(forma);
        double X2 = getX2(forma);  
        double Y2 = getY2(forma);

        printf("tipo: %c id: %d corp: %s x1: %lf y1: %lf x2: %lf y2:%lf\n", tipo, id, corp, X1, Y1, X2, Y2);
        fprintf(txt, "tipo: %c id: %d corp: %s x1: %lf y1: %lf x2: %lf y2:%lf\n", tipo, id, corp, X1, Y1, X2, Y2);

        } else if (tipo == 't') { 
        int id = getIdtexto(forma);
        double x = getXtexto(forma);
        double y = getYtexto(forma);
        char* corp = getStringcorp(forma);
        char* corb = getStringcorb(forma);
        char* texto = getStringtexto(forma);
        char a = getStringA(forma);
        printf("tipo: %c id: %d corp: %s corb: %s ancora: %c texto: %s x: %lf y: %lf\n", tipo, id, corp, corb, a, texto, x, y);
        fprintf(txt, "tipo: %c id: %d corp: %s corb: %s ancora :%c texto: %s x: %lf y: %lf\n", tipo, id, corp, corb, a, texto, x, y);

        } else {
            printf("tipo de forma nao reconhecido...(funcao copiar forma)\n");
            exit(1);
        }
        aux = aux->next;
    }
}

void PushPopTxt(FILE* txt, Pilha p) {
    StPilha* pilha = (StPilha*)p;
    Node* aux = pilha->topo;
    Item forma;
    char tipo;

    forma = aux->forma;
    tipo = GetTipoGarbage(forma);

    if (tipo == 'c') {
            
        int id = getIdCirculo(forma);
        char *corp = getCorpCIR(forma);
        char *corb = getCorbCIR(forma);
        double xc = getXc(forma);
        double yc = getYc(forma);
        double r = getRaio(forma);
        printf("tipo: %c id: %d corp: %s corb: %s xc: %lf yc: %lf r: %lf\n", tipo, id, corp, corb, xc, yc, r);
        fprintf(txt, "tipo = %c\nid = %d\ncorp = %s\ncorb = %s\nx do centro = %lf\ny do centro = %lf\nraio = %lf\n\n", tipo, id, corp, corb, xc, yc, r);

        } else if (tipo == 'r') {

        int id = getIdRetangulo(forma);
        char *corp = getCorpRET(forma);
        char *corb = getCorbRET(forma);
        double X = getX(forma);
        double Y = getY(forma);
        double W = getW(forma);  
        double H = getH(forma);
        printf("tipo: %c id: %d corp: %s corb: %s x: %lf y: %lf w: %lf h:%lf\n", tipo, id, corp, corb, X, Y, W, H);
        fprintf(txt, "tipo = %c\nid = %d\ncorp = %s\ncorb = %s\nx = %lf\ny = %lf\nlargura = %lf\naltura = %lf\n\n", tipo, id, corp, corb, X, Y, W, H);

        } else if (tipo == 'l') {

        int id = getIdlinha(forma);
        char *corp = getCorLIN(forma);
        double X1 = getX1(forma);
        double Y1 = getY1(forma);
        double X2 = getX2(forma);  
        double Y2 = getY2(forma);

        printf("tipo: %c id: %d corp: %s x1: %lf y1: %lf x2: %lf y2:%lf\n", tipo, id, corp, X1, Y1, X2, Y2);
        fprintf(txt, "tipo = %c\nid = %d\ncorp = %s\nx1 = %lf\ny1 = %lf\nx2 = %lf\ny2 = %lf\n\n", tipo, id, corp, X1, Y1, X2, Y2);

        } else if (tipo == 't') { 
        int id = getIdtexto(forma);
        double x = getXtexto(forma);
        double y = getYtexto(forma);
        char* corp = getStringcorp(forma);
        char* corb = getStringcorb(forma);
        char a = getStringA(forma);
        char* texto = getStringtexto(forma);
        printf("tipo: %c id: %d corp: %s corb: %s ancora: %c texto: %s x: %lf y: %lf\n", tipo, id, corp, corb, a, texto, x, y);
        fprintf(txt, "tipo = %c\nid = %d\na = %c\ntexto = %s\ncorp = %s\ncorb = %s\nx = %lf\ny = %lf\n\n", tipo, id, a, texto, corp, corb, x, y);

        } else {
            printf("tipo de forma nao reconhecido...(funcao copiar forma)\n");
            exit(1);
        }
        aux = aux->next;
    }
