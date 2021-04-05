#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Auxiliares.h"
#include "estado.h"
#include "Printas.h"






//////////////////// FUNCAO PRINTA PARA IMPRIMIR O TABULEIRO//////////////////////////////////


void printa(ESTADO e)
{
    char c = ' ';

    printf("  1 2 3 4 5 6 7 8\n");
    for (int i = 0; i < 8; i++) {
        printf ("%d ",i+1);
        for (int j = 0; j < 8; j++) {
            switch (e.grelha[i][j]) {

                case (VALOR_O): {
                    c = 'O';
                    break;
                }
                case VALOR_X: {
                    c = 'X';
                    break;
                }
                case VAZIA: {
                    c = '-';
                    break;
                }
            }
            printf("%c ", c);

        }
        printf("\n");
    }

}

//////////////////// FUNCAO SCORE IMPRIME A PONTUAÇAO DOS JOGADORES NO ECRA//////////////////////////////////

void score (ESTADO e){
    int i;int j;int r=0;int r2=0;

    for ( i = 0; i < 8; i++) {
        for ( j = 0; j < 8; j++) {
            switch (e.grelha[i][j]) {
                case VALOR_O: {

                    r++;
                    break;
                }
                case VALOR_X: {
                    r2++;
                    break;
                }
            }
        }
    }

    printf("Score Jogador1 (O): %d                       Score Jogador2 (X): %d     \n\n", r,r2);
}





//////////////////// FUNCAO PRINTH PARA IMPRIMIR O TABULEIRO COM AJUDA (?)//////////////////////////////////
// mostra a primeira jogada valida

void printh(ESTADO e,char player) {
    char c = ' '; int k = 0;
    printf("  1 2 3 4 5 6 7 8\n");
    for (int i = 0; i < 8; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < 8; j++) {
            switch (e.grelha[i][j]) {
                case VALOR_O: {
                    c = 'O';
                    break;
                }
                case VALOR_X: {
                    c = 'X';
                    break;
                }
                case VAZIA: {
                    if ((k==0) && (valida(e, i, j,player))) {c = '?'; k = 1;}
                    else c = '-';
                    break;
                }
            }
            printf("%c ", c);

        }
        printf("\n");
    }
}






//////////////////// FUNCAO PRINTS PARA IMPRIMIR O TABULEIRO COM SUGESTOES//////////////////////////////////
// mostra todas as possições validas para jogar

void prints(ESTADO e,char player) {
    char c = ' ';
    printf("  1 2 3 4 5 6 7 8\n");
    for (int i = 0; i < 8; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < 8; j++) {
            switch (e.grelha[i][j]) {
                case VALOR_O: {
                    c = 'O';
                    break;
                }
                case VALOR_X: {
                    c = 'X';
                    break;
                }
                case VAZIA: {
                    if (valida(e, i, j,player)) c = '.';
                    else c = '-';
                    break;
                }
            }
            printf("%c ", c);

        }
        printf("\n");
    }
}



//////////////////FUNCAO ESCREVE PARA GRAVAR O ESTADO DO JOGO EM FICHEIRO///////////////////////////



void escreve(char f[],ESTADO e, char player) {
    char modo;                // para guardar o modo a escrever
    char x = ' ';             // auxiliar para guardar as peças em cada posição
    int l, c;                 // l e c sao coordenadas das jogadas
    FILE *fp;
    fp = fopen(f, "w");
    if(e.modo=='0') {modo='M'; fprintf(fp, "%c %c\n", modo, player);}  // verificamos o modo de jogo  em caso de ser contra bots grava o nivel do bot
    else {modo='A'; fprintf(fp, "%c %c %c\n", modo, player,e.nivel);}
    for (l = 0; l < 8; l++) {
        for (c = 0; c < 8; c++) {
            switch (e.grelha[l][c]) {
                case VALOR_O: {
                    x = 'O';
                    break;
                }
                case VALOR_X: {
                    x = 'X';
                    break;
                }
                case VAZIA: {
                    x = '-';
                    break;
                }
            }
            if (c == 7) fprintf(fp,"%c\n", x);      // caso seja na coluna 7 escreva '\n' caso contrario um ' '
            else fprintf(fp,"%c ", x);

        }
    }
    fclose(fp);
}







//////////////////FUNCAO ABRE PARA ABRIR UM JOGO CUJO ESTADO ESTA GRAVADO NUM FICHEIRO //////////////////////


ESTADO abre (char f[], char *player) {
    ESTADO e = {0};
    char r, m;   // r-guarda a peça de cada posição, m-guarda o modo
    FILE *fp;
    int l, c;     // l e c sao coordenadas das jogadas
    fp = fopen(f, "r");
    fscanf(fp, "%c", &m);
    fscanf(fp, " %c", player);

    if (m=='A') { e.modo='1';
        fscanf(fp, " %c", &e.nivel);  // verifica se o jogo e contra bots para ir ao ficheiro retirar o nivel do bot
    }
    if (m == 'M')
    {
        e.modo = '0';
        e.nivel = '0';
    }

    if(*player =='X') e.peca=VALOR_X;        // guarda a peça no ESTADO e
    else if (*player=='O') e.peca=VALOR_O;




    for (l = 0; l < 8;l++) {
        for (c = 0; c < 8; c++) {
            fscanf(fp, "%s ", &r);

            switch (r) {
                case 'X': {
                    e.grelha[l][c] = VALOR_X;
                    break;
                }
                case 'O': {
                    e.grelha[l][c] = VALOR_O;
                    break;
                }
                case '-': {
                    e.grelha[l][c] = VAZIA;
                    break;
                }
            }
        }
    }
    fclose(fp);
    return e;
}
ESTADO torneio (int *argc, char argv[],char *pecabot) {ESTADO e = {0};
    FILE *file;
    char *ficheiro = &argv[0];
    char linha[20];
    char player = ' ';
    file = fopen(ficheiro, "r");
    if (file != NULL) {
        *argc = 0;
// tabuleiro existente
        e = abre(ficheiro, &player);
        if (player=='O') {e.peca = VALOR_O;*pecabot='O';}
        else {e.peca = VALOR_X;*pecabot = 'X';}
        fclose(file);}

    else {
// tabuleiro inexistente
// criar novo tabuleiro
// ...
        *argc = 1;
        file = fopen(ficheiro, "w");
        if (file != NULL) {
            fputs("A X 3\n", file);
            fputs("- - - - - - - -\n", file);
            fputs("- - - - - - - -\n", file);
            fputs("- - - - - - - -\n", file);
            fputs("- - - X O - - -\n", file);
            fputs("- - - O X - - -\n", file);
            fputs("- - - - - - - -\n", file);
            fputs("- - - - - - - -\n", file);
            fputs("- - - - - - - -\n", file);
            fclose(file);
        } else {
            printf("Erro ao criar o ficheiro %s. Certifique-se que tem permissões.\n", ficheiro);
        }
    }
    return e;
}

