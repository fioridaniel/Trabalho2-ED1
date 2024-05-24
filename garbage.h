#ifndef _GARBAGECOLLECTOR_
#define _GARBAGECOLLECTOR_

typedef void* GcCore;
typedef void* Forma;
typedef void* GerenteMemoria;
typedef void* TotalArmazenamento;
typedef void* LISTA;

/*
    O Garbage Collector eh definido como um conjunto de 
    Modulos que operam sobre uma colecao de itens, que 
    mantem uma lista de todos os itens que foram alocados
    durante a execucao do programa. Quando um item passa a ser
    somente referenciado pelo coletor, ele eh desalocado.
    Para o Garbage Collector ser acionado, utiliza-se o comando -gc N,
    onde N eh um numero inteiro positivo. Isso quer dizer que a cada
    N comandos operados pelo qry, sera feita uma coleta do Garbage.
    Por convencao, caso nao o comando -gc nao for inserido, N sera 10.
*/

/*
    O Gerente Memoria mantem um conjunto de dados
    que armazenam o numero de bytes coletados, juntamente
    com o numero de figuras coletadas em cada execucao 
    do coletor.
*/

/*
    A Forma possui o apontador para o objeto armazenado,
    um char que representa o tipo da forma, lembrando que so
    podem ser c, r, l e t (MINUSCULOS), e estao associados a 
    circulo, retangulo, linha e texto respectivamente.
    E por fim, possui o contador de referencias, que mostra
    quantos objetos possui o endereco dessa forma.
*/

/*
    O TotalArmazenamento armazena quantos bytes de dados foram 
    alocados durante a execucao do programa nos arquivos
    geo e qry, bem como a quantidade de execucoes do Garbage Collector.
    Alem disso, possui os alertas indicados durante a execucao do coletor.
    Quando uma forma que possuia pelo menos uma referencia, eh desalocada,
    um alerta eh emitido.
*/

/*
    Cria o Garbage Collector, e inicializa a lista, o gerente
    memoria, e o objeto TotalArmazenamento. Retorna o coletor. 
*/
GcCore CreateGcCore(int nx);

/*
    Cria o Gerente memoria com tamanho nx, e retorna.
*/
GerenteMemoria CriaGerenciador(int nx);

/*
    Cria o TotalArmazenamento, e retorna.
*/
TotalArmazenamento CriaArmazenamentoDeDados();

/*
    Envia um alerta (string) para o coletor,
    indicando que existem referencias a alguma forma
    que ja foi deletada.
*/
void SetAlerta(GcCore gc, char* alerta);

/*
    Incrementa o numero total de bytes das formas
    criadas pelos arquivos geo e qry. Pega o tipo
    associado a forma e incrementa o respectivo tamanho
    desse objeto. 
*/
void IncrementSize(TotalArmazenamento dados, char tipo);

/*
    Funcao que ativa o GcCore, e coleta todas as formas
    que possuem referencia zero na lista. Ele deposita o numero 
    de bytes e o numero de formas coletadas no gerente
    de memoria.
*/
void ExecutarColeta(LISTA lista, GerenteMemoria gm);

/*
    Pega as informacoes dos itens que estavam depositados 
    na lista que nao foram analisados no final do programa.
*/
void ExecucoesNaoAnalisadas(LISTA lista, FILE* arqTxtSaida);

/*
    Passa o total de execucoes para o TotalArmazenamento.
*/
void SetNumeroExecucoes(TotalArmazenamento t, int vezes);

/*
    Retorna o total de execucoes do TotalArmazenamento. 
*/
int GetNumeroExecucoes(TotalArmazenamento t);

/*
    Reporta os dados do TotalArmazenamento no arquivo arqTxtSaida.
*/
void ReportaArmazenamentoDeDados(FILE* arqTxtSaida, TotalArmazenamento t);

/*
    Insere o numero de bytes e figuras coletadas no Gerente Memoria
    de uma determinada execucao do GcCore.
*/
void InsereNoGerente(GerenteMemoria gm, long int bytes, int figuras);

/*
    Reporta todos os dados armazenados no Gerente Memoria no arqTxtSaida.
*/
void ReportaGerente(FILE* arqTxtSaida, GerenteMemoria gm, int execucoes);

/*
    Recebe o tipo de um objeto, e retorna o tamanho associado a esse objeto.
*/
long int GetSize(char tipo);

/*
    Cria uma Forma Retangulo com os parametros fornecidos.
*/
Forma CriaStructRetangulo(int id, double x, double y, double w, double h, char* corb, char* corp);

/*
    Cria uma Forma Circulo com os parametros fornecidos.
*/
Forma CriaStructCirculo(int id, double x, double y, double r, char *corp, char *corb);

/*
    Cria uma Forma Linha com os parametros fornecidos.
*/
Forma CriaStructLinha(int id, double x1, double y1, double x2, double y2, char* cor);

/*
    Cria uma Forma Texto com os parametros fornecidos.
*/
Forma CriaStructTexto(int id, double x, double y, char* corp, char* corb, char* string, char a);

/*
    Incrementa em um o numero de referencias da Forma st.
*/
void IncrementaRef(Forma st);

/*
    Decrementa em um o numero de referencias da Forma st.
*/
void DecrementaRef(Forma st);

/*
    Seta o numero de referencias da Forma st.
*/
void SetRef(Forma st, int ref);

/*
    Retorna o numero de referencias da Forma st.
*/
int GetRef(Forma st);

/*
    Retorna o apontador da figura do objeto Forma. 
*/
Forma GetFormaGarbage(Forma st);

/*
    Retorna char correspondente da figura do objeto Forma. Lembrando que so
    podem ser c, r, l e t (MINUSCULOS), e estao associados a 
    circulo, retangulo, linha e texto respectivamente.
*/
char GetTipoGarbage(Forma st);

/*
    Retorna o apontador para o Gerente Memoria.
*/
GerenteMemoria RetornaGerente(GerenteMemoria gerente);

/*
    Retorna o apontador para a lista.
*/
LISTA RetornaLista(LISTA list);

#endif