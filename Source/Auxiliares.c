#include <stdio.h>
#include <stdlib.h>
#include "Auxiliares.h"
#include "estado.h"



//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////FUCOES AUXILIARES TROCAR JOGADOR,PECA...  ////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

char troca (char n){               //trocar jogador
    if (n =='X') n = 'O';
    else if (n == 'O' ) n = 'X';
    return n;
}



void playertopeca (char p , ESTADO * pe)     //faz corresponder player 'X' ou 'O' ao respetivo e.peca valor
{
    if (p=='X') (*pe).peca=VALOR_X;
    else if (p=='O') (*pe).peca=VALOR_O;
}


VALOR inverso (VALOR e){               //obter valor inverso
    if (e == VALOR_X) e = VALOR_O;
    else if (e == VALOR_O) e = VALOR_X;
    else if (e == VAZIA) e = VAZIA;
    return e;
}



char corresponde(VALOR a) {             //faz corresponder o valor ao char representante desse valor
    char res[3] = {'-', 'X', 'O'};      //VAZIA = '-' ; VALOR_X = 'X' ; VALOR_O = 'O';
    return res[a];
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////PROCURAR SITUAÇOES FIM DE JOGO / PASSAGEM  ////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


int passar (ESTADO e, char player )   // verificar se tem jogadas disponiveis para o jogador 'player',se der 1 tem jogada disponivel ,se der 0 jogador tem de passar;
{
    int i = 0;
    int j = 0;
    for (i = 0; i <= 7; i++) {
        for (j = 0; j <= 7; j++) {
            if ((valida(e, i,j,player)) == 1) return 1;
        }
    }
    return 0;
}



int fimdejogo (ESTADO e, char player )     // verificar se e possivel qualquer dos dois jogadores jogar, por exemplo se um jogador tiver de passar o outro tem de ser capaz de jogar
{
    int i = 0;
    int j = 0;
    char  p1 = player;
    char  p2 = troca(player);
    for (i = 0; i <= 7; i++) {
        for (j = 0; j <= 7; j++) {
            if ((valida(e, i,j,p1)) == 1) return 1;
        }
    }
    for (i = 0; i <= 7; i++) {
        for (j = 0; j <= 7; j++) {
            if ((valida(e, i,j,p2)) == 1) return 1;
        }
    }
    return 0;

}




void acabou (ESTADO e,char pecabot) {
    int i;         //linha
    int j;         //coluna
    int O = 0;     //variavel para contar pontos da peca 'O'
    int X = 0;    //variavel para contar pontos da peca 'X'

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            switch (e.grelha[i][j]) {
                case VALOR_O: {

                    O++;
                    break;
                }
                case VALOR_X: {
                    X++;
                    break;
                }
            }
        }
    }
    if (e.modo == '1') {               //jogo contra Bots
        if (pecabot=='O'){             //se o bot for 'O'
        if (O > X) printf("\n     ||||||| O Bot com a peca 'O' Venceu! ||||||||");
        if (O < X) printf("\n     ||||||| O jogador com a peca 'X' Venceu! |||||||");}
        if (pecabot=='X'){             // se o bot for 'X'
            if (O < X) printf("\n     ||||||| O Bot com a peca 'X' Venceu! ||||||||");
            if (O > X) printf("\n     ||||||| O jogador com a peca 'O' Venceu! |||||||");}

        if (O == X) printf("\n     ||||||||||Empate|||||||||");
    } else {                          //jogo normal
    if (O > X) printf("\n     ||||||| O jogador com a peca 'O' Venceu! ||||||||");
    if (O < X) printf("\n     ||||||| O jogador com a peca 'X' Venceu! |||||||");
    if (O == X) printf("\n     ||||||||||Empate|||||||||");
    }
}










//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////        STACK        //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


pstack stackinic (pstack * pps)  //iniciar stack nula
{
    freeall (*pps);
    (*pps) = NULL;
    return (*pps);
}



void freeall ( pstack l)    //limpar stack
{

    pstack ant = l;        //apontadores ant e now para a stack l
    pstack now = l;
    while (now != NULL)
    {
        ant = now;          //ant aponta para now
        now = now->prox;    // now aponta para o elemento seguinte da stack
        free(ant);
    }

}



int push(ESTADO e, pstack* pps)   //Inserir um estado na stack, criando um novo nodo e colocando o apontador que indica o topo a apontar para o novo nodo
        {
    pstack novo;
    int r = 0;

    novo = malloc(sizeof(struct Nodee));   //criar um novo nodo e alocar memoria
    if (novo == NULL)
    {
        r = 1;               //deu erro
    }
    if (novo != NULL)
    {
        novo -> e = e;
        novo -> prox = (*pps);
        (*pps) = novo;

    }
    return r;
}




ESTADO pop (pstack* pps)   //retirar o elemento no topo da stack e dar return desse ESTADO
{
    pstack eliminar;
    eliminar = (*pps);
    ESTADO ant;
    ant = (*pps)->e;       //ESTADO ant fica igual ao ESTADO no topo da stack
    (*pps) = (*pps)->prox;    //topo da stack passa a ser o nodo seguinte
    free (eliminar);           //free do nodo que era o topo da stack
    return ant;               // return do ESTADO ant
}


int isempty (pstack* pps)     // se tiver vazia = 1
{
    int r = 0;
    if ((*pps) == NULL) r =1;
    return r;
}

///////////////////////LIMPAR TABULEIRO ///////////////////////

ESTADO limpar ( ESTADO * f)     //limpar ESTADO
{
    ESTADO e;
    e = *f;
    int i,j;
    for ( i = 0; i < 8 ; i++)
    {
        for ( j = 0; j < 8 ; j++)
        {
            e.grelha[i][j] = VAZIA;
        }
    }
    e.peca = VALOR_X;
    e.modo = 0;
    e.nivel = 0;
    return e;
}