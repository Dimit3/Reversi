#ifndef PROJETOO_C_PRINTAS_H
#define PROJETOO_C_PRINTAS_H


#include "estado.h"





////////////////////////////////////////////////////////////////////////////////////////
/////////////////////FUNCOES PARA IMPRIMIR TABULEIROS, GRAVAR E LER/////////////////////
////////////////////////////////////////////////////////////////////////////////////////




void printa(ESTADO);
void score (ESTADO);
ESTADO abre (char f[], char *player);
void escreve(char f[],ESTADO e, char player);
void prints(ESTADO e,char player);
void printh(ESTADO e,char player);
ESTADO torneio (int *argc, char argv[],char *pecabot);









#endif //PROJETOO_C_PRINTAS_H


