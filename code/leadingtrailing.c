#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 10

char productions[MAX][20];
char leading[MAX][20];
char trailing[MAX][20];
int n;

int isTerminal(char symbol) {
    return !isupper(symbol);  // terminals are lowercase or symbols
}

void addToSet(char *set, char symbol) {
    if (!strchr(set, symbol)) {
        int len = strlen(set);
        set[len] = symbol;
        set[len + 1] = '\0';
    }
}

void computeLeading(char nt, char *set) {
    for (int i = 0; i < n; i++) {
        if (productions[i][0] == nt) {
            for (int j = 2; productions[i][j] != '\0'; j++) {
                char symbol = productions[i][j];

                if (symbol == '|') continue;

                if (isTerminal(symbol)) {
                    addToSet(set, symbol);
                    break;
                } else if (isupper(symbol)) {
                    if (symbol != nt) {
                        computeLeading(symbol, set);
                        break;
                    }
                }
                break;
            }
        }
    }
}

void computeTrailing(char nt, char *set) {
    for (int i = 0; i < n; i++) {
        if (productions[i][0] == nt) {
            int len = strlen(productions[i]);
            for (int j = len - 1; j >= 2; j--) {
                char symbol = productions[i][j];
                if (symbol == '|') continue;

                if (isTerminal(symbol)) {
                    addToSet(set, symbol);
                    break;
                } else if (isupper(symbol)) {
                    if (symbol != nt) {
                        computeTrailing(symbol, set);
                        break;
                    }
                }
                break;
            }
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);
    getchar();  // Consume newline

    for (int i = 0; i < n; i++) {
        printf("Enter production %d (e.g., E=E+T): ", i + 1);
        fgets(productions[i], sizeof(productions[i]), stdin);
        productions[i][strcspn(productions[i], "\n")] = '\0';  // Remove newline
    }

    for (int i = 0; i < n; i++) {
        char nt = productions[i][0];

        computeLeading(nt, leading[nt - 'A']);
        computeTrailing(nt, trailing[nt - 'A']);
    }

    printf("\nLEADING and TRAILING sets:\n");
    for (int i = 0; i < n; i++) {
        char nt = productions[i][0];

        printf("LEADING(%c): { ", nt);
        for (int j = 0; j < strlen(leading[nt - 'A']); j++) {
            printf("%c ", leading[nt - 'A'][j]);
        }
        printf("}\n");

        printf("TRAILING(%c): { ", nt);
        for (int j = 0; j < strlen(trailing[nt - 'A']); j++) {
            printf("%c ", trailing[nt - 'A'][j]);
        }
        printf("}\n");
    }

    return 0;
}
