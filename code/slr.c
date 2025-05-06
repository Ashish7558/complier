#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 20

// Grammar Productions
char prod[MAX][10] = {
    "E'->E",
    "E->E+T",
    "E->T",
    "T->T*F",
    "T->F",
    "F->(E)",
    "F->i"
};

char terminals[] = {'i', '+', '*', '(', ')', '$'};
char nonTerminals[] = {'E', 'T', 'F'};

// Sample parsing table: [states][terminals + non-terminals]
char action[12][6][10] = {
    {"s5", "", "", "s4", "", ""},        // state 0
    {"", "s6", "", "", "", "acc"},       // state 1
    {"", "r2", "s7", "", "r2", "r2"},     // state 2
    {"", "r4", "r4", "", "r4", "r4"},     // state 3
    {"s5", "", "", "s4", "", ""},        // state 4
    {"", "r6", "r6", "", "r6", "r6"},     // state 5
    {"s5", "", "", "s4", "", ""},        // state 6
    {"s5", "", "", "s4", "", ""},        // state 7
    {"", "s6", "", "", "s11", ""},       // state 8
    {"", "r1", "s7", "", "r1", "r1"},     // state 9
    {"", "r3", "r3", "", "r3", "r3"},     // state 10
    {"", "r5", "r5", "", "r5", "r5"}      // state 11
};

// GOTO Table (states × non-terminals)
int goTo[12][3] = {
    {1, 2, 3},
    {-1, -1, -1},
    {-1, -1, -1},
    {-1, -1, -1},
    {8, 2, 3},
    {-1, -1, -1},
    {-1, 9, 3},
    {-1, -1, 10},
    {-1, -1, -1},
    {-1, -1, -1},
    {-1, -1, -1},
    {-1, -1, -1}
};

int getIndex(char symbol) {
    for (int i = 0; i < 6; i++)
        if (terminals[i] == symbol)
            return i;
    return -1;
}

int getNonTerminalIndex(char symbol) {
    for (int i = 0; i < 3; i++)
        if (nonTerminals[i] == symbol)
            return i;
    return -1;
}

void parseInput(char *input) {
    int stack[MAX], top = 0;
    stack[top++] = 0; // Initial state

    int ip = 0;
    char a = input[ip];

    printf("Stack\t\tInput\t\tAction\n");

    while (1) {
        int state = stack[top - 1];
        int col = getIndex(a);
        char *act = action[state][col];

        // Print stack and input
        for (int i = 0; i < top; i++) printf("%d ", stack[i]);
        printf("\t\t%s\t\t%s\n", &input[ip], act);

        if (strncmp(act, "s", 1) == 0) {
            int num = atoi(act + 1);
            stack[top++] = a;  // push symbol
            stack[top++] = num; // push state
            a = input[++ip];    // advance input
        } else if (strncmp(act, "r", 1) == 0) {
            int prodNum = atoi(act + 1);
            int len = strlen(strchr(prod[prodNum], '>') + 1) * 2; // *2 for symbol and state
            top -= len;

            int st = stack[top - 1];
            stack[top++] = prod[prodNum][0]; // push LHS

            int gotoCol = getNonTerminalIndex(prod[prodNum][0]);
            stack[top++] = goTo[st][gotoCol];
        } else if (strcmp(act, "acc") == 0) {
            printf("\nAccepted!\n");
            break;
        } else {
            printf("\nError: Invalid string!\n");
            break;
        }
    }
}

int main() {
    char input[30];
    printf("Enter input string (e.g., i+i*i): ");
    scanf("%s", input);
    strcat(input, "$");

    parseInput(input);
    return 0;
}
