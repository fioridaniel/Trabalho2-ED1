#include "shapebank.h"

typedef struct Node {
    Forma geo;
} Node;

void* InicializaShapeBank(int nx) {
    Node* shapebank = (Node*)malloc(sizeof(Node) * (nx + 1));
    if(shapebank == NULL)
    {
        printf("Erro ao alocar memoria para o shapebank...saindo do programa.\n");
        exit(1);
    }

    for (int i = 0; i <= nx; ++i) {
        shapebank[i].geo = NULL;
    }

    return shapebank;
}

void DepositarNoshape(ShapeBank shapebank, Forma forma, int id) {
    ((Node *)shapebank)[id - 1].geo = forma;
    printf("forma depositada no shapebank\n");
      
}

Forma copiaDoshape(ShapeBank shapebank, int mem) {
    Forma forma = ((Node *)shapebank)[mem - 1].geo;
    return forma;
}

void removerFormaShape(ShapeBank shapebank, int mem) { 
    //free(((Node *)shapebank)[mem - 1].geo);
    ((Node *)shapebank)[mem - 1].geo = NULL;
    printf("Forma removida da posicao %d da memoria\n", mem);
}

void ShapeBankSvgFinal(Forma forma, char tipo_forma, FILE* fsvg) {
        int ref = GetRef(forma);
        char buffer[30];

        printf("ANTES %d\n", ref);

        sprintf(buffer, "%d", ref);
        printf("DEPOIS %s\n", buffer);

        if (tipo_forma == 'c') {
            
            int id = getIdCirculo(forma);
            char *corp = getCorpCIR(forma);
            char *corb = getCorbCIR(forma);
            double xc = getXc(forma);
            double yc = getYc(forma);
            double r = getRaio(forma);

            printf("%d %s %s %lf %lf %lf\n", id, corp, corb, xc, yc, r);

            char deco[100];

            sprintf(deco, " fill=\"%s\" stroke=\"%s\"", corp, corb);
            escreveCirculoSvg(fsvg, xc, yc, r, deco);
            escreveTextoSvg(fsvg, xc, yc, buffer, "fill=\"red\" stroke=\"red\" font-size=\"8\" font-weight=\"normal\" font-family=\"Arial\"");
            //printf("%d %s %lf %lf %lf\n", id, deco, xc, yc, r);

        } else if (tipo_forma == 'r') {

            int id = getIdRetangulo(forma);
            char *corp = getCorpRET(forma);
            char *corb = getCorbRET(forma);
            double X = getX(forma);
            double Y = getY(forma);
            double W = getW(forma);  
            double H = getH(forma);

            printf("%d %s %s %lf %lf %lf %lf\n", id, corp, corb, X, Y, W, H);

            char deco[100];

            sprintf(deco, " fill=\"%s\" stroke=\"%s\"", corp, corb);
            escreveRetanguloSvg(fsvg, X, Y, W, H, deco);
            escreveTextoSvg(fsvg, X, Y, buffer, "fill=\"red\" stroke=\"red\" font-size=\"8\" font-weight=\"normal\" font-family=\"Arial\"");
            //printf("%d %s %lf %lf %lf %lf", id, deco, X, Y, W, H);

        } else if (tipo_forma == 'l') {

            int id = getIdlinha(forma);
            char *corp = getCorLIN(forma);
            double X1 = getX1(forma);
            double Y1 = getY1(forma);
            double X2 = getX2(forma);  
            double Y2 = getY2(forma);
            
            //printf("%d %s %lf %lf %lf %lf\n", id, corp, X1, Y1, X2, Y2);
            escreveTextoSvg(fsvg, X1, Y1, buffer, "fill=\"red\" stroke=\"red\" font-size=\"8\" font-weight=\"normal\" font-family=\"Arial\"");
            escreveLinhaSvg(fsvg, X1, Y1, X2, Y2, corp);

        } else { //condicao do txt
            int id = getIdCirculo(forma);
            double x = getXtexto(forma);
            double y = getYtexto(forma);
            char* corp = getStringcorp(forma);
            char* corb = getStringcorb(forma);
            char* texto = getStringtexto(forma);
            char a = getStringA(forma);

            char deco[50];
            sprintf(deco, "fill=\"%s\" stroke=\"%s\"", corp, corb);
            escreveTextoSvg(fsvg, x, y, texto, deco);
            escreveTextoSvg(fsvg, x, y, buffer, "fill=\"red\" stroke=\"red\" font-size=\"8\" font-weight=\"normal\" font-family=\"Arial\"");
            //printf("id:%d a:%c texto:%s corp:%s corb:%s x:%lf y:%lf\n", id, a, texto, corp, corb, x, y);
        }
    }

    void ReportarTxtShape(ShapeBank shapebank, int mem, FILE* txt) {
        Forma estrutura = ((Node*)shapebank)[mem - 1].geo;
        char tipo_forma = GetTipoGarbage(estrutura);
        //Forma estrutura = GetFormaGarbage(forma);
        printf("tipo:%c\n", tipo_forma);

        fprintf(txt, "Comando del:\n");

        if (tipo_forma == 'c') {
            
            int id = getIdCirculo(estrutura);
            char *corp = getCorpCIR(estrutura);
            char *corb = getCorbCIR(estrutura);
            double xc = getXc(estrutura);
            double yc = getYc(estrutura);
            double r = getRaio(estrutura);

            //printf("%d %s %s %lf %lf %lf\n", id, corp, corb, xc, yc, r);
            fprintf(txt, "id = %d\ncorp = %s\ncorb = %s\nx do centro = %lf\ny do centro = %lf\nraio = %lf\n\n", id, corp, corb, xc, yc, r);

        } else if (tipo_forma == 'r') {

            int id = getIdRetangulo(estrutura);
            char *corp = getCorpRET(estrutura);
            char *corb = getCorbRET(estrutura);
            double X = getX(estrutura);
            double Y = getY(estrutura);
            double W = getW(estrutura);  
            double H = getH(estrutura);

            //printf("%d %s %s %lf %lf %lf %lf\n", id, corp, corb, X, Y, W, H);
            fprintf(txt, "id = %d\ncorp = %s\ncorb = %s\nx = %lf\ny = %lf\nlargura = %lf\naltura = %lf\n\n", id, corp, corb, X, Y, W, H);


        } else if (tipo_forma == 'l') {

            int id = getIdlinha(estrutura);
            char *corp = getCorLIN(estrutura);
            double X1 = getX1(estrutura);
            double Y1 = getY1(estrutura);
            double X2 = getX2(estrutura);  
            double Y2 = getY2(estrutura);
            
            //printf("%d %s %lf %lf %lf %lf\n", id, corp, X1, Y1, X2, Y2);
            fprintf(txt, "id = %d\ncorp = %s\nx1 = %lf\ny1 = %lf\nx2 = %lf\ny2 = %lf\n\n", id, corp, X1, Y1, X2, Y2);

        } else { //condicao do txt
            int id = getIdCirculo(estrutura);
            double x = getXtexto(estrutura);
            double y = getYtexto(estrutura);
            char* corp = getStringcorp(estrutura);
            char* corb = getStringcorb(estrutura);
            char* texto = getStringtexto(estrutura);
            char a = getStringA(estrutura);

            //printf("%d %c %s %s %s %lf %lf\n", id, a, texto, corp, corb, x, y);
            fprintf(txt, "id = %d\na = %c\ntexto = %s\ncorp = %s\ncorb = %s\nx = %lf\ny = %lf\n\n", id, a, texto, corp, corb, x, y);
            
    }
}

char verificarTipoShape(ShapeBank shapebank, int mem) { 
    Forma forma = ((Node*)shapebank)[mem - 1].geo;
    char tipo_forma = GetTipoGarbage(forma);

        if (tipo_forma == 'c') {

            return tipo_forma;

        } else if (tipo_forma == 'r') {

            return tipo_forma;

        } else if (tipo_forma == 'l') {

            return tipo_forma;
            
        } else { //condicao do txt

            return tipo_forma;

        }
    }

int ElseifId(Forma forma) {
    int id;
    char tipo = GetTipoGarbage(forma);

    if(tipo == 'c')
    {
        id = getIdCirculo(forma);
    }
    else if(tipo == 'r')
    {
        id = getIdRetangulo(forma);
    }
    else if(tipo == 'l')
    {
        id = getIdlinha(forma);
    }
    else
    {
        id = getIdtexto(forma);
    }

    return id;
}


