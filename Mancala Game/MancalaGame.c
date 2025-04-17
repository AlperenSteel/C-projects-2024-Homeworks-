/*
    Name: Yusuf Alperen Çelik
    Project Name: Mancala Game
    Date: 24.04.2024
*/
/*Description:
This program is a simple Mancala game.
The game is played between a player and a computer.
The player and the computer take turns to move the stones.
The player can choose a cup to move the stones.
The computer chooses the cup to move the stones.
*/
#include <stdio.h>

#define BOARD_SIZE 7  /* 12 small cups + 2 large cups*/

void initializeGame(int board[2][BOARD_SIZE], int n);
void printBoard(int board[2][BOARD_SIZE]);
void gamePlay(int board[2][BOARD_SIZE]);
int move(int player, int board[2][BOARD_SIZE], int cup, int side);
int checkEndGame(int board[2][BOARD_SIZE]);
int check_optimum(int board[2][BOARD_SIZE]);

int main() 
{
    int board[2][BOARD_SIZE];  
    int n;
    printf("Enter the number of stones in each cup: ");
    scanf("%d", &n);
    initializeGame(board, n);
    printBoard(board);
    gamePlay(board);
    return 0;
}

void initializeGame(int board[2][BOARD_SIZE], int n) 
{
    int i;
    /*Fill the entire indexes with n files received from the user*/
    for (i = 0; i < BOARD_SIZE; i++) 
    {
        board[0][i] = n;
        board[1][i] = n;
    }
    /*fill the board[1][6] and board[0][6] cells with zeros*/
    board[0][6] = 0;
    board[1][6] = 0;
}

void printBoard(int board[2][BOARD_SIZE]) 
{
    /*Print game interface in desired format*/
    printf("+---+---+---+---+---+---+---+---+\n");
    printf("|   |%2d |%2d |%2d |%2d |%2d |%2d |   |\n", 
           board[1][5], board[1][4], board[1][3], board[1][2], board[1][1], board[1][0]);
    printf("|%2d |---+---+---+---+---+---|%2d |\n", 
           board[1][6], board[0][6]);
    printf("|   |%2d |%2d |%2d |%2d |%2d |%2d |   |\n", 
           board[0][0], board[0][1], board[0][2], board[0][3], board[0][4], board[0][5]);
    printf("+---+---+---+---+---+---+---+---+\n");
    printf("    | 0 | 1 | 2 | 3 | 4 | 5 | <- indexes\n");
}

int check_optimum(int board[2][BOARD_SIZE])
{
    /*A simple AI: find the optimum index to take the stones*/
    int stone_count = 0;
    int i, j;
    int maxValue = board[1][0];  
    int maxIndex = 0;
    for(i = 0; i < BOARD_SIZE-1; i++) /*Is there an index that allows the last stone into the big cup? function that controls it*/
    {
        stone_count = board[1][i];
        if(stone_count == 6 - i)
        {
            printf("Computer selected cup: %d\n", i);
            return i;
        }
    }
    for (j = 1; j < BOARD_SIZE-1; j++) 
    {
        if (board[1][j] > maxValue) 
        {
            maxValue = board[1][j];
            maxIndex = j;
        }
    }
    printf("Computer selected cup: %d (index)\n", maxIndex);
    return maxIndex;
}
void gamePlay(int board[2][BOARD_SIZE]) {
    int currentPlayer = 0;  /* 0 for player, 1 for computer*/
    int side, cup, continueTurn;
    int playerScore = board[0][6];
    int computerScore = board[1][6];
    while (!checkEndGame(board)) 
    {
        continueTurn = 0;
        do 
        {
            if(checkEndGame(board))
            {
                break;
            }
            printf("Current player: %s\n", (currentPlayer == 0 ? "Player" : "Computer"));
            if (currentPlayer == 0) 
            {
                side = currentPlayer;
                printf("Select a cup (0-5): ");
                scanf("%d", &cup);
                while (cup < 0 || cup > 5 || board[0][cup] == 0) 
                {
                    printf("Invalid choice. Please select a non-empty cup between 0 and 5: ");
                    scanf("%d", &cup);
                }
            } 
            else 
            {
                side = currentPlayer;
                /*Simple AI: Choose the first non-empty cup*/
                cup = -1;
                cup = check_optimum(board);
            }
            continueTurn = move(currentPlayer, board, cup, side);
            printBoard(board);
        } 
        while (continueTurn);
        currentPlayer = 1 - currentPlayer;
    }
}
int move(int player, int board[2][BOARD_SIZE], int cup, int side) 
{
    int other_result;
    int initial_player = player;
    int pos = cup;
    int stones = board[side][pos];
    board[side][pos] = 0;
    while(stones > 0)
    {
        pos = (pos + 1) % BOARD_SIZE;
        if(initial_player == 0 && side == 1 && pos == 6)
        {
            side = 0;
        }
        else if(initial_player == 1 && side == 0 && pos == 6)
        {
            side = 1;
        }
        else if(initial_player == 0 && side == 0 && pos == 6)
        {
            board[side][pos]++;
            stones--;
            if(stones == 0)
            {
                return 1;
            }
            side = 1;
            pos = -1; /*The reason why this is -1 is because when it enters "while" it will be 0 and it will be the first element of the array.*/
        }
        else if(initial_player == 1 && side == 1 && pos == 6)
        {   
            board[side][pos]++;
            stones--;
            if(stones == 0)
            {
                return 1;
            }
            side = 0;
            pos = -1; /*The reason why this is -1 is because when it enters "while" it will be 0 and it will be the first element of the array.*/
        }
        else
        {
            board[side][pos]++;
            stones--;
        }
    }
    if(board[side][pos] == 1)
    {
        return 0;
    }
    else if(board[side][pos] > 1) /*If more than 1 stones in that position loop must continue.*/
    {
        other_result = move(player, board, pos, side);
        if(other_result == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return -1;
}
int checkEndGame(int board[2][BOARD_SIZE]) 
{
    int i;
    int sumPlayer = 0, sumComputer = 0;
    for (i = 0; i < BOARD_SIZE-1; i++) 
    {
        sumPlayer += board[0][i];
    }
    for (i = 0; i < BOARD_SIZE-1; i++)
    {
        sumComputer += board[1][i];
    }
    /*If all a player's buckets are empty, the game ends*/
    if (sumPlayer == 0 || sumComputer == 0) 
    {
    /* Determine a winner based on the number of tiles in the big cup*/
        if (board[0][6] > board[1][6]) 
        {
            printf("Game over. Winner: Player!\n");
        } 
        else if (board[0][6] < board[1][6]) 
        {
            printf("Game over. Winner: Computer!\n");
        } 
        else 
        {
            printf("Game over. Draw!\n");
        }
        return 1; /*Game over*/
    }
    return 0; /*Game continues*/
}