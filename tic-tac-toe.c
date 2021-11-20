#include <stdio.h>

void print_tris(int *);
char x_or_o(int);
int check_victory(int *);
int count_0s(int *);

int main() {
    int table[9] = {0, 0, 0, 
                    2, 1, 0, 
                    1, 2, 1};
    int i = 0, number_of_turns = 0;
    print_tris(table);
    while (check_victory(table) == 0) {
        i=0;
        number_of_turns++;
        do{
            printf("In which position do you want to put %c? ", x_or_o((number_of_turns%2)+1));
            scanf("%d", &i);
            if (table[i-1] != 0) printf("aaaaaoooooooooooo \n");
        } while(i<1 || i>9 || table[i-1] != 0);
        table[i-1] = (number_of_turns%2)+1;
        print_tris(table);
    }
    if (check_victory(table) == 1) printf("X won yehhhhhhhhhh");
    if (check_victory(table) == 2) printf("O won yehhhhhhhhhh");
    if (check_victory(table) == -1) printf("draw :''''''''(");
    if (check_victory(table) == 0) printf("WHAAAAAAAT????");
    return 0;
}

void print_tris(int table[9]) {

    printf("         |         |         \n");
    printf("    %c    |    %c    |    %c     \n", x_or_o(table[0]), x_or_o(table[1]), x_or_o(table[2]));
    printf("         |         |         \n");
    printf("____________________________\n");
    printf("         |         |         \n");
    printf("    %c    |    %c    |   %c     \n", x_or_o(table[3]), x_or_o(table[4]), x_or_o(table[5]));
    printf("         |         |         \n");
    printf("____________________________\n");
    printf("         |         |         \n");
    printf("    %c    |    %c    |   %c     \n", x_or_o(table[6]), x_or_o(table[7]), x_or_o(table[8]));
    printf("         |         |         \n");
}

char x_or_o(int n) {
        return !n ? ' ' : n == 1 ? 'X' : 'O';
    }

int check_victory(int * table) {
    if (table[0] == table[1] && table[1] == table[2] && table[0] != 0) return table[0];
    if (table[3] == table[4] && table[4] == table[5] && table[3] != 0) return table[3];
    if (table[6] == table[7] && table[7] == table[8] && table[6] != 0) return table[6];
    if (table[0] == table[3] && table[3] == table[6] && table[0] != 0) return table[0];
    if (table[1] == table[4] && table[4] == table[7] && table[1] != 0) return table[1];
    if (table[2] == table[5] && table[5] == table[8] && table[2] != 0) return table[2];
    if (table[0] == table[4] && table[4] == table[8] && table[0] != 0) return table[0];
    if (table[2] == table[4] && table[4] == table[6] && table[2] != 0) return table[2];
    if (count_0s(table) == 0) return -1;
    return 0;
}

int count_0s(int * table) {
    int i, counter=0;
    for (i=0; i<9; i++) {
        if (table[i] == 0) counter++;
    }
    return counter;
}