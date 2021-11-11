#include <stdio.h>

void print_tris(int *);
char x_or_o(char);

int main() {
    int table[9] = {0, 1, 0, 2, 1, 0, 1, 2, 1};
    print_tris(table);
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

char x_or_o(char c) {
        return !c ? ' ' : c == 1 ? 'X' : 'O';
    }