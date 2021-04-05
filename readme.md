Jogo do Reversi
Projeto final da disciplina de laboratório de algoritmia 1
Implementação do jogo do Reversi para 2 jogadores assim como 1 jogador contra bot implementado pela estratégia Minimax
----
Apenas compilar e executar a partir do CMakeLists.

Para jogar os seguintes comandos são aceites:

-N <peça> para novo jogo em que o primeiro a jogar é o jogador com peça. 
-L <ficheiro> para ler um jogo de ficheiro. Em modo automático (A), após leitura do ficheiro, o próximo jogador a jogar é sempre o humano!
-E <ficheiro> escrever em ficheiro estado do jogo.
-J <L> <C> jogar peça atual na posição (L,C). O comando J 1 1 pede para colocar a peça atual no canto superior esquerdo!
-S para imprimir um ponto ‘.’ nas posições com jogada válida.
-H para sugestão de jogada. Deve ser colocado um ‘?’ no sitio sugerido.
-U para desfazer a última jogada (Undo). Isto tem de permitir desfazer até ao estado inicial do jogo!
-A <peça> <nível> novo jogo contra ‘bot’ (computador) em que o ‘bot’ joga com a peça <peça> num nível de dificuldade <nível> (3 níveis possíveis). Neste modo quem joga primeiro é sempre o jogador com a peça preta ‘X’.
-Q para sair.

---
Nota final: 17