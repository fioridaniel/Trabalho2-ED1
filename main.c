#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "arqsvg.h"
#include "leArquivo.h"
#include "arqgeo.h"
#include "shapebank.h"
#include "registrador.h"
#include "qry.h"
#include "path.h"
#include "garbage.h"
#include "lista.h"

int main(int argc, char * argv[])
{

    int i, j;

    char * entryArg    = NULL;
    char * outputArg   = NULL;
    char * geoArg      = NULL;
    char * qryArg      = NULL;

    char * geoFile     = NULL;
    char * geoFilePath = NULL;
    char * geoFileName = NULL;

    char * qryFile     = NULL;
    char * qryFilePath = NULL;
    char * qryFileName = NULL;

    char * entryPath   = NULL;
    char * outputPath  = NULL;

    int nx = 100;
    int gc = 10;
    GcCore gccore;

    // SEPARADOR DE PARÂMETROS
    for (i = 1; i < argc; i++)
    {
        // Diretório de base de ENTRADA (Opcional)
        if (strcmp(argv[i], "-e") == 0)
        {
            // TRATAR CASOS DE DIRETÓRIOS
            entryArg = argv[i + 1];
            entryPath = malloc(sizeof(char) * (strlen(entryArg) + 1));
            normalizePath(entryArg, entryPath, strlen(entryPath) + 1);
        }
        else
        // Diretório base de SAÍDA (OBRIGATÓRIO)
        if (strcmp(argv[i], "-o") == 0)
        {
            // TRATAR CASOS DE DIRETÓRIO
            outputArg = argv[i + 1];
            outputPath = malloc(sizeof(char) * (strlen(outputArg) + 1));
            normalizePath(outputArg, outputPath, strlen(outputPath) + 1);
        }
        else
        // Endereço ou nome de arg.geo (deve estar contigo em -e) (OBRIGATÓRIO)
        if (strcmp(argv[i], "-f") == 0)
        {
            // TRATAR ENDEREÇO E NOME
            geoArg = argv[i + 1];
            geoFileName = malloc(sizeof(char) * (strlen(geoArg) + 1));
            geoFilePath = malloc(sizeof(char) * (strlen(geoArg) + 1));
            getFileName(geoArg, geoFileName, strlen(geoArg) + 1);
            getPath(geoArg, geoFilePath, strlen(geoArg) + 1);

            // Verificar se tem ./ no início, então remover
            if (geoFilePath[0] == '.' && geoFilePath[1] == '/')
                sprintf(geoFilePath, "%s", geoFilePath + 2);
            if (geoFilePath[0] == '.')
                geoFilePath[0] = '\0';
            geoFileName = realloc(geoFileName, sizeof(char) * (strlen(geoFileName) + 1));
            geoFilePath = realloc(geoFilePath, sizeof(char) * (strlen(geoFilePath) + 1));
        }
        else
        // Endereço ou nome de arg.qry (deve estar contigo em -e) (Opcional)
        if (strcmp(argv[i], "-q") == 0)
        {
            // TRATAR ENDEREÇO E NOME
            qryArg = argv[i + 1];
            qryFileName = malloc(sizeof(char) * (strlen(qryArg) + 1));
            qryFilePath = malloc(sizeof(char) * (strlen(qryArg) + 1));
            getFileName(qryArg, qryFileName, strlen(qryArg) + 1);
            getPath(qryArg, qryFilePath, strlen(qryArg) + 1);

            // Verificar se tem ./ no início, então remover
            if (qryFilePath[0] == '.' && qryFilePath[1] == '/')
                sprintf(qryFilePath, "%s", qryFilePath + 2);
            if (qryFilePath[0] == '.')
                qryFilePath[0] = '\0';
            qryFileName = realloc(qryFileName, sizeof(char) * (strlen(qryFileName) + 1));
            qryFilePath = realloc(qryFilePath, sizeof(char) * (strlen(qryFilePath) + 1));
        }
        // Tamanho maximo do shapebank
        if(strcmp(argv[i], "-nx") == 0)
        {
            nx = atoi(argv[i + 1]);

            if(nx == -1)
            {
                nx = 10000;
            }

            printf("\n\nNX = %d\n", nx);
        }

        if(strcmp(argv[i], "-gc") == 0)
        {
            gc = atoi(argv[i + 1]);
            printf("\n\nGC = %d\n", gc);
        }
    }

    // Tratamento de caminho para o diretório base de entrada
    if (entryArg == NULL)
    {
        // Não foi especificado um diretório de entrada, então seguir diretriz: 
        // "Caso não seja informado, o diretório de entrada é o diretório corrente da aplicação."
        entryPath = malloc(sizeof(char) * 2);
        strcpy(entryPath, ".");
    }

    geoFile = malloc(sizeof(char) * (strlen(entryPath) + 1 + strlen(geoFilePath) + 1 + strlen(geoFileName) + 1));

    // Tratamento do caminho para .geo
    strcpy(geoFile, entryPath);
    if (strcmp(geoFilePath, "") != 0)
        sprintf(geoFile, "%s/%s", geoFile, geoFilePath);
    sprintf(geoFile, "%s/%s", geoFile, geoFileName);


    if (qryArg != NULL)
    {
        // Existe um .qry
        qryFile = malloc(sizeof(char) * (strlen(entryPath) + 1 + strlen(qryFilePath) + 1 + strlen(qryFileName) + 1));
        // Tratamento do caminho para .qry
        strcpy(qryFile, entryPath);
        if (strcmp(qryFilePath, "") != 0)
            sprintf(qryFile, "%s/%s", qryFile, qryFilePath);
        sprintf(qryFile, "%s/%s", qryFile, qryFileName);
    }
    
    printf("- entryPath:  %s\n", entryPath);
    printf("- outputPath: %s\n", outputPath);
    printf("- geoFile:    %s\n", geoFile);
    printf("- qryFile:    %s\n", qryFile);
    printf("- geoPath:    %s\n", geoFilePath);
    printf("- qryPath:    %s\n", qryFilePath);
    printf("- geoName:    %s\n", geoFileName);
    printf("- qryName:    %s\n", qryFileName);
    
    char * geoFileNameWithoutExt = malloc(sizeof(char) * (strlen(geoFileName) + 1));
    getFileNameWithoutExt(geoFileName, geoFileNameWithoutExt, strlen(geoFileName) + 1);
    geoFileNameWithoutExt = realloc(geoFileNameWithoutExt, sizeof(char) * (strlen(geoFileNameWithoutExt) + 1));
    
    
    char * mainSvgFile = malloc(sizeof(char) * (strlen(outputPath) + 1 + strlen(geoFileNameWithoutExt) + strlen(".svg") + 1));
    sprintf(mainSvgFile, "%s/%s.svg", outputPath, geoFileNameWithoutExt);

    char * qryFilenameWithoutExt = malloc(sizeof(char) * (strlen(qryFileName) + 1));
    getFileNameWithoutExt(qryFileName, qryFilenameWithoutExt, strlen(qryFileName) + 1);
    qryFilenameWithoutExt = realloc(qryFilenameWithoutExt, sizeof(char) * (strlen(qryFilenameWithoutExt) + 1));

    char * geo_qry = malloc(sizeof(char) * (strlen(geoFileNameWithoutExt) + 1 + strlen(qryFilenameWithoutExt) + 1));
    sprintf(geo_qry, "%s-%s", geoFileNameWithoutExt, qryFilenameWithoutExt);
    
    char * finalSvgFile = malloc(sizeof(char) * (strlen(outputPath) + 1 + strlen(geoFileNameWithoutExt) + 1 + strlen(qryFilenameWithoutExt) + strlen(".svg") + 1));
    sprintf(finalSvgFile, "%s/%s-%s.svg", outputPath, geoFileNameWithoutExt, qryFilenameWithoutExt);

    char * txtFile = malloc(sizeof(char) * (strlen(outputPath) + 1 + strlen(geo_qry) + strlen(".txt") + 1));
    sprintf(txtFile, "%s/%s.txt", outputPath, geo_qry);
    FILE * TXTFile = fopen(txtFile, "w");
    
    FILE * arquivoGeo    = abreArquivoCmd(geoFile);
    printf("teste 1\n");
    FILE * arqSvgInicial = abreEscritaSvg(mainSvgFile);
    printf("teste 2\n"); 




    void* shapebank = InicializaShapeBank(nx);
    gccore          = CreateGcCore(nx);
    void* lista     = RetornaLista(gccore);

    ComandosGeo(shapebank, gccore, arquivoGeo, arqSvgInicial);
    fechaArquivoCmd(arquivoGeo);
    fechaSvg(arqSvgInicial);



    FILE* arquivoQry   = abreArquivoCmd(qryFile);
    printf("teste 3\n");
    FILE* arqSvgFinal  = abreEscritaSvg(finalSvgFile);
    printf("teste 4\n");
    FILE * arqTxtSaida = fopen(txtFile, "w");
    lerQry(shapebank, gccore, arquivoQry, arqTxtSaida, nx / 2, gc);

    char tipo_forma;

    for(int i = 1; i <= nx; i++) { 
        Forma forma = copiaDoshape(shapebank, i);
        if(forma != NULL) {
        tipo_forma = GetTipoGarbage(forma);
        ShapeBankSvgFinal(forma, tipo_forma, arqSvgFinal);  
        }
    }

    ReportaArmazenamentoDeDados(arqTxtSaida, gccore);
    void* gerente = RetornaGerente(gccore);
    ReportaGerente(arqTxtSaida, gerente, GetNumeroExecucoes(gccore));
    ExecucoesNaoAnalisadas(lista, arqTxtSaida);
    
    fechaSvg(arqSvgFinal);
    fechaArquivoCmd(arqTxtSaida);


    printf("\n\nNX = %d\n", nx);
    return 0;
}   