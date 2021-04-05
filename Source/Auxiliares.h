
#ifndef PROJETOO_C_AUXILIARES_H
#define PROJETOO_C_AUXILIARES_H

#include "estado.h"



///////////////////FUNCOES AUXILIARES PARA TROCAR JOGADOR / PECAS...///////////////////////////
void playertopeca (char p , ESTADO * pe);
VALOR inverso (VALOR e);
char troca (char n);
char corresponde(VALOR a);






//////////////////////FUNCOES PARA VER SE O JOGADOR TEM DE PASSAR E SE O JOGO ACABOU/////////
int passar (ESTADO e, char player );
void acabou (ESTADO e, char pecabot);
int fimdejogo (ESTADO e, char player );




/////////////////////////////////STACK UNDO////////////////////////////////////////////////////
void freeall ( pstack ps);
pstack stackinic (pstack * pps);
int push(ESTADO e, pstack* pps);
int isempty (pstack* pps);
ESTADO pop (pstack* pps);



////////////////////////////////LIMPAR TABULEIRO////////////////////////////////////////////////////

ESTADO limpar ( ESTADO * f);



#endif //PROJETOO_C_AUXILIARES_H
