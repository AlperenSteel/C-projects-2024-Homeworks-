// Name: Yusuf Alperen Çelik
// Project Name: Botanist Game
// Description: 
//      This program simulates a botanist searching for rare flowers in a forest.
//      The botanist can move in four directions (up, down, left, right) and collect rare flowers.
//      The game state is saved to a file when the botanist collects a flower or when the game ends.
//      The botanist has a limited number of bottles to collect flowers.
//      The game ends when the botanist collects all the rare flowers or runs out of bottles.
//      The game state is saved to a file when the botanist collects a flower or when the game ends.
//      The botanist can also end the game and save the state to a file by pressing 'e'.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 500

typedef struct {
    char map[MAX_SIZE][MAX_SIZE]; /* 2D array to represent the forest*/
    int width;  
    int height; 
    int flower_x[MAX_SIZE]; /* X coordinate of the rare flower*/
    int flower_y[MAX_SIZE]; /* Y coordinate of the rare flower*/
} Forest;


/* Define structure for the botanist*/
typedef struct {
    int coord_x; /*X coordinate of the botanist*/
    int coord_y; /*Y coordinate of the botanist*/
    int number_of_bottles; /*Number of bottles the botanist has*/
    int flowers_collected; /*Number of rare flowers collected*/
} Botanist;
void init_game(Forest* forest, Botanist* botanist);
void search(Forest* forest, Botanist* botanist);
void display_forest(Forest* forest, Botanist* botanist);
void save_game_state(Forest* forest, Botanist* botanist); /*Function to save the game state.*/
int search_flower(Forest* forest, Botanist* botanist);

int main()
{
    char move;
    Forest forest;
    Botanist botanist;
    botanist.flowers_collected = 0;
    init_game(&forest, &botanist);
    display_forest(&forest, &botanist);
    search(&forest, &botanist);
    return 0;
}
void init_game(Forest *forest, Botanist *botanist) 
{
    int i, j, k = 0;
    FILE *file = fopen("init.txt", "r");
    if (file == NULL) 
    {
        printf("File could not be opened.");
        exit(1);
    }
    /*Read the forest and botanist info from the file*/
    fscanf(file, " %d,%d\n%d,%d,%d\n", &forest->height, &forest->width, &botanist->coord_y, &botanist->coord_x, &botanist->number_of_bottles);
    for (i = 0; i < forest->height; i++) /*Read the forest*/
    {
        for (j = 0; j < forest->width; j++) 
        {
            fscanf(file, "%c,", &forest->map[i][j]);
        }
        fscanf(file, "\n");
    }
    /*Find the flower coordinates*/
    for (i = 0; i < forest->height; i++) 
    {
        for (j = 0; j < forest->width; j++) 
        {
            if (forest->map[i][j] == 'X') 
            {
                forest->flower_x[k] = i;
                forest->flower_y[k] = j;
                k++;
            }
        }
    }
    fclose(file);
}
void search(Forest* forest, Botanist* botanist) /*Function to handle the botanist's movements. It takes input from the user and moves the botanist accordingly.*/
{
    char direction;
    int flag = 1;
    /*If botanist has no bottles left, end the game*/
    if(botanist->number_of_bottles == 0)
    {
        printf("You have no bottles left. Game over!\n");
        printf("Games last state savd in a file!\n");
        save_game_state(forest, botanist);
        exit(1);
    }
    printf("Enter your move r(right),l(left),u(up),d(down). \n");
    printf("If you want to end the game and save it to a file, press 'e'\n");
    scanf(" %c", &direction);
        switch(direction)
        {
            case 'u':
                if(forest->map[botanist->coord_y - 1][botanist->coord_x] == 'X')
                {
                    printf("You found the rare flower!\n");
                    botanist->flowers_collected += 1;
                    botanist->number_of_bottles -= 1;
                    forest->map[botanist->coord_y][botanist->coord_x] = ' ';
                    forest->map[botanist->coord_y-1][botanist->coord_x] = 'B';
                    botanist->coord_y -= 1;
                }
                else if((botanist->coord_y)  == 0)
                {
                    printf("You hit the wall. Try another move!\n");
                    break;
                }
                else if(forest->map[botanist->coord_y - 1][botanist->coord_x] == 'T')
                {
                    printf("You hit the tree. Try another move!\n");
                    break;
                }
                else
                {
                    printf("Moving in that location\n");
                    forest->map[botanist->coord_y][botanist->coord_x] = ' ';
                    forest->map[botanist->coord_y-1][botanist->coord_x] = 'B';
                    botanist->coord_y -= 1;
                }
                break;
            case 'd':
                if(forest->map[botanist->coord_y + 1][botanist->coord_x] == 'X')
                {
                    printf("\nI've found it!\n");
                    botanist->flowers_collected += 1;
                    botanist->number_of_bottles -= 1;
                    forest->map[botanist->coord_y][botanist->coord_x] = ' ';
                    forest->map[botanist->coord_y + 1][botanist->coord_x] = 'B';
                    botanist->coord_y += 1;
                }
                else if((botanist->coord_y)  == forest->height - 1)
                {
                    printf("You hit the wall. Try another move!\n");
                    break;
                }
                else if(forest->map[botanist->coord_y + 1][botanist->coord_x] == 'T')
                {
                    printf("You hit the tree. Try another move!\n");
                    break;
                }
                else
                {
                    printf("Moving in that location\n");
                    forest->map[botanist->coord_y][botanist->coord_x] = ' ';
                    forest->map[botanist->coord_y + 1][botanist->coord_x] = 'B';
                    botanist->coord_y += 1;
                }
                break;
            case 'l':
                if(forest->map[botanist->coord_y][botanist->coord_x - 1] == 'X')
                {
                    printf("You found the rare flower!\n");
                    botanist->flowers_collected += 1;
                    botanist->number_of_bottles -= 1;
                    forest->map[botanist->coord_y][botanist->coord_x] = ' ';
                    forest->map[botanist->coord_y][botanist->coord_x-1] = 'B';
                    botanist->coord_x -= 1;
                }
                else if((botanist->coord_x)  == 0)
                {
                    printf("You hit the wall. Try another move!\n");
                    break;
                }
                else if(forest->map[botanist->coord_y][botanist->coord_x - 1] == 'T')
                {
                    printf("You hit the tree. Try another move!\n");
                    break;
                }
                else
                {
                    printf("Moving in that location\n");
                    forest->map[botanist->coord_y][botanist->coord_x] = ' ';
                    forest->map[botanist->coord_y][botanist->coord_x-1] = 'B';
                    botanist->coord_x -= 1;
                }
                break;
            case 'r':
                if(forest->map[botanist->coord_y][botanist->coord_x + 1] == 'X')
                {
                    printf("You found the rare flower!\n");
                    botanist->flowers_collected += 1;
                    botanist->number_of_bottles -= 1;
                    forest->map[botanist->coord_y][botanist->coord_x] = ' ';
                    forest->map[botanist->coord_y][botanist->coord_x+1] = 'B';
                    botanist->coord_x += 1;
                }
                else if((botanist->coord_x)  == forest->width - 1)
                {
                    printf("You hit the wall. Try another move!\n");
                    break;
                }
                else if(forest->map[botanist->coord_y][botanist->coord_x + 1] == 'T')
                {
                    printf("You hit the tree. Try another move!\n");
                    break;
                }
                else
                {
                    forest->map[botanist->coord_y][botanist->coord_x] = ' ';
                    forest->map[botanist->coord_y][botanist->coord_x+1] = 'B';
                    botanist->coord_x += 1;
                }
                break;
            case 'e':
                save_game_state(forest, botanist); /*Pressing 'e' to end the game and save it*/
                flag = 0;
                break;
            default:     /*Default case for invalid input*/
                printf("Enter a valid character!\n");
                break;
        }
        if(flag == 1)
        {
            if(search_flower(forest, botanist) == 0)
            {
                printf("You have collected all the rare flowers!\n");
                printf("Game saved to file (last.txt).\n");
                save_game_state(forest, botanist);
                display_forest(forest, botanist);
                exit(1);
            }
            display_forest(forest, botanist);
            search(forest, botanist);
        }
        else
        {
            printf("Game saved to file (last.txt).\n");
            exit(1);
        }
}
void display_forest(Forest *forest, Botanist *botanist) 
{
    int i, j;
    /*Loop through the forest map and print each cell's contents*/
    for (i = 0; i < forest->height; i++) 
    {
        for (j = 0; j < forest->width; j++) 
        {
            printf("%c", forest->map[i][j]);
            if (j < forest->width - 1) 
            {
                printf(",");
            }
        }
        printf("\n");
    }
    printf("\nNot used bottle number: %d\n", botanist->number_of_bottles);
    printf("Number of flowers collected: %d\n", botanist->flowers_collected);
    printf("Botanist coordinates: X:%d,Y:%d\n\n", botanist->coord_x, botanist->coord_y);
}
/*Function to save the current game state to a file.*/
void save_game_state(Forest* forest, Botanist* botanist) 
{
    int i,j;
    FILE  *file = fopen("last.txt", "w");
    if (file == NULL)
    {
        printf("File could not be opened.");
        exit(1);
    }
    /*Write forest dimensions and botanist info to the file*/
    fprintf(file, "%d,%d\n%d,%d,%d\n", forest->height, forest->width, botanist->coord_y, botanist->coord_x, botanist->number_of_bottles);
    for (i = 0; i < forest->height; i++) /*Write the forest map to the file*/
    {
        for (j = 0; j < forest->width; j++)
        {
            fprintf(file, "%c,", forest->map[i][j]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\nNot used bottle number: %d\n", botanist->number_of_bottles);
    fprintf(file, "Number of flowers collected: %d\n", botanist->flowers_collected);
    fprintf(file, "Botanist coordinates: X:%d,Y:%d\n\n", botanist->coord_x, botanist->coord_y);
}
int search_flower(Forest* forest, Botanist* botanist)/*Function to search for rare flowers in the forest. Returns 1 if flower found, 0 otherwise.*/
{
    int i, j;
    for (i = 0; i < forest->height; i++) /*Loop through the forest map to search for the rare flower*/
    {
        for (j = 0; j < forest->width; j++) 
        {
            if (forest->map[i][j] == 'X') 
            {
                return 1; /*Rare flower found*/
            }
        }
    }
    return 0; /*Rare flower not found*/
}