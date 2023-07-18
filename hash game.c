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
int HorizontalVerificationGame(Game *game, int optionLine, int optionColumn, char vez)
{
    int countLoop = 1;
    int optionColumnLoop = optionColumn;
    while (1)
    {
        optionColumnLoop++;
        char vezLoop = game->Table[optionLine][optionColumnLoop];

        if (vezLoop == vez)
        {
            countLoop++;
        }
        else
        {
            break;
        }
    }
    optionColumnLoop = optionColumn;
    while (1)
    {

        optionColumnLoop--;
        char vezLoop = game->Table[optionLine][optionColumnLoop];

        if (vezLoop == vez)
        {
            countLoop++;
        }
        else
        {
            break;
        }
    }
    if (countLoop >= 3)
    {

        return 1;
    }
    else
    {
        return 0;
    }
}
int VerticalVerificationGame(Game *game, int optionLine, int optionColumn, char vez)
{
    int countLoop = 1;
    //3
    int optionLineLoop = optionLine;
    while (1)
    {
        optionLineLoop++;
        char vezLoopVertical = (game->Table[optionLineLoop][optionColumn]);
       //vezLoopVertical == X
        if (vezLoopVertical == vez)
        {

            countLoop++;
        }
        else
        {
            break;
        }
    }
    optionLineLoop = optionLine;
    while (1)
    {
        optionLineLoop--;
        char vezLoopVertical = (game->Table[optionLineLoop][optionColumn]);

        if (vezLoopVertical == vez)
        {

            countLoop++;
        }
        else
        {
            break;
        }
    }

    if (countLoop >= 3)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int DiagonalVerificationGame(Game *game, int optionLine, int optionColumn, char vez)
{
    int countLoop = 1;
    int optionLineLoop = optionLine;
    int optionColumnLoop = optionColumn;
    while (1)
    {
        optionLineLoop++;
        optionColumnLoop++;
        char vezLoopVertical = (game->Table[optionLineLoop][optionColumnLoop]);

        if (vezLoopVertical == vez)
        {

            countLoop++;
        }
        else
        {
            break;
        }
    }
    optionLineLoop = optionLine;
    optionColumnLoop = optionColumn;
    while (1)
    {
        optionLineLoop--;
        optionColumnLoop--;
        char vezLoopVertical = (game->Table[optionLineLoop][optionColumnLoop]);

        if (vezLoopVertical == vez)
        {

            countLoop++;
        }
        else
        {
            break;
        }
    }

    if (countLoop >= 3)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int verificationGame(Game *game, int optionLine, int optionColumn, char vez)
{

    int resultHorizontal = 0, resultVertical = 0, resultDiagonal = 0;
    resultHorizontal = HorizontalVerificationGame(game, optionLine, optionColumn, vez);
    resultVertical = VerticalVerificationGame(game, optionLine, optionColumn, vez);
    resultDiagonal = DiagonalVerificationGame(game, optionLine, optionColumn, vez);

    if (resultHorizontal || resultVertical || resultDiagonal)
        return 1;
    else
        return 0;
}
int insertTable(Game *game, int optionLine, int optionColumn, char vez, int round)
{

    game->Table[opcaoLinha][opcaoColuna] = vez;
    if (round > 4)
    {
        int result = verificationGame(game, optionLine, optionColumn, vez);
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
        int result = insertTable(&game, opcaoLinha, opcaoColuna, vez, round);
        if (result == 1)
        {
            renderTable(&game);
            printf("\nO jogador %c ganhou!", vez);
            break;
        }

        renderTable(&game);

        vez = (vez == 'X' ? 'O' : 'X');
        round++;
    }
}
