/*
TITLE: 
    ECTS Collector
    Author: YUSUF ALPEREN ÇELİK
    Date: 20.03.2024
*/
/*
    DESCRIPTION:
    This program is a simple game where the player has to collect ECTS points to pass through the walls.
    The player can move around the board using the WASD keys.
    The player can pass through the inner wall if they have collected enough ECTS points.
    The player can pass through the outer wall if they have collected enough ECTS points.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 16
#define FIRST_GRADE_ECTS 32
#define SECOND_GRADE_ECTS 24

char board[BOARD_SIZE * BOARD_SIZE];
int student_position;
int total_ects = 0;
int total_movements = 0;
int inner_wall_passable = 0;
int outer_wall_passable = 0;
int inner_number_array[] = {119, 120, 121, 135, 137, 151, 152, 153}; /* Indexes where 1's can occur. */
int outer_number_array[] = {85, 86, 87, 88, 89, 90, 91, 102, 117, 133, 149, 165, 181, 182, 183, 184, 185, 186, 187, 188, 107, 123, 139, 155}; /* Indexes where 2's can occur */
int outer_wall_array[] = {68, 69, 70, 71, 72, 73, 74, 75, 76, 84, 100, 116, 132, 148, 164, 180, 196, 197, 198, 199, 200, 201, 202, 203, 204, 92, 108, 124, 140, 156, 172, 188};
int possible_outer_collision = 0;

/* Function prototypes */
void initialize_game();
void print_board();
void move_player(char direction);
int check_completion();

int main() {
    srand(time(NULL));
    initialize_game();
    print_board();

    char move;
    while (!check_completion()) {
        printf("\nEnter your move (w/a/s/d): \n");
        scanf(" %c", &move);
        move_player(move);
        print_board();
    }

    printf("\nCongratulations! You have completed both grades!\n");
    printf("Total ECTS: %d\n", total_ects);
    printf("Total movements: %d\n\n", total_movements);

    return 0;
}
void initialize_game() 
{
    /* Initialize the board with empty spaces*/
    int i;
    for (i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) 
    {
        board[i] = '.';
    }
    /* Place outer wall*/
    for (i = 4; i < 13; i++) {
        board[i * BOARD_SIZE + 4] = '#'; /* Left wall*/
        board[i * BOARD_SIZE + 12] = '#'; /* Right wall*/
        board[4 * BOARD_SIZE + i] = '#'; /* Top wall*/
        board[12 * BOARD_SIZE + i] = '#'; /* Bottom wall*/
    }
    /* Place inner wall*/
    for (i = 6; i < 11; i++) {
        board[i * BOARD_SIZE + 6] = '#'; /* Left wall */
        board[i * BOARD_SIZE + 10] = '#'; /* Right wall */
        board[6 * BOARD_SIZE + i] = '#'; /* Top wall */
        board[10 * BOARD_SIZE + i] = '#'; /* Bottom wall*/
    }
    /* Place student ('P') at the center */
    student_position = (BOARD_SIZE / 2) * BOARD_SIZE + (BOARD_SIZE / 2); /*Center of the table. */
    board[student_position] = 'P';
    board[BOARD_SIZE * BOARD_SIZE - 1] = 'X';
    /* Place first grade courses*/
    int first_grade_courses = 4;
    while(first_grade_courses > 0) 
    {   
        int random_index = rand() % 8;
        if(board[inner_number_array[random_index]] == '.')/* To be able to print 4 1's at a time, to prevent the 1's from overlapping in the same place. */
        {
        board[inner_number_array[random_index]] = '1';
        first_grade_courses--;
        }
    }
    /*Place second grade courses*/
    int second_grade_courses = 3;
    while(second_grade_courses > 0) 
    {
        int random_index = rand() % 24;
        if (board[outer_number_array[random_index]] == '.')
        {
            board[outer_number_array[random_index]] = '2';
            second_grade_courses--;
        }
    }
}
void print_board() {
    int i,j;
    for (i = 0; i < BOARD_SIZE; i++) 
    {
        for (j = 0; j < BOARD_SIZE; j++) 
        {
            printf("%c ", board[i * BOARD_SIZE + j]);
        }
        printf("\n");
        
    }
}
void move_player(char direction) {
    int new_position = student_position;

    if(direction == 'W' || direction == 'A' || direction == 'D' || direction == 'S')
    {
        direction = direction + 32;
    }
    
    switch(direction) 
    {
        case 'a':
            if (new_position % BOARD_SIZE > 0)  /*It has to be somewhere other than the first column */
            {
                new_position -= 1;
            }
            break;
        case 's':
            if (new_position / BOARD_SIZE < BOARD_SIZE - 1) /*It has to be somewhere other than the last line. */
            {
                new_position += BOARD_SIZE;
            }
            break;
        case 'd':
            if (new_position % BOARD_SIZE < BOARD_SIZE - 1)  /*It shouldn't be at the end of the line*/
            {
                new_position += 1;
            }
            break;
        case 'w':
            if (new_position / BOARD_SIZE > 0) /*It must greater than 16*/
            {
                new_position -= BOARD_SIZE;
            }
            break;
        default:
            printf("\nEnter a valid character!\n");
            break;
    }

    if (board[new_position] == '1') 
    {
        total_ects += 8;
        board[new_position] = '.';
        if (total_ects >= FIRST_GRADE_ECTS) 
        {
            inner_wall_passable = 1;
            printf("\nYou have collected enough ECTS to pass through the inner wall!\n");
        }
    } 
    else if (board[new_position] == '2') 
    {
        total_ects += 8;
        board[new_position] = '.';
        if (total_ects >= FIRST_GRADE_ECTS + SECOND_GRADE_ECTS) 
        {
            outer_wall_passable = 1;
            printf("\nYou have collected enough ECTS to pass through the outer wall!\n");
        }
    } 
    else if(inner_wall_passable && board[new_position] == '#') /*If the first wall can be crossed and there is a # at that index*/
    {
        if(!outer_wall_passable) /*If the second wall can't be crossedd*/
        {
            int i;
            for(i = 0; i <= 32; i++) /*Search for whether the wall we are trying to pass is an inner wall or an outer wall.*/
                {
                    if(outer_wall_array[i] == new_position)
                    {
                        possible_outer_collision = 1;
                        printf("\nYou hit the wall!\n");
                        return;
                    }
                }
            if(possible_outer_collision == 0)
            {
                printf("\nYou passed through the wall!\n");
            }
        }
    }
    else if(!inner_wall_passable && board[new_position] == '#')
    {
        printf("\n You hit the wall\n");
        return;
    }

    /* Update student position */
    board[student_position] = '.'; /* Clear previous position*/
    student_position = new_position;
    board[student_position] = 'P'; /* Set new position */
    total_movements++;
}
int check_completion() 
{
    if (board[BOARD_SIZE * BOARD_SIZE - 1] == 'P') 
    {
        return 1; /* Player reached the X point*/
    }
    return 0;
}