#include "leArquivo.h"

#define MAX_SIZE 1000

typedef struct {
    double r, xc, yc;
    char* corp, *corb;
    double x, y, w, h;
    double x1, y1, x2, y2;
} formas;

ArqCmds abreArquivoCmd(char *fn) {
   FILE* arq = fopen(fn, "r");
    if(arq == NULL) {
        printf("Arquivo nao foi aberto corretamente.\n");
        exit(1);
    }
    return arq;
}

bool leLinha(FILE* arq, char *linha, int max_size) {
    if (fgets(linha, max_size, arq) != NULL) {
        return true;
    } else {
        return false;
    }
}

void getParametroI(char *linha, int i) { 
    char* token = strtok(linha, " ");
    for (int j = 0; j < i; j++) {
        if (token == NULL) {
            return; 
        }
        token = strtok(NULL, " ");
    }
}

void fechaArquivoCmd(FILE* arq) {
    fclose(arq);
}