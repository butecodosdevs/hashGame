#include <stdio.h>
#include <stdlib.h>
int opcaoLinha;
int opcaoColuna;
char vez = 'X';
typedef struct
{
    char typePlayer;
} Player;

typedef struct
{
    char Table[3][3];
} Game;

void renderTable(Game *game)
{
    int i = 0, j = 0;

    while (i <= 2)
    {
        while (j <= 2)
        {
            printf("%c", game->Table[i][j]);
            if (j != 2)
                printf("|");
            fflush(stdin);
            j++;
        }
        if (i != 2)
            printf("\n-----\n");

        i++;
        j = 0;
    }
}

int validationForPosition(Game *game, int optionLine, int optionColumn, char vez)
{
    if (optionLine > 2 || optionColumn > 2)
    {
        printf("\n Erro: voce escolheu uma posicao inexistente");
        return 1;
    }
    if (game->Table[opcaoLinha][opcaoColuna] != ' ')
    {
        printf("\n Erro: voce escolheu uma posicao preenchida");
        return 1;
    }
    return 0;
}
int verificationGame(Game *game, int count, int optionLine, int optionColumn, char vez)
{
    printf("\nChecando Game\n");
      
    if (count == 2)
    {
        return 1;
    }
    else
    {
        //Adicionar recursividade para checagem se deu velha ou se houve vitoria de algum player
        if (game->Table[optionLine][optionColumn] == vez)
            verificationGame(&game, count + 1, optionLine, optionColumn + 1, vez);
    }
}
int insertTable(Game *game, int optionLine, int optionColumn, char vez, int round)
{
    int count = 1;
    game->Table[opcaoLinha][opcaoColuna] = vez;
    if (round > 4)
    {
        int result = verificationGame(game, count, optionLine, optionColumn, vez);
         return result;

    }
}
void roundGame()
{
    printf("\n Vez do jogador %c:", vez);
    fflush(stdin);
    printf("\n Escolha a posicao (linha) %c:", vez);
    scanf("%d", &opcaoLinha);
    printf("\n Escolha a posicao (coluna) %c:", vez);
    scanf("%d", &opcaoColuna);
}
int main()
{
    Game game = {{{' ', ' ', ' '},
                  {' ', ' ', ' '},
                  {' ', ' ', ' '}}};

    renderTable(&game);
    Player player1;
    Player player2;

    int round = 1;
    player1.typePlayer = 'X';
    player2.typePlayer = 'O';

    while (1)
    {
       roundGame();
        if (validationForPosition(&game, opcaoLinha, opcaoColuna, vez))
        {
            continue;
        }
        int result  = insertTable(&game, opcaoLinha, opcaoColuna, vez, round);
        if(result == 1){
            renderTable(&game);
            printf("\nO jogador %c ganhou!", vez);
            break;
        }

        renderTable(&game);

        vez = (vez == 'X' ? 'O' : 'X');
        round++;
    }
}
