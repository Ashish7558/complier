#include <stdio.h>
#include <string.h>

#define MAX 10

// Grammar: 
// E → E + T | T
// T → T * F | F
// F → (E) | id

// Terminals: id, +, *, (, ), $
// Non-terminals: E, T, F

char *terminals[] = {"id", "+", "*", "(", ")", "$"};
char *non_terminals[] = {"E", "T", "F"};

int num_terminals = 6;
int num_non_terminals = 3;

// Simplified ACTION table: state × terminal
char *ACTION[12][6];

// Simplified GOTO table: state × non-terminal
int GOTO[12][3];

void fillParsingTable() {
    // ACTION[state][terminal_index]
    ACTION[0][0] = "s5";   // id
    ACTION[0][3] = "s4";   // (

    ACTION[1][1] = "s6";   // +
    ACTION[1][5] = "acc";  // $

    ACTION[2][1] = "r2";
    ACTION[2][2] = "s7";
    ACTION[2][4] = "r2";
    ACTION[2][5] = "r2";

    ACTION[3][1] = "r4";
    ACTION[3][2] = "r4";
    ACTION[3][4] = "r4";
    ACTION[3][5] = "r4";

    ACTION[4][0] = "s5";
    ACTION[4][3] = "s4";

    ACTION[5][1] = "r6";
    ACTION[5][2] = "r6";
    ACTION[5][4] = "r6";
    ACTION[5][5] = "r6";

    ACTION[6][0] = "s5";
    ACTION[6][3] = "s4";

    ACTION[7][0] = "s5";
    ACTION[7][3] = "s4";

    ACTION[8][1] = "s6";
    ACTION[8][4] = "s11";
    ACTION[8][5] = "err";

    ACTION[9][1] = "r1";
    ACTION[9][2] = "s7";
    ACTION[9][4] = "r1";
    ACTION[9][5] = "r1";

    ACTION[10][1] = "r3";
    ACTION[10][2] = "r3";
    ACTION[10][4] = "r3";
    ACTION[10][5] = "r3";

    ACTION[11][1] = "r5";
    ACTION[11][2] = "r5";
    ACTION[11][4] = "r5";
    ACTION[11][5] = "r5";

    // GOTO[state][non-terminal index]
    GOTO[0][0] = 1; // E
    GOTO[0][1] = 2; // T
    GOTO[0][2] = 3; // F

    GOTO[4][0] = 8;
    GOTO[4][1] = 2;
    GOTO[4][2] = 3;

    GOTO[6][1] = 9;
    GOTO[6][2] = 3;

    GOTO[7][2] = 10;
}

int getTerminalIndex(char *sym) {
    for (int i = 0; i < num_terminals; i++) {
        if (strcmp(terminals[i], sym) == 0)
            return i;
    }
    return -1;
}

int getNonTerminalIndex(char *sym) {
    for (int i = 0; i < num_non_terminals; i++) {
        if (strcmp(non_terminals[i], sym) == 0)
            return i;
    }
    return -1;
}

void printParsingTable() {
    printf("\nLALR(1) PARSING TABLE:\n");
    printf("State\t");
    for (int i = 0; i < num_terminals; i++) {
        printf("%s\t", terminals[i]);
    }
    for (int i = 0; i < num_non_terminals; i++) {
        printf("%s\t", non_terminals[i]);
    }
    printf("\n");

    for (int i = 0; i < 12; i++) {
        printf("%d\t", i);
        for (int j = 0; j < num_terminals; j++) {
            printf("%s\t", ACTION[i][j] ? ACTION[i][j] : "-");
        }
        for (int j = 0; j < num_non_terminals; j++) {
            if (GOTO[i][j])
                printf("%d\t", GOTO[i][j]);
            else
                printf("-\t");
        }
        printf("\n");
    }
}

int main() {
    fillParsingTable();
    printParsingTable();
    return 0;
}
