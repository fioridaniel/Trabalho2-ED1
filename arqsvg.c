#include <stdio.h>
#include "arqsvg.h"

ArqSvg abreEscritaSvg(char *fn) {
  ArqSvg fsvg = (FILE*)fopen(fn, "w");

  if(fsvg == NULL) {
  return NULL;
  }

  fprintf(fsvg, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
  return fsvg;
}

void escreveCirculoSvg(ArqSvg fsvg, double xc, double yc, double r, char *deco) {
  fprintf(fsvg, "  <circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\"%s />\n", xc, yc, r, deco);
}

void escreveRetanguloSvg(ArqSvg fsvg, double x, double y, double larg, double alt, char *deco) {
  fprintf(fsvg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\"%s />\n", x, y, larg, alt, deco);
}

void escreveLinhaSvg(ArqSvg fsvg, double x1, double y1, double x2, double y2, char *deco) {
  fprintf(fsvg, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:%s; stroke-width:1\" />\n", x1, y1, x2, y2, deco);
}
  //exemplo para deco: char *deco = "stroke:green; stroke-width:2"

void escreveTextoSvg(ArqSvg fsvg, double x, double y, char *txt, char *decoTxt) {
  fprintf(fsvg, "  <text x=\"%lf\" y=\"%lf\" %s>%s</text>\n", x, y, decoTxt, txt);
  printf("CONFIRMANDO \n%s\n", txt);
  // fprintf(fsvg, "  <text x=\"%lf\" y=\"%lf\" font-size=\"%s\" font-weight=\"%s\" font-family=\"%s\" %s>%s</text>\n", x, y, fontSize, fontWeight, fontFamily, decoTxt, txt);
}

void fechaSvg(ArqSvg fsvg) {
  fprintf(fsvg, "</svg>");
  fclose(fsvg);
}
