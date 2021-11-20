#include <stdio.h>
#include <unistd.h>

void print_tris(int *); // Prints the board

char x_or_o(int, int); // Converts 0, 1, 2 into '(number of cell)', 'X' and 'O'

int check_victory(int *); // Checks if a win/draw condition was met

int count_0s(int *); // Counts the number of 0s on board, used in check_victory

int main() {
    int table[9] = {0, 0, 0, // Initializations
                    0, 0, 0, 
                    0, 0, 0};
    int i, number_of_turns; 
    char rematch = 'y';

    printf("Welcome to Tic-Tac-Toe!\n");

    while (rematch == 'y') {
        number_of_turns = 0; // Resetting variables
        for (i=0; i<9; i++) 
            table[i] = 0;
        
        print_tris(table);

        while (check_victory(table) == 0) {
            i = 0;
            number_of_turns++;
            do {
                printf("In which position do you want to put %c? ", x_or_o((number_of_turns % 2) + 1, 0));
                scanf("%d", &i);

                if (table[i - 1] != 0) // Cell already has character
                    printf("This cell already has a %c in it, please choose another one\n", x_or_o(table[i - 1], i-1));
                if (i < 1 || i > 9) // Out of bounds number
                    printf("Please choose one of the avaiable cells (Input a number from 1 to 9)\n");
            } while (i < 1 || i > 9 || table[i - 1] != 0);
            
            table[i - 1] = (number_of_turns % 2) + 1;
            print_tris(table);
        }
        if (check_victory(table) == 1)
            printf("X won!\n");
        if (check_victory(table) == 2)
            printf("O won!\n");
        if (check_victory(table) == -1)
            printf("Draw!\n");
            
        if (check_victory(table) != 0) {
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

void print_tris(int table[9]) {

    printf("         |         |         \n");
    printf("    %c    |    %c    |    %c     \n", x_or_o(table[0], 0), x_or_o(table[1], 1), x_or_o(table[2], 2));
    printf("         |         |         \n");
    printf("____________________________\n");
    printf("         |         |         \n");
    printf("    %c    |    %c    |   %c     \n", x_or_o(table[3], 3), x_or_o(table[4], 4), x_or_o(table[5], 5));
    printf("         |         |         \n");
    printf("____________________________\n");
    printf("         |         |         \n");
    printf("    %c    |    %c    |   %c     \n", x_or_o(table[6], 6), x_or_o(table[7], 7), x_or_o(table[8], 8));
    printf("         |         |         \n");
}

char x_or_o(int n, int i) {
        return !n ? '1'+ i : n == 1 ? 'X' : 'O';
    }

int check_victory(int * table) { // Returns the value of winner in case of win condition // Checking...
    if (table[0] == table[1] && table[1] == table[2] && table[0] != 0) return table[0];  // 1st row
    if (table[3] == table[4] && table[4] == table[5] && table[3] != 0) return table[3];  // 2nd row
    if (table[6] == table[7] && table[7] == table[8] && table[6] != 0) return table[6];  // 3rd row
    if (table[0] == table[3] && table[3] == table[6] && table[0] != 0) return table[0];  // 1st column
    if (table[1] == table[4] && table[4] == table[7] && table[1] != 0) return table[1];  // 2nd column
    if (table[2] == table[5] && table[5] == table[8] && table[2] != 0) return table[2];  // 3rd column
    if (table[0] == table[4] && table[4] == table[8] && table[0] != 0) return table[0];  // 1st diagonal
    if (table[2] == table[4] && table[4] == table[6] && table[2] != 0) return table[2];  // 2nd diagonal
    if (count_0s(table) == 0) return -1; // No places left, initiate draw
    return 0; // Nothing wrong! Continue playing
}

int count_0s(int * table) {
    int i, counter=0;
    for (i=0; i<9; i++) {
        if (table[i] == 0) counter++;
    }
    return counter;
}