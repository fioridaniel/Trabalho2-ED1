#include <stdio.h>
#include <stdlib.h>
#include "garbage.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "shapebank.h"
#include "lista.h"

typedef struct Gerente{
    long int bytes_coletados;
    int figuras_coletadas;
} Gerente;

typedef struct StForma{
  int ref;
  Forma f;
  char tipo;
} StForma;

typedef struct StTotal{
    long int total_bytes;
    int execucoes;
    char alertas[1000][1000];
} StTotal;

typedef struct StColetor{
  LISTA formasReferenciadas;
  Gerente* gm;
  StTotal* total;
} StColetor;

GcCore CreateGcCore(int nx) {
    StColetor* collector = (StColetor*)malloc(sizeof(StColetor));

    if(collector == NULL)
    {
        printf("erro ao alocar memoria..saindo do programa.\n");
        exit(1);
    }

    collector->gm = CriaGerenciador(nx);
    collector->formasReferenciadas = createLista(nx);
    collector->total = CriaArmazenamentoDeDados();
    return collector;
}

GerenteMemoria RetornaGerente(GerenteMemoria gerente) {
    StColetor* gm = (StColetor*)gerente;
    return gm->gm;
}

LISTA RetornaLista(LISTA list) {
    StColetor* lista = (StColetor*)list;
    return lista->formasReferenciadas;
}

GerenteMemoria CriaGerenciador(int nx) {
    Gerente* geren = (Gerente*)malloc(sizeof(Gerente) * nx);
    geren->bytes_coletados = geren->figuras_coletadas = 0;

    for(int i = 0; i < nx; i++) {
        geren[i].bytes_coletados   = -1;
        geren[i].figuras_coletadas = -1;
    }
    return geren; 
}

TotalArmazenamento CriaArmazenamentoDeDados() {
    StTotal* total   = (StTotal*)malloc(sizeof(StTotal));
    total->execucoes = total->total_bytes = 0;

    for (int i = 0; i < 500; ++i) {
        for (int j = 0; j < 500; ++j) {
            total->alertas[i][j] = '\0';
        }
    }
    
    if(total == NULL)
    {
        printf("erro ao alocar memoria..saindo do programa.\n");
        exit(1);
    }
    return total;
}

void SetAlerta(GcCore gc, char* alerta) {
    StColetor* col = (StColetor*)gc;

    for(int i = 0; i < 500; i++) {
        if(col->total->alertas[i][0] == '\0')
        {
            strcpy(col->total->alertas[i], alerta);
            break; 
        } 
    }
}

void ExecutarColeta(LISTA lista, GerenteMemoria gm) {
    Gerente* geren = (Gerente*)gm;

    long int soma_bytes = 0;
    int soma_figuras    = 0;
    char tipo;

    while(true)
    {
        Forma forma = PercorreLista(lista);
        if(forma == NULL)
        {
            break;
        }

        tipo        = GetTipoGarbage(forma);
        soma_bytes += GetSize(tipo);
        soma_figuras++;
    }
    InsereNoGerente(geren, soma_bytes, soma_figuras);
}

void ExecucoesNaoAnalisadas(LISTA lista, FILE* arqTxtSaida) {
    long int soma_bytes = 0;
    int soma_figuras    = 0;
    char tipo;

    while(true)
    {
        Forma forma = PercorreLista(lista); 
        if(forma == NULL)
        {
            printf("testando dentro de execucoes nao analisadas.\n");
            break;
        }

        tipo        = GetTipoGarbage(forma);
        soma_bytes += GetSize(tipo);
        soma_figuras++;
        forma = NULL;
    }
    fprintf(arqTxtSaida, "\nTotal de bytes e formas que embora pudessem, nao foram coletados:\nbytes  = %ld\nformas = %d\n", soma_bytes, soma_figuras);
}

void SetNumeroExecucoes(TotalArmazenamento t, int vezes) {
    StColetor* total = (StColetor*)t;
    StTotal* def = total->total;

    def->execucoes = vezes;
}

int GetNumeroExecucoes(TotalArmazenamento t) {
    StColetor* total = (StColetor*)t;
    StTotal* def = total->total;

    return def->execucoes;
}

void ReportaArmazenamentoDeDados(FILE* arqTxtSaida, TotalArmazenamento t) {
    StColetor* total = (StColetor*)t;
    StTotal* def = total->total;
    fprintf(arqTxtSaida, "\nTotal de vezes que a coleta foi executada       = %d\nTotal de bytes alocados pelos arquivo geo e qry = %ld\n", def->execucoes, def->total_bytes);

    fprintf(arqTxtSaida, "\nALERTAS DO GCCORE:\n");

    for(int i = 0; i < 500; i++) {
        if(def->alertas[i][0] != '\0')
        {
            fprintf(arqTxtSaida, "\n%s\n", def->alertas[i]);                
        } 
    }
}

void InsereNoGerente(GerenteMemoria gm, long int bytes, int figuras) {
    Gerente* gerente = (Gerente*)gm;

    int i = 0;
    while(gerente[i].bytes_coletados != -1)
    {
        i++;
    }
    gerente[i].bytes_coletados    = bytes;
    gerente[i].figuras_coletadas  = figuras;

}

void ReportaGerente(FILE* arqTxtSaida, GerenteMemoria gm, int execucoes) {
    Gerente* gerente = (Gerente*)gm;

    long int total_bytes = 0; 
    int total_fig        = 0;

    for(int i = 0; i < execucoes; i++) {
        if(gerente[i].bytes_coletados != -1 || gerente[i].figuras_coletadas != -1) { 
        total_bytes += gerente[i].bytes_coletados;
        total_fig   += gerente[i].figuras_coletadas;
        fprintf(arqTxtSaida, "\nExecucao %d do GcCore\nBytes coletados   = %ld\nFiguras coletadas = %d\n", i + 1, gerente[i].bytes_coletados, gerente[i].figuras_coletadas);
        }
        
        else {
        fprintf(arqTxtSaida, "\nExecucao %d do GcCore\nBytes coletados   = 0\nFiguras coletadas = 0\n", i + 1);
        }
    }
    fprintf(arqTxtSaida, "\nTotal de bytes coletadas   = %ld\nTotal de figuras coletadas = %d\n", total_bytes, total_fig);
}

Forma CriaStructRetangulo(int id, double x, double y, double w, double h, char* corb, char* corp) {
    StForma* nova = (StForma*)malloc(sizeof(StForma));
    nova->f    = inicializaRetangulo(id, x, y, w, h, corb, corp);
    nova->ref  = 1;
    nova->tipo = 'r';

    return nova;
}

Forma CriaStructCirculo(int id, double x, double y, double r, char *corp, char *corb) {
    StForma* nova = (StForma*)malloc(sizeof(StForma));
    nova->f    = inicializaCirculo(id, x, y, r, corp, corb);
    nova->ref  = 1;
    nova->tipo = 'c';

    return nova;
}

Forma CriaStructLinha(int id, double x1, double y1, double x2, double y2, char* cor) {
    StForma* nova = (StForma*)malloc(sizeof(StForma));
    nova->f       = inicializaLinha(id, x1, y1, x2, y2, cor);
    nova->ref     = 1;
    nova->tipo    = 'l';

    return nova;
}

Forma CriaStructTexto(int id, double x, double y, char* corp, char* corb, char* string, char a) {
    StForma* nova = (StForma*)malloc(sizeof(StForma));
    nova->f       = inicializaTexto(id, x, y, corp, corb, string, a);
    nova->ref     = 1;
    nova->tipo    = 't';

    return nova;
}

long int GetSize(char tipo) {
    if(tipo == 'c') 
    {
        return SizeCirculo();
    }
    else if(tipo == 'r')
    {
        return SizeRetangulo();
    }
    else if(tipo == 'l')
    {
        return SizeLinha();
    }
    else
    {
        return SizeTexto();
    }
}

void IncrementSize(TotalArmazenamento dados, char tipo) {
    StColetor* data = (StColetor*)dados;
    if(tipo == 'c') 
    {
        data->total->total_bytes += SizeCirculo();
    }
    else if(tipo == 'r')
    {
        data->total->total_bytes += SizeRetangulo();
    }
    else if(tipo == 'l')
    {
        data->total->total_bytes += SizeLinha();
    }
    else
    {
        data->total->total_bytes += SizeTexto();
    }
}

int GetRef(Forma st) {
    return ((StForma*)st)->ref;
}

void IncrementaRef(Forma st) {
    ((StForma*)st)->ref++;
    printf("Incrementando o numero de ref = %d\n", ((StForma*)st)->ref);
}

void DecrementaRef(Forma st) {
    ((StForma*)st)->ref--;
    printf("Decrementando o numero de ref = %d\n", ((StForma*)st)->ref);
}

void SetRef(Forma st, int ref) {
    ((StForma*)st)->ref = ref;
    printf("Setando o numero de ref = %d\n", ((StForma*)st)->ref);
}

Forma GetFormaGarbage(Forma st) {
    StForma* stforma = (StForma*)st;
    return stforma->f;
}

char GetTipoGarbage(Forma st) {
    StForma* stforma = (StForma*)st;
    return stforma->tipo;
}

