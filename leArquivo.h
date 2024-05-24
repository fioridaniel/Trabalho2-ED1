#ifndef _LE_ARQUIVOS__
#define _LE_ARQUIVOS__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**EXERCICIO: escrever a descricao do modulo e das operacoes. Implementar o
               este modulo. 
        - Note que faltam os parametros das operacoes. Voce deve
          coloca-los

   Suponha que o arquivo a ser lido esteja organizado em linhas.
Cada linha possui varias strings separadas por um espaco branco.
   A operacao leLinha tenta ler a proxima linha do arquivo e retorna verdadeiro
caso tenha conseguido (ou seja existia uma linha para ser lida).
  A operacao getParametroI retorna a i-esima string da ultima linha lida.
 */

typedef void* ArqCmds;

// Abre o arquivo especificado e retorna um ponteiro para o arquivo aberto.
ArqCmds abreArquivoCmd(char* fn);

// Tenta ler a próxima linha do arquivo especificado.
// Retorna verdadeiro se a leitura foi bem-sucedida, falso caso contrário.
bool leLinha(FILE* arq, char *linha, int max_size);

// Retorna a i-ésima string da última linha lida do arquivo.
void getParametroI(char *linha, int i);

// Fecha o arquivo especificado.
void fechaArquivoCmd(FILE* arq);

#endif