#ifndef PROJ_ESTADO_H
#define PROJ_ESTADO_H




/**
estado.h
Definição do estado i.e. tabuleiro. Representação matricial do tabuleiro.
*/




// definição de valores possiveis no tabuleiro
typedef enum {VAZIA, VALOR_X, VALOR_O} VALOR;





/**
Estrutura que armazena o estado do jogo
*/


typedef struct estado {
    VALOR peca;// peça do jogador que vai jogar!
    VALOR grelha[8][8];
    char modo;      // modo em que se está a jogar! 0-> manual, 1-> contra computador
    char nivel;      //nivel do bot 1-3      0 se for Manual
} ESTADO;





//////////////// stack para a funçao undo //////////

struct Nodee {
    ESTADO e;
    struct Nodee* prox;
};

typedef struct Nodee* pstack;             // pstack é um POINTER para Nodee

struct Nodee* ps;                         // ps é o nosso pointer para stack aqui declarado






////////////////////////// FUNCOES ////////////////////////


void interpreta ();



////////////////////////JOGADAS E VALIDA/////////////////

ESTADO jogada ( int L , int C , ESTADO e,char player);
int valida (ESTADO e, int x, int y,char player);
int validale (ESTADO e, int x, int y,char player);
int validald (ESTADO e, int x, int y,char player);
int validacc (ESTADO e, int x, int y,char player);
int validacb (ESTADO e, int x, int y,char player);
int validad1 (ESTADO e, int x, int y,char player);
int validad2 (ESTADO e, int x, int y,char player);
int validad3 (ESTADO e, int x, int y,char player);
int validad4 (ESTADO e, int x, int y,char player);



//////////////////////BOTS ////////////////////////////////

ESTADO jogarbot (ESTADO *f, char pecabot);
int ponttabuleiro( ESTADO e, char player);

int minimax (ESTADO e, int altura, int alpha, int beta, char maximizante, int * xx, int *yy, char pecabot);


#endif //PROJ_ESTADO_H