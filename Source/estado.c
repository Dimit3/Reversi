#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Printas.h"
#include "estado.h"
#include "Auxiliares.h"


void interpreta ()
{
    char linha[50];   //string para guardar o comando
    char outra[50];   //string auxiliar para o comando
    int L,C, v, erro,fdj,P;  // L e C sao coordenadas das jogadas, v vai ter 0 ou 1 dependendo se a jogada é valida
                            // erro tem 0 ou 1 se der erro no push / malloc, fjd- é fim de jogo ou nao tem 1 ou 0
                            // P o jogador tem de passar ou nao tem 1 ou 0

    char player = ' ', p2;  // o jogador e o jogador 2
    char c = '0';          // caracter do comando lido vai ser usado no switch
    ESTADO (e) = {0};      // criar um estado novo
    int z = 0;             // auxiliar na undo caso ainda nao tenhamos feito um jogo novo
int zzz = 0;
    ///bot///
    char pecabot;         // peça que o bot ta a usar
    char nivel;           //nivel dificuldade do bot

    ///BOT///

    do
    {

        printf ("%c>",player);                         //colocar x>  ou  o> antes do comando para saber quem é a jogar
        gets ( linha );                               // guardar o comando em linha
        sscanf (linha ,"%c %s", &c , outra);          // ler a linha guardando a primeira parte em c para fazer switch e a segunda parte em outra para ser depois usada
        c = toupper(c);


        switch (c) {

            case 'N' :

                if (z != 0) {
                    playertopeca(player, &e);
                    erro = push(e,&ps);
                    if (erro == 1) {
                        printf("Malloc falou!");
                        break;
                    }
                }

                e = limpar(&e);                       // limpar o estado
                sscanf(outra, "%c", &player);        // ir buscar o primeiro jogador
                player = toupper(player);
                playertopeca(player, &e);           // fazer corresponder jogador ao e.peca
                printf("Novo jogo em que o primeiro a jogar e o jogador com peca %c \n ", player);
                z++;                                // esta variável z é para saber se a stack tá vazia ou nao depois de jogarmos uma primeira vez pois apenas fazemos push no case J
                e.grelha[3][4] = VALOR_X;
                e.grelha[4][3] = VALOR_X;
                e.grelha[3][3] = VALOR_O;
                e.grelha[4][4] = VALOR_O;
                if (erro == 1) {
                    printf("Malloc falou!");
                    break;
                }
                score(e);        // colocar pontuaçao
                printa(e);       // colocar tabuleiro
                e.modo = '0';
                break;


            case 'L' :

                playertopeca(player, &e);
                if (z != 0) erro = push(e, &ps);              // fazer push do tabuleiro anterior na stack
                if (erro == 1) {
                    printf("Malloc falou!");
                    break;
                }

                e = abre(outra, &player);                      // abrir o novo ficheiro
                pecabot = troca(player);
                score(e);
                printa(e);
                z++;
                break;

            case 'E' :

                escreve(outra, e, player);        // guardar o tabuleiro
                score(e);
                printa(e);
                printf("Jogo guardado com sucesso \n");
                break;


            case 'J' :
                playertopeca(player, &e);
                sscanf(linha, "%*c %d %d", &L, &C);                      // pegar nas coordenadas da jogada
                printf("Jogou em: L = %d, C = %d \n", L, C);             // dizer onde foi jogado
                v = valida(e, L - 1, C - 1, player);                    // validar a jogada se for invalida vai dar erro
                if (v == 0) {
                    printf("Jogada invalida");
                    break;
                }


                erro = push(e, &ps);                                   // push do tabuleiro anterior na stack
                if (erro == 1) {
                    printf("Malloc falou!");
                    break;
                }


                e = jogada(L, C, e, player);                         // jogar e mudar tabuleiro
                score(e);
                printa(e);

                p2 = troca(player);                                  //esta parte vai ver se o proximo jogador tem de passar
                if (e.modo == '0')
                    P = passar(e, p2);
                if (e.modo == '1')
                    P = passar(e, pecabot);


                fdj = fimdejogo(e, player);                         // vai ver se é fim de jogo
                if (fdj == 0) {
                    acabou(e, pecabot);
                    break;
                }
                if (P == 0) printf("O jogador %c passou", p2);    // caso o jogador tenha passado se for return 0 quer dizer que passou ,return 1 continua
                if (P == 1) {
                    player = troca(player);
                    e.peca = inverso(e.peca);
                }



                if (e.modo == '1') {            // se for contra bot

                    if (P == 1) {               // se o bot nao passou vai jogar
                        bot:                    // bot inicio usado para um goto
                        printf("\n");
                        system("pause");            // achamos melhor colocar uma pausa para ser mais facil de seguir
                        e = jogarbot(&e, pecabot);  // o bot vai jogar
                        score(e);
                        printa(e);

                        p2 = troca(player);
                        P = passar(e, p2);               // vai ver se o jogador humano tem de passar
                        fdj = fimdejogo(e, player);
                        player = troca(player);
                        e.peca = inverso(e.peca);
                        if (fdj == 0) {                   // se for situaçao de fim de jogo
                            acabou(e, pecabot);
                            break;
                        }
                        if (P == 0) {
                            printf("O jogador %c passou", p2);
                            player = troca(player);
                            e.peca = inverso(e.peca);
                            goto bot;                            // se o jogador tiver de passar o bot vai jogar denovo
                        }


                    }
                }
                break;


            case 'S' :
                score(e);
                prints(e,player);
                break;

            case 'H' :
                score(e);
                printh( e, player);
                break;

            case 'U' :
                if ((isempty(&ps)==1)) {printf("Ja esta no estado inicial"); break;}
                e = pop(&ps);
                score(e);
                printa(e);
                player = corresponde(e.peca);
                break;

            case 'A' :
                playertopeca(player,&e);                               // fazer corresponder o player ao e.peca
                if (z!=0){
                    erro = push (e,&ps);                               // push na stack
                    if (erro == 1) {printf("Malloc falou!");break;}
                }
                e = limpar (&e);                                      // limpar o tabuleiro
                printf("JOGO CONTRA BOT\n");
                sscanf(linha,"%*c %c %c",&pecabot,&nivel);            // pegar na peca do bot e no nivel
                pecabot = toupper(pecabot);
                player = troca(pecabot);                              //player é o inverso da peca do bot
                playertopeca(player,&e);                              // fazer corresponder o player ao e.peca
                e.modo  = '1';
                e.nivel = (char) nivel;
                e.grelha[3][4] = VALOR_X;
                e.grelha[4][3] = VALOR_X;
                e.grelha[3][3] = VALOR_O;
                e.grelha[4][4] = VALOR_O;
                score(e);
                printa (e);

                if (pecabot == 'X')                             // se o bot for o X ele vai jogar primeiro
                {
                    playertopeca(pecabot,&e);
                    system("pause");                            // fizemos uma pausa antes do o bot jogar para ser mais facil do jogador seguir o jogo
                    e = jogarbot(&e , pecabot);                // chamar a funçao do bot jogar
                    score(e);
                    printa(e);
                    z++;
                    e.peca = VALOR_O;
                }

                break;

            case 'C':
                e = torneio (&zzz,outra,&pecabot);
                if (zzz == 0){
                    P = passar(e, pecabot);
                    if (P == 0) printf("O jogador %c passou", p2);    // caso o jogador tenha passado se for return 0 quer dizer que passou ,return 1 continua
                    if (P == 1) {
                        pecabot = troca(pecabot);        }
                    break;
                }
                    e = jogarbot(&e , pecabot);
                    erro = push(e, &ps);                                   // push do tabuleiro anterior na stack
                    if (erro == 1) {
                        printf("Malloc falou!");}

                    printa (e);
                    score(e);
                    escreve (outra,e,troca(pecabot));
                    fdj = fimdejogo(e, pecabot);                         // vai ver se é fim de jogo
                    if (fdj == 0) {
                        acabou(e, pecabot);
                        break;
                    }

                else printf ("Jogo Criado");

                break;


            case 'Q' :
                printf ("Sair \n");
                freeall(ps);                         // fazer free á stack toda
                exit(0);


            default  :  printf ("invalido"); break;


        }
        printf("\n");

    } while ( c != 'Q');
}




////////////////////////////////////////////////////////////////////////////////////////
////////////////////////FUNCAO PARA VALIDAR A JOGADA////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////





int validale (ESTADO e, int x, int y, char player)             // valida linha do lado esquerdo
{
    char p,g;                                                 // p vai ter o jogador atual g vai ter o oponente
    int i = 0;                                                // i é o indice para percorrer
    if (player == 'X') p = VALOR_X;
    else if (player == 'O') p= VALOR_O;

    g = inverso(p);

    if (e.grelha[x][y - 1] == g) {                         // se o valor ao lado esquerdo na linha for o inverso vai continuar senao dá logo return a 0
        i = y-1;                                           // i começa na "casa" á esquerda de onde for jogado (linha - 1)
        while (i > 0 && e.grelha[x][i] == g) {            // decrementando o i enquanto for igual ao inverso da peca jogada
            i--;
        }
        if (e.grelha[x][i] == p) return 1;               // dá return 1 se o proximo for uma peça igual á que foi jogada inicialmente
    }
    return 0;
}


int validald (ESTADO e, int x, int y,char player)         // valida linha do lado direito
{
    char p,g;                                                 // p vai ter o jogador atual g vai ter o oponente
    int i = 0;                                                // i é o indice para percorrer
    if (player == 'X') p = VALOR_X;
    else if (player == 'O') p= VALOR_O;

    g=inverso(p);

    if (e.grelha[x][y + 1] == g) {                         // se o valor ao lado direito na linha for o inverso vai continuar senao dá logo return a 0
        i = y+1;                                           // i começa na "casa" á direita de onde for jogado (linha + 1)
        while (i < 7 && e.grelha[x][i] == g) {            // incrementado o i enquanto for igual ao inverso da peca jogada
            i++;
        }
        if (e.grelha[x][i] == p) return 1;               // dá return 1 se o proximo for uma peça igual á que foi jogada inicialmente

    }
    return 0;
}


int validacb (ESTADO e, int x, int y,char player)               // valida coluna para baixo
{
    char p,g;                                                 // p vai ter o jogador atual g vai ter o oponente
    int i = 0;                                                // i é o indice para percorrer
    if (player == 'X') p = VALOR_X;
    else if (player == 'O') p= VALOR_O;

    g=inverso(p);

    if (e.grelha[x + 1][y] == g) {                         // se o valor em baixo na coluna for o inverso vai continuar senao dá logo return a 0
        i = x+1;                                           // i começa na "casa" em baixo de onde for jogado (linha + 1)
        while (i < 7 && e.grelha[i][y] == g) {            // incrementando o i enquanto for igual ao inverso da peca jogada
            i++;
        }
        if (e.grelha[i][y] == p)  return 1;               // dá return 1 se o proximo for uma peça igual á que foi jogada inicialmente
    }
    return 0;

}

int validacc (ESTADO e, int x, int y,char player)               // valida coluna para cima
{
    char p,g;                                                 // p vai ter o jogador atual g vai ter o oponente
    int i = 0;                                                // i é o indice para percorrer
    if (player == 'X') p = VALOR_X;
    else if (player == 'O') p= VALOR_O;

    g=inverso(p);

    if (e.grelha[x - 1][y] == g) {                         // se o valor em cima na coluna for o inverso vai continuar senao dá logo return a 0
        i = x-1;                                           // i começa na "casa" em cima de onde for jogado (linha - 1)
        while (i > 0 && e.grelha[i][y] == g) {            // decrementado o i enquanto for igual ao inverso da peca jogada
            i--;
        }
        if (e.grelha[i][y] == p)  return 1;               // dá return 1 se o proximo for uma peça igual á que foi jogada inicialmente

    }
    return 0;

}

int validad1 (ESTADO e, int x, int y,char player)  // l-- c --             diagonal 1        NO
{
    char p,g;                                                             // p vai ter o jogador atual g vai ter o oponente
    int i = x-1, j = y-1 ;                                               // i e j sao os indices para percorrer começam ambos em jogada - 1  (Noroeste)
    if (player == 'X') p = VALOR_X;
    else if (player == 'O') p= VALOR_O;

    g=inverso(p);

        if (e.grelha[x - 1][y - 1] == g) {                         // se o valor a Noroeste de onde for jogado for igual ao inverso continua senao da return a 0

        while (i > 0 && j > 0 && e.grelha[i][j] == g)          // decrementando ambos enquanto for igual ao inverso da peca jogada
        {
            i--;
            j--;

        }
        if (e.grelha[i][j] == p) return 1;                    // dá return 1 se o proximo for uma peça igual á que foi jogada inicialmente
    }
    return 0;
}

int validad2 (ESTADO e, int x, int y,char player)  // l-- c ++          diagonal 2       SO
{
    char p,g;                                                             // p vai ter o jogador atual g vai ter o oponente
    int i = x-1, j = y +1;                                               // i e j sao os indices para percorrer   vao para (Sudoeste)
    if (player == 'X') p = VALOR_X;
    else if (player == 'O') p= VALOR_O;
    g=inverso(p);
    if (e.grelha[x - 1][y + 1] == g) {                         // se o valor a Sudoeste de onde for jogado for igual ao inverso continua senao da return a 0

        while (i > 0 && j < 7 && e.grelha[i][j] == g)          // decrementamos o i e incrementamos o j enquanto for igual ao inverso da peca jogada
        {
            i--;
            j++;

        }
        if (e.grelha[i][j] == p)  return 1;                    // dá return 1 se o proximo for uma peça igual á que foi jogada inicialmente
    }
    return 0;
}


int validad3 (ESTADO e, int x, int y,char player)  // l++ c --           diagonal 3   NE
{
    char p,g;                                                             // p vai ter o jogador atual g vai ter o oponente
    int i = x+1, j = y-1 ;                                               // i e j sao os indices para percorrer     para (Nordeste)
    if (player == 'X') p = VALOR_X;
    else if (player == 'O') p= VALOR_O;

    g=inverso(p);

    if (e.grelha[x + 1][y - 1] == g) {                         // se o valor a Nordeste de onde for jogado for igual ao inverso continua senao da return a 0

        while (i < 7 && j > 0&& e.grelha[i][j] == g)          // decrementamos o j e incrementamos o i enquanto for igual ao inverso da peca jogada
        {
            i++;
            j--;

        }
        if (e.grelha[i][j] == p)  return 1;
    }
    return 0;
}

int validad4 (ESTADO e, int x, int y,char player)  // l++ c ++            diagonal 4    SE
{
    char p,g;                                                             // p vai ter o jogador atual g vai ter o oponente
    int i = x+1, j = y+1 ;                                                // i e j sao os indices para percorrer     para (Sudeste)
    if (player == 'X') p = VALOR_X;
    else if (player == 'O') p= VALOR_O;

    g=inverso(p);

    if (e.grelha[x + 1][y + 1] == g) {                      // se o valor a Sudeste de onde for jogado for igual ao inverso continua senao da return a 0

        while (i < 7 && j < 7&& e.grelha[i][j] == g)          // incrementamos ambos enquanto for igual ao inverso da peca jogada
        {
            i++;
            j++;

        }
        if (e.grelha[i][j] == p)  return 1;
    }
    return 0;
}



// funçao valida explica em mais detalhe no relatorio
// esta funçao vai validar a jogada dando return a 1 se for valida ou a 0 se nao for


int valida (ESTADO e, int x, int y,char player)
{

    if (e.grelha[x][y] != VAZIA) return 0;                     // se onde o jogador for jogar nao for vazio é invalido

    if (validale(e,x,y,player)  || validald(e,x,y,player)  || validacc(e,x,y,player)|| validacb(e,x,y,player)
        || validad1 (e,x,y,player) || validad2 (e,x,y,player) || validad3 (e,x,y,player) || validad4(e,x,y,player) )
        return 1;           // se qualquer uma das validas auxiliares der return a 1 a valida principal vai dar return a 1 também senão a 0
    else return 0;


}







////////////////////////////////////////////////////////////////////////////////////////
////////////////////////FUNCAO PARA JOGAR A PECA E TROCAR AS PECAS//////////////////////
////////////////////////////////////////////////////////////////////////////////////////

ESTADO jogada (int L , int C ,ESTADO e ,char player){


    if (player == 'X') e.grelha [L-1][C-1] = VALOR_X;
    else e.grelha [L-1][C-1] = VALOR_O;

    char  p = e.grelha[L-1][C-1];
    char g = inverso (p);
    if(validale(e,L-1,C-1,player)) {
        int l = L -1;
        int c = C -1;
        while (e.grelha [l][c-1] == g && c >= 0){
            e.grelha [l][c-1] = e.grelha [L-1][C-1];
            c--;

        }
    }
    if(validald(e,L-1,C-1,player)) {
        int l = L -1;
        int c = C -1;
        while (e.grelha [l][c+1] == g && c < 8){
            e.grelha [l][c+1] = e.grelha [L-1][C-1];
            c++;

        }
    }
    if(validacc(e,L-1,C-1,player)) {
        int l = L -1;
        int c = C -1;
        while (e.grelha [l-1][c] == g && l >= 0){
            e.grelha [l-1][c] = e.grelha [L-1][C-1];
            l--;

        }
    }
    if(validacb(e,L-1,C-1,player)) {
        int l = L -1;
        int c = C -1;
        while (e.grelha [l+1][c] == g && l < 8){
            e.grelha [l+1][c] = e.grelha [L-1][C-1];
            l++;

        }
    }
    if(validad1(e,L-1,C-1,player)) {
        int l = L -1;
        int c = C -1;
        while (e.grelha [l-1][c-1] == g && l >= 0 && c>=0){
            e.grelha [l-1][c-1] = e.grelha [L-1][C-1];
            l--;c--;

        }
    }
    if(validad2(e,L-1,C-1,player)) {
        int l = L -1;
        int c = C -1;
        while (e.grelha [l-1][c+1] == g && l >= 0 && c<8){
            e.grelha [l-1][c+1] = e.grelha [L-1][C-1];
            l--;c++;

        }
    }
    if(validad3(e,L-1,C-1,player)) {
        int l = L -1;
        int c = C -1;
        while (e.grelha [l+1][c-1] == g && l < 8 && c>=0){
            e.grelha [l+1][c-1] = e.grelha [L-1][C-1];
            l++;c--;

        }
    }
    if(validad4(e,L-1,C-1,player)) {
        int l = L -1;
        int c = C -1;
        while (e.grelha [l+1][c+1] == g && l < 8 && c<8){
            e.grelha [l+1][c+1] = e.grelha [L-1][C-1];
            l++;c++;

        }
    }

    return e;
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////            BOTS         /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


// pontos das posiçoes do tabuleiro
int pontos[8][8] = {{99,-8,8,6,6,8,-8,99},
                    {-8,-24,-4,-3,-3,-4,-24,-8},
                    {8,-4,7,4,4,7,-4,8},
                    {6,-3,4,0,0,4,-3,6},
                    {6,-3,4,0,0,4,-3,6},
                    {8,-4,7,4,4,7,-4,8},
                    {-8,-24,-4,-3,-3,-4,-24,-8},
                    {99,-8,8,6,6,8,-8,99}};




// esta função faz a conta de quanto vale o tabuleiro
int ponttabuleiro(ESTADO e,char player){
    int l,c,r=0;
    for (l=0;l<8;l++){
        for(c=0;c<8;c++){
            if (((e.grelha[l][c] == VALOR_X)&&(player == 'X'))||((e.grelha[l][c] == VALOR_O)&&(player == 'O'))) r = r + pontos[l][c];
            else if (((e.grelha[l][c] == VALOR_O)&&(player=='X'))||((e.grelha[l][c] == VALOR_X)&&(player=='O'))) r = r - pontos[l][c];
        }
    }
    return r;
}


// esta funçao faz corresponder o nivel do bot a cada algoritmo que vai usar
// se for nivel 1 vai jogar na primeira jogada valida
// nivel 2 vai usar a funçao minimax mais abaixo com altura 1
// nivel 3 vai usar a funçao minimax altura 3


ESTADO jogarbot (ESTADO *f, char pecabot)
{


    ESTADO e = *f;

    // EASY // joga na primeira jogada valida
    int i,j,v;


    if (e.nivel == '1')
    {
        for (i = 0; i < 8; i++)
        {
            for (j = 0; j < 8; j++)
            {
                v = valida(e , i , j , pecabot);
                if (v == 1)
                {
                    e = jogada(i + 1 , j + 1 , e , pecabot);
                    printf("O BOT jogou em: L = %d, C = %d \n",i+1,j+1);
                    goto fim;
                }
            }
        }
    }

    // FIM EASY //

    //  MEDIO  //       altura 1

    int xx,yy;


    if (e.nivel == '2')
    {
        minimax (e,  1, (int) -INFINITY, (int) +INFINITY, 'T', &xx, &yy,pecabot);
        e = jogada(xx+1,yy+1,e,pecabot);
        printf("O BOT jogou em: L = %d, C = %d \n",xx+1,yy+1);
    }

    // FIM MEDIO //


    // DIFICIL //       altura 3


    if (e.nivel == '3')
    {
        minimax (e,  3, (int) -INFINITY, (int) +INFINITY, 'T', &xx, &yy,pecabot);
        e = jogada(xx+1,yy+1,e,pecabot);
        printf("O BOT jogou em: L = %d, C = %d \n",xx+1,yy+1);
    }


    // FIM DIFICIL //

    fim:
    return e;
}




#define MAXIMO(a,b) ((a>=b)?a:b)
#define MINIMO(a,b) ((a<=b)?a:b)





// funçao minimax usada para fazer os bots jogarem está explicada em mais detalhe no relatório

int minimax (ESTADO e, int altura,int alpha , int beta, char maximizante , int *xx, int * yy, char pecabot)
{
    int valortab,valormax,valortabmin,valormin,i ,j;               // valortab-> valor tabuleiro que estamos a avaliar quanto maior melhor; valormax-> valormaximo encontrado;
                                                                    //valortab-> valor tabuleiro que estamos a avaliar quanto menor melhor, é avaliado na forma inversa do valor tab pois é para o oponent
                                                                    //valormin-> valor minimo encontrado                i e j sao indices para percorrer o tabuleiro
    ESTADO clone;                                                   // estado clone onde vamos jogar e avaliar-lo
    char player = troca(pecabot);                                  // o player humano é a pecabot trocada
    int meh;                                                      // é lixo nao serve para nada, mas é preciso para darmos um argumento á função quando chamamos recursivamente


    if (altura == 0 ) return ponttabuleiro(e,pecabot);            // quando chega a altura 0 dá return há pontuação do tabuleiro atual


    if (maximizante=='T') {                                       // maximizante 'T' ou 'F' de acordo se contamos de forma positiva ou negativa o tabuleiro
        valormax = (int) (-INFINITY);

        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {                            // percorrer tabuleiro e encontrar jogadas validas
                if (valida(e,i,j,pecabot)){
                    clone = e;
                    clone = jogada(i+1,j+1,clone,pecabot);       // clonamos e jogamos na jogada valida
                    clone.peca = inverso(clone.peca);            // trocar a peça para ser o outro jogador

                    valortab = minimax(clone,altura-1,alpha,beta, 'F' ,&meh,&meh,pecabot);      // chamamos a função minimax denovo no clone mas com o maximizante a 'F' pois é o oponente
                    valormax = MAXIMO(valortab,valormax);                                       // valor maximo encontrado
                    if ( MAXIMO(valortab,valormax) == valortab) {*xx= i; *yy=j;}                //se o maximo é o valor do tabuleiro atual mandar as coordenadas onde foi feita a jogada
                    alpha = MAXIMO(alpha,valortab);
                    if (beta <= alpha)         // pruning
                        break;
                }

            }
            if (beta <= alpha)         // pruning
                break;
        }
        return valormax;
    }

    else {                                                           // a mesma coisa mas quando o maximizante é 'F'
        valormin = (int) (+INFINITY);

        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {                                    // percorrer tabuleiro e encontrar jogadas validas
                if (valida(e,i,j,player)){
                    clone = e;
                    clone = jogada(i+1,j+1,clone,player);                 // clonamos e jogamos na jogada valida
                    clone.peca = inverso(clone.peca);
                    valortabmin = minimax(clone,altura-1,alpha,beta,'T',&meh,&meh,pecabot);      // chamamos a função minimax denovo no clone mas com o maximizante a 'T'
                    valormin = MINIMO(valortabmin,valormin);                                     // valor minimo encontrado
                    if ( MINIMO(valortabmin,valormin) == valortabmin) {*xx= i; *yy=j;}          // se o minimo é o valor do tabuleiro atual mandar as coordenadas onde foi feita a jogada
                    beta = MINIMO(beta,valortabmin);
                    if (beta <= alpha)                // pruning
                        break;
                }

            }
            if (beta <= alpha)                         // pruning
                break;
        }
    }
    return valormin;

}


