#include "registrador.h"

typedef struct {
    Forma geo;
} Registrador;

Registrador registradores[5];

Forma CopiaDoRegistrador(int mem) {
    if(mem > 5 || mem < 1) {
        printf("Numero de memoria nao compativel com os registradores\n");
        exit(1);
    }

    printf("estrutura copiada do registrador rg%d\n", mem);
    return registradores[mem - 1].geo; 
}

void CarregaRegistrador(Forma estrutura, int mem) {
    if(mem > 5 || mem < 1) {
        printf("Numero de memoria nao compativel com os registradores\n");
        return;
    }

    printf("estrutura carregada no registrador rg%d\n", mem);
    registradores[mem - 1].geo = estrutura;
}

char VerificarTipoRegistrador(int mem) { 
    char tipo_forma = GetTipoGarbage(registradores[mem - 1].geo);
    printf("verificando o tipo da forma em REG: %c\n", tipo_forma);

    return tipo_forma;
}

