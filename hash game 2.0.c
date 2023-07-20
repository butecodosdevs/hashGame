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
typedef struct
{
    int ColumnX[3];
    int LineX[3];
    int ColumnO[3];
    int LineO[3];
    int PrincipalDiagonalX;
    int SecondaryDiagonalX;
    int PrincipalDiagonalO;
    int  SecondaryDiagonalO;
} GamePositionXO;

void renderTable(Game *game)
{
    int i = 0, j = 0;

    while (i <= 2)
    {
        while (j <= 2)
        {
            printf("%c", game->Table[i][j]);
            if (j != 2)
                printf(" | ");
            fflush(stdin);
            j++;
        }
        if (i != 2)
            printf("\n--|---|--\n");

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

int insertTable(Game *game, GamePositionXO *gamePosition, int optionLine, int optionColumn, char vez, int round)
{
    game->Table[opcaoLinha][opcaoColuna] = vez;
    if (vez == 'X')
    {
        gamePosition->ColumnX[optionColumn] += 1;
        gamePosition->LineX[optionLine] += 1;
        if(optionColumn == optionLine){
                 gamePosition->PrincipalDiagonalX += 1;
        }
        if((optionColumn + optionLine) == 2){
                 gamePosition->SecondaryDiagonalX += 1;
        }
    
        if (gamePosition->ColumnX[optionColumn] == 3 || gamePosition->LineX[optionLine] == 3|| gamePosition->PrincipalDiagonalX == 3 || gamePosition->SecondaryDiagonalX == 3)
            return 1; 
    }
    else if (vez == 'O')
    {
        gamePosition->ColumnO[optionColumn] += 1;
        gamePosition->LineO[optionLine] += 1;
          if(optionColumn == optionLine){
                 gamePosition->PrincipalDiagonalO += 1;
        }
        if((optionColumn + optionLine) ==2){
                 gamePosition->SecondaryDiagonalO += 1;
        }
    
        if (gamePosition->ColumnO[optionColumn] == 3 || gamePosition->LineO[optionLine] == 3 ||  gamePosition->PrincipalDiagonalO == 3 || gamePosition->SecondaryDiagonalO == 3)
            return 1; // VULGO VITORA
    }
    return 0;
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
    GamePositionXO gamePosition = {0, 0.0f, '\0'};
    ;
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
        int result = insertTable(&game, &gamePosition, opcaoLinha, opcaoColuna, vez, round);
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
