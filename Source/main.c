#include <stdio.h>
#include <stdlib.h>
#include "Printas.h"
#include "estado.h"
#include "Auxiliares.h"




int main()
{
    printf("\n");
    ps = stackinic(&ps);     // iniciar a stack da função undo
    interpreta ();           // ir para a função interpreta que está no estado, é a linha de comandos
    printf("\n");
    system("pause");
    return 0;
}