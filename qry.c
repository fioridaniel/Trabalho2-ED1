#include "qry.h"

#define MAX_SIZE 10000
#define capacidade 5000

int getRg(char rg[])
{
    int tam = strlen(rg);
    int inteiro = rg[tam - 1] - '0';
    return inteiro;
}

int getSt(char st)
{
    if (st == 'A')
    {
        return 1;
    }
    else if (st == 'B')
    {
        return 2;
    }
    else if (st == 'C')
    {
        return 3;
    }
    else
    {
        return 4;
    }
}

void lerQry(ShapeBank shapebank, GcCore gccore, FILE *arqQry, FILE* arqTxtSaida, int tamSt, int gc)
{
    char linha[MAX_SIZE];
    char comando[30], aux[MAX_SIZE];
    char rg[5], rg2[5], st, st2, tipo;
    int int_rg, int_st, int_rg2, int_st2;
    int mem;
    Pilha *stacks[4];
    Item i;
    int cont = 1;
    int vezes = 0;
    int nx = tamSt * 2;

    void* lista   = RetornaLista(gccore);
    void* gerente = RetornaGerente(gccore);
    FILE* txt   = arqTxtSaida;

    for (int i = 0; i < 4; i++)
    {
        stacks[i] = createPilha(tamSt); // Inicializa cada stack
    }

    printf("\nPilha criada com sucesso!\n");

    while (leLinha(arqQry, linha, MAX_SIZE))
    {
        aux[0] = '\0'; // Esvazia a variavel aux e comando a cada iteracao
        comando[0] = '\0';
        strcpy(aux, linha);
        sscanf(aux, "%s", comando);

        if (comando != NULL)
        {
            if (strcmp(comando, "ld") == 0)
            {
                printf("\nComando ld\n");
                sscanf(aux, "%s %s %d", comando, rg, &mem);
                int_rg = getRg(rg);
                Forma forma = copiaDoshape(shapebank, mem);
                tipo = verificarTipoShape(shapebank, mem);

                if((CopiaDoRegistrador(int_rg) != NULL) /*&& (CopiaDoRegistrador(int_rg) != forma)*/)
                {
                    printf("\nDRECEMENTANDO REF DENTRO DA FUNCAO LD\n");
                    DecrementaRef(CopiaDoRegistrador(int_rg));
                }

                CarregaRegistrador(forma, int_rg);
                IncrementaRef(forma);
    
            }
            else if (strcmp(comando, "sto") == 0)
            {
                printf("\nComando sto\n");
                sscanf(aux, "%s %d %s", comando, &mem, rg);
                int_rg = getRg(rg);
                Forma forma = CopiaDoRegistrador(int_rg);
                tipo = VerificarTipoRegistrador(int_rg); 

                //int id = ElseifId(forma);

                if((copiaDoshape(shapebank, mem) != NULL))
                {
                    printf("DECREMENTANDO DENTRO DA FUNCAO STO\n");
                    DecrementaRef(copiaDoshape(shapebank, mem));
                    //SetRef(copiaDoshape(shapebank, mem), 0); //talvez fazer uma condicao para quando o shapebank ja estiver carregado com aquela forma
                    IncrementaRef(forma);
                }

                else if(copiaDoshape(shapebank, mem) == NULL)
                {
                    printf("POSICAO MEM DO SHAPEBANK ESTA VAZIA\n");
                    IncrementaRef(forma);
                }

                else
                {
                    printf("ERRO DENTRO DA FUNCAO STO ... CONDICAO NAO ENCONTRADA.\n");
                }

                DepositarNoshape(shapebank, forma, mem);
            }
            else if (strcmp(comando, "push") == 0)
            {

                printf("\nComando push\n");
                fprintf(txt, "Comando push:\n");
                sscanf(aux, "%s %c %s", comando, &st, rg);
                int_st = getSt(st);
                int_rg = getRg(rg);
                printf("numero do rg: %d\n", int_rg);
                Forma forma = CopiaDoRegistrador(int_rg);
                tipo = VerificarTipoRegistrador(int_rg);
                if (int_st >= 1 && int_st <= 4)
                {
                    push(stacks[int_st - 1], forma);
                    PushPopTxt(txt, stacks[int_st - 1]);
                    IncrementaRef(forma);
                }
                else
                {
                    printf("Numero da pilha invalido: %d\n", int_st);
                }
            }
            else if (strcmp(comando, "pop") == 0)
            {
                printf("\nComando pop\n");
                fprintf(txt, "\nComando pop:\n");
                sscanf(aux, "%s %s %c", comando, rg, &st);
                int_rg = getRg(rg);
                printf("numero do rg: %d\n", int_rg);
                int_st = getSt(st);

                if (int_st >= 1 && int_st <= 4)
                {
                    if (!isEmpty(stacks[int_st - 1]))
                    {
                        tipo = VerificaTipoStack(stacks[int_st - 1]);
                        PushPopTxt(txt, stacks[int_st - 1]);
                        i = pop(stacks[int_st - 1]);
                        
                        if((CopiaDoRegistrador(int_rg) != NULL) /*&& (i != NULL) && (CopiaDoRegistrador(int_rg) != i)*/)
                        {
                            printf("\nDRECEMENTANDO REF DENTRO DA FUNCAO POP\n");
                            DecrementaRef(CopiaDoRegistrador(int_rg));
                        }

                        printf("stack tipo: %c\n", tipo);
                        CarregaRegistrador(i, int_rg);         
                    }
                    else
                    {
                        printf("Nao foi possivel completar a operacao, stack vazia...\n");
                    }
                }
            }
            else if (strcmp(comando, "mvs") == 0)
            {
                printf("\nComando mvs\n");
                sscanf(aux, "%s %c %c", comando, &st, &st2);

                int_st  = getSt(st);
                int_st2 = getSt(st2);

                while (!isEmpty(stacks[int_st - 1]))
                {
                    tipo = VerificaTipoStack(stacks[int_st - 1]);
                    i = pop(stacks[int_st - 1]);

                    push(stacks[int_st2 - 1], i);
                }
            }
            else if (strcmp(comando, "ca") == 0)
            {
                char corp[30], corb[30]; // Initialize to NULL
                char dx[30], dy[30];
                printf("\nComando ca\n");
                sscanf(aux, "%s %s %s %s %s %s %s", comando, rg2, rg, dx, dy, corb, corp);
                int r1 = getRg(rg);
                int r2 = getRg(rg2);
                Forma forma  = CopiaDoRegistrador(r1);
                tipo = VerificarTipoRegistrador(r1);


                Forma forma2 = CopiaDoRegistrador(r2);

                if (strcmp(dx, "-") != 0)
                {

                    if (tipo == 'c')
                    {

                        setXc(forma, getXc(forma) + atof(dx));
                    }
                    else if (tipo == 'r')
                    {

                        setX(forma, getX(forma) + atof(dx));
                    }
                    else if (tipo == 'l')
                    {

                        setX1(forma, getX1(forma) + atof(dx));
                        setX2(forma, getX2(forma) + atof(dx));
                    }
                    else
                    {

                        setXtexto(forma, getXtexto(forma) + atof(dx));
                    }
                }

                if (strcmp(dy, "-") != 0)
                {

                    if (tipo == 'c')
                    {

                        setYc(forma, getYc(forma) + atof(dy));
                    }
                    else if (tipo == 'r')
                    {

                        setY(forma, getY(forma) + atof(dy));
                    }
                    else if (tipo == 'l')
                    {

                        setY1(forma, getY1(forma) + atof(dy));
                        setY2(forma, getY2(forma) + atof(dy));
                    }
                    else
                    {

                        setYtexto(forma, getYtexto(forma) + atof(dy));
                    }
                }
                if (strcmp(corb, "-") != 0)
                {

                    if (tipo == 'c')
                    {

                        setCorbCIR(forma, corb);
                    }
                    else if (tipo == 'r')
                    {

                        setCorbRET(forma, corb);
                    }
                    else if (tipo == 'l')
                    {

                        setCorLIN(forma, corb);
                    }
                    else
                    {

                        setStringCorb(forma, corb);
                    }
                }
                if (strcmp(corp, "-") != 0)
                {

                    if (tipo == 'c')
                    {

                        setCorpCIR(forma, corp);
                    }
                    else if (tipo == 'r')
                    {
                        printf("VERIFICANDO ERRO....\n");
                        setCorpRET(forma, corp);
                    }
                    else if (tipo == 'l')
                    {

                        setCorLIN(forma, corp);
                    }
                    else
                    {

                        setStringCorp(forma, corp);
                    }
                }
               
                if(forma2 != NULL /*&& (CopiaDoRegistrador(r2) != forma)*/)
                {
                    printf("\nDRECEMENTANDO REF DENTRO DA FUNCAO CA\n");
                    DecrementaRef(forma2);
                }

                CarregaRegistrador(forma, r2);
                IncrementaRef(forma);
                //IncrementaSize(GetTipoGarbage(forma));
            }
            else if (strcmp(comando, "del") == 0)
            { 
                //setar ref para zero. Emitir alerta do coletor
                printf("Comando del\n");
                sscanf(aux, "%s %d", comando, &mem);
                ReportarTxtShape(shapebank, mem, txt);
                Forma forma = copiaDoshape(shapebank, mem);
                //SetRef(forma, 0);

                int numRef = GetRef(forma);

                if(numRef >= 1)
                {
                char alerta[1000];
                sprintf(alerta, "%d referencia(s) a uma forma que foi deletada", GetRef(forma));
                SetAlerta(gccore, alerta);
                }
                removerFormaShape(shapebank, mem);
            }
            else if (strcmp(comando, "prts") == 0)
            {
                printf("\nComando prts\n");
                fprintf(txt, "\nComando PRTS:");
                sscanf(aux, "%s %c", comando, &st);
                int_st = getSt(st);
                int tam = size(stacks[int_st - 1]);
                fprintf(txt, "Numero de elementos da stack %c: %d\n",st, tam);
                Prts(txt, stacks[int_st - 1]);
            }
            else if (strcmp(comando, "tp") == 0)
            {
                printf("\nComando tp\n");
                double x, y;
                char texto[300]; 
                sscanf(aux, "%s %c %d %lf %lf %[^\n]", comando, &st, &mem, &x, &y, texto);

                printf("%s\n", texto);

                int_st = getSt(st);

                if (isEmpty(stacks[int_st - 1]))
                {
                    Forma forma = inicializaTexto(mem, x, y, "#FF0000", "#550000", strcat(texto, "VAZIA"), 'i');
                    insertNode(lista, forma);
                    if(copiaDoshape(shapebank, mem) != NULL) {
                    DecrementaRef(copiaDoshape(shapebank, mem));
                    }
                    DepositarNoshape(shapebank, forma, mem);
                }

                else
                {
                    printf("A pilha %d nao esta vazia", st);
                }


            }
            else if(strcmp(comando, "bb") == 0)
            {
                printf("\nComando bb\n");
                sscanf(aux, "%s %s %s", comando, rg, rg2);

                int_rg = getRg(rg);
                int_rg2 = getRg(rg2);
                

                //POTENCIALMENTE O PROBLEMA

                Forma forma1 = CopiaDoRegistrador(int_rg);
                Forma forma2 = CopiaDoRegistrador(int_rg2);

                char tipo1 = VerificarTipoRegistrador(int_rg); 
                char tipo2 = VerificarTipoRegistrador(int_rg2);

                int id, id1;

                id = ElseifId(forma2);

                //printf("ID DA FORMA: %d\n", id);

                //Forma forma1 = CopiarForma(forma1, tipo1); //r1
                //Forma forma2 = CopiarForma(forma2, tipo2); //r2

                double maior_x1, menor_x1, maior_y1, menor_y1;
                double maior_x2, menor_x2, maior_y2, menor_y2;

                char forma1_corb[30];
                char forma2_corp[30];

                double x_ancora, y_ancora;

                double maior_x;
                double maior_y;
                
                    if (tipo1 == 'c')
                    {
                    menor_x1 = getXc(forma1) - getRaio(forma1);
                    menor_y1 = getYc(forma1) - getRaio(forma1);
                    maior_x1 = getXc(forma1) + getRaio(forma1);
                    maior_y1 = getYc(forma1) + getRaio(forma1);
                    strcpy(forma1_corb, getCorbCIR(forma1));
                    id1 = getIdCirculo(forma1);
                        
                    }
                    else if (tipo1 == 'r')
                    {
                    menor_x1 = getX(forma1);
                    menor_y1 = getY(forma1);
                    maior_y1 = getY(forma1) + getH(forma1);
                    maior_x1 = getX(forma1) + getW(forma1);
                    strcpy(forma1_corb, getCorbRET(forma1));
                    id1 = getIdRetangulo(forma1);

                    }
                    else if (tipo1 == 'l')
                    {
                    menor_x1 = getX1(forma1);
                    menor_y1 = getY1(forma1);
                    maior_x1 = getX2(forma1);
                    maior_y1 = getY2(forma1);
                    strcpy(forma1_corb, getCorLIN(forma1));
                    id1 = getIdlinha(forma1);

                    }
                    else
                    {
                    maior_x1 = menor_x1 = getXtexto(forma1);
                    maior_y1 = menor_y1 = getYtexto(forma1);
                    strcpy(forma1_corb, getStringcorb(forma1));    
                    id1 = getIdtexto(forma1);
                    }

                    //DecrementaRef(gccore, forma1, nx);
                
                    if (tipo2 == 'c')
                    {
                    menor_x2 = getXc(forma2) - getRaio(forma2);
                    menor_y2 = getYc(forma2) - getRaio(forma2);
                    maior_x2 = getXc(forma2) + getRaio(forma2);
                    maior_y2 = getYc(forma2) + getRaio(forma2);
                    strcpy(forma2_corp, getCorpCIR(forma2));
                    }
                    else if (tipo2 == 'r')
                    {
                    menor_x2 = getX(forma2);
                    menor_y2 = getY(forma2);
                    maior_y2 = getY(forma2) + getH(forma2);
                    maior_x2 = getX(forma2) + getW(forma2);
                    strcpy(forma2_corp, getCorpRET(forma2));
                       
                    }
                    else if (tipo2 == 'l')
                    {
                    menor_x2 = getX1(forma2);
                    menor_y2 = getY1(forma2);
                    maior_x2 = getX2(forma2);
                    maior_y2 = getY2(forma2);
                    strcpy(forma2_corp, getCorLIN(forma2));
                       
                    }

                    else
                    {
                    maior_x2 = menor_x2 =  getXtexto(forma2);
                    maior_y2 = menor_y2 = getYtexto(forma2);
                    strcpy(forma2_corp, getStringcorp(forma2)); 
                       
                    }

                    
                    if(menor_x1 < menor_x2)
                    {
                        x_ancora = menor_x1;
                        printf("1.menor x: %lf\n", x_ancora);
                    }

                    else {
                        x_ancora = menor_x2;
                        printf("2.menor x: %lf\n", x_ancora);
                    }

                    if(menor_y1 < menor_y2)
                    {
                       y_ancora = menor_y1;
                        printf("3.menor y: %lf\n",y_ancora);
                    }

                    else {
                        y_ancora = menor_y2;
                        printf("4.menor y: %lf\n", y_ancora);
                    }

                    if(maior_x1 > maior_x2) 
                    {
                        maior_x = maior_x1;
                        printf("5.maior x: %lf\n", maior_x);
                    } 
                    
                    else {
                        maior_x = maior_x2;
                        printf("6.maior x: %lf\n", maior_x);
                    }

                    if(maior_y1 > maior_y2) 
                    {
                        maior_y = maior_y1;
                        printf("7.maior y: %lf\n", maior_y);
                    }

                    else {
                        maior_y = maior_y2;
                        printf("8.maior y: %lf\n",maior_y);
                    }
                    
                    Forma final = CriaStructRetangulo(id, x_ancora, y_ancora, maior_x - x_ancora, maior_y - y_ancora, forma2_corp, forma1_corb);
                    IncrementSize(gccore, 'r');
                    insertNode(lista, final);
                    fprintf(txt, "ATRIBUTOS DO BOUDING BOX:\n(x,y) = (%lf, %lf)\nlargura = %lf\naltura = %lf\nCor preenchimento = %s\nCor borda = %s\n\n", x_ancora, y_ancora, maior_x - x_ancora, maior_y - y_ancora, forma2_corp, forma1_corb);
                    printf("\nx anc: %lf\ny anc: %lf\nw: %lf\nh: %lf\n, %s\n %s\n", x_ancora, y_ancora, maior_x - x_ancora, maior_y - y_ancora, forma2_corp, forma1_corb);

                    if((CopiaDoRegistrador(int_rg) != NULL) && (final != NULL) && (CopiaDoRegistrador(int_rg) != final))
                    {
                        printf("\nDRECEMENTANDO REF DENTRO DA FUNCAO LD\n");
                        DecrementaRef(CopiaDoRegistrador(int_rg));
                    }

                    CarregaRegistrador(final, int_rg);
                    IncrementaRef(final);
                }

                else if(strcmp(comando, "newc") == 0)
                {
                    double xc, yc, raio;
                    char corb[30], corp[30];
                    sscanf(aux, "%s %s %lf %lf %lf %s %s", comando, rg, &xc, &yc, &raio, corb, corp);   
                    Forma forma = CriaStructCirculo(nx + 1, xc, yc, raio, corp, corb);
                    IncrementSize(gccore, 'c');
                    insertNode(lista, forma);

                    int_rg = getRg(rg);

                    if((CopiaDoRegistrador(int_rg) != NULL))
                    {
                        printf("\nDRECEMENTANDO REF DENTRO DA FUNCAO LD\n");
                        DecrementaRef(CopiaDoRegistrador(int_rg));
                    }
                    CarregaRegistrador(forma, int_rg);
                }
            }

        else
        {
            if (*comando == '\n')
            {
                break;
            }
            printf("Comando invalido: %s\n", comando); 
        }

        if (cont % gc == 0) {
            vezes++;
            //ExecutaColeta(lista, gerente);
            ExecutarColeta(lista, gerente);
            //condicao para dar free nas coisas que possuiem referencia zero.
        }
        cont++;
    }

    int exec = cont / gc;
    SetNumeroExecucoes(gccore, vezes);
    printf("\nVEZES QUE O GCCORE FOI ATIVADO = %d\n", vezes);

    printf("NUMERO DE COMANDOS PROCESSADOS PELO QRY = %d\n", cont - 1);

    if(cont > exec)
    {
        printf("Execucoes nao analisadas = %d\n", (cont - 1) - (vezes*gc));
    }
}

