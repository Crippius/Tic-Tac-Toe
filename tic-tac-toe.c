#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void print_tris(int *); // Prints the board

char x_or_o(int, int); // Converts 0, 1, 2 into '(number of cell)', 'X' and 'O'

int check_victory(int *); // Checks if a win/draw condition was met

int count_0s(int *); // Counts the number of 0s on board, used in check_victory

int insert_O(int *); // Makes decision on where should the AI place O (look at TODO)

int main() {
    int table[9] = {0, 0, 0, // Initializations
                    0, 0, 0, 
                    0, 0, 0};
    int i, turn, format; 
    char rematch = 'y';

    printf("Welcome to Tic-Tac-Toe!\n");

    while (rematch == 'y') {
        turn = 0; // Resetting variables for every game
        for (i=0; i<9; i++) 
            table[i] = 0;
        
        print_tris(table);

        do { // PvP or PvE
            printf("Do you want to play against another player (1) of an AI (2)? "); scanf("%d", &format); printf("\n");
        } while(format < 1 || format  > 2);

        if (format == 2)
            printf("You're going to use X\n");
        
        printf("Dediciding who starts...\n"); // Using random to make every game different
        srand(time(NULL));        
        turn = rand()%2;
        printf("%c starts!\n", x_or_o(1+(turn%2), 0));

        while (check_victory(table) == 0) { // While a win/draw condition has not been found
            i = 0;
            
            if (format==2 && 1+(turn%2) == 2) { // AI's turn

                if (turn!=1) printf("O's turn!\n"); // Removing redundancies, doesn't say it the first time
                 
                i = insert_O(table) + 1; // To counteract the following - 1
                printf("Added O in cell No %d\n", i);
            }
            else { // Player's turn
                    do {

                    printf("In which position do you want to put %c? ", x_or_o((turn % 2) + 1, 0));
                    scanf("%d", &i);

                    if (table[i - 1] != 0) // Cell already has character
                        printf("This cell already has a %c in it, please choose another one\n", x_or_o(table[i - 1], i-1));
                    if (i < 1 || i > 9) // Out of bounds number
                        printf("Please choose one of the avaiable cells (Input a number from 1 to 9)\n");

                } while (i < 1 || i > 9 || table[i - 1] != 0);
            }
            
            table[i - 1] = (turn % 2) + 1; // Inserting char in table and restarting
            print_tris(table);
            turn++;
        }

        if (check_victory(table) == 1) // Finding what the win/draw condition was
            printf("X won!\n");
        if (check_victory(table) == 2)
            printf("O won!\n");
        if (check_victory(table) == -1)
            printf("Draw!\n");

        if (check_victory(table) != 0) { // Asking for a rematch
            fflush(stdin);
            do {
                printf("Do you want a rematch? (y/n) ");
                scanf("%c", &rematch);
            } while (rematch != 'y' && rematch != 'n');
        }
    }
    
    printf("Thanks for playing!");
    sleep(2);
    return 0;
}

void print_tris(int table[9]) { // Prints board, nothing more to say

    printf("         |         |         \n");
    printf("    %c    |    %c    |    %c     \n", x_or_o(table[0], 0), x_or_o(table[1], 1), x_or_o(table[2], 2));
    printf("         |         |         \n");
    printf("____________________________\n");
    printf("         |         |         \n");
    printf("    %c    |    %c    |    %c     \n", x_or_o(table[3], 3), x_or_o(table[4], 4), x_or_o(table[5], 5));
    printf("         |         |         \n");
    printf("____________________________\n");
    printf("         |         |         \n");
    printf("    %c    |    %c    |    %c     \n", x_or_o(table[6], 6), x_or_o(table[7], 7), x_or_o(table[8], 8));
    printf("         |         |         \n");
}

char x_or_o(int n, int i) {                       // Is n == 0 ? if True -> return number of cell
        return !n ? '1'+ i : n == 1 ? 'X' : 'O';  //             if False -> is n == 1 ? if True -> return 'X'
    }                                             //                                     if False -> return 'O'

int check_victory(int * table) { // Returns the value of winner in case of win/draw condition 
    int i;
    
    for (i=0; i<3; i++) {
        if (table[0+3*i] == table[1+3*i] && table[1+3*i] == table[2+3*i] && table[0+3*i] != 0)
            return table[0+3*i]; // Checking rows

        if (table[0+i] == table[3+i] && table[3+i] == table[6+i] && table[0+i] != 0)
            return table[0+i]; // Checking columns
        
    } 

    if (table[0] == table[4] && table[4] == table[8] && table[0] != 0) 
        return table[0];  // Checking 1st diagonal

    if (table[2] == table[4] && table[4] == table[6] && table[2] != 0) 
        return table[2];  // Checking 2nd diagonal

    if (count_0s(table) == 0) 
        return -1; // No places left, initiate draw
    
    return 0; // Nothing wrong! Continue playing
}

int count_0s(int * table) { // How many 0's on board?
    int i, counter=0;
    for (i=0; i<9; i++) {
        if (table[i] == 0) counter++;
    }
    return counter;
}

int insert_O(int * table){
    int i, value;

    // There's defiinitely a better way to do it
    // TO DO: Make a function that checks all combinations WITHOUT this mess

    for (i=0; i<3; i++) { 
        // Check rows for possible win outcome in the next turns
        if (table[0+3*i] == table[1+3*i] && table[2+3*i] == 0 && table[0+3*i] != 0)
            return 2+3*i;
        if (table[0+3*i] == table[2+3*i] && table[1+3*i] == 0 && table[0+3*i] != 0)
            return 1+3*i;
        if (table[1+3*i] == table[2+3*i] && table[0+3*i] == 0 && table[1+3*i] != 0)
            return 0+3*i;

        // Check columns
        if (table[0+i] == table[1+i] && table[2+i] == 0 && table[0+i] != 0)
            return 2+i;
        if (table[0+i] == table[2+i] && table[1+i] == 0 && table[0+i] != 0)
            return 1+i;
        if (table[1+i] == table[2+i] && table[0+i] == 0 && table[1+i] != 0)
            return 0+i;              
    }
    
    // Check 1st diagonal 
    if (table[0] == table[4] && table[8] == 0 && table[0] != 0)
        return 8;
    if (table[0] == table[8] && table[4] == 0 && table[0] != 0)
        return 4;
    if (table[4] == table[8] && table[0] == 0 && table[4] != 0)
        return 0;
    
    // Check 2nd diagonal 
    if (table[2] == table[4] && table[6] == 0 && table[2] != 0)
        return 6;
    if (table[2] == table[6] && table[4] == 0 && table[2] != 0)
        return 4;
    if (table[4] == table[6] && table[2] == 0 && table[4] != 0)
        return 2;
    
    else { // Choose a random (empty) cell
        do {
            value = rand()%9;
        } while  (table[value] != 0); 
        return value;
    }

}