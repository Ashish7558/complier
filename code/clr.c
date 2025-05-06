#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PROD 10
#define MAX_ITEMS 100

typedef struct {
    char lhs;
    char rhs[10];
} Production;

typedef struct {
    char lhs;
    char rhs[10];
    int dotPos;
    char lookahead;
} LR1Item;

Production prod[MAX_PROD];
int prodCount = 0;

LR1Item itemSet[MAX_ITEMS];
int itemCount = 0;

void addProduction(char lhs, char *rhs) {
    prod[prodCount].lhs = lhs;
    strcpy(prod[prodCount].rhs, rhs);
    prodCount++;
}

void displayProductions() {
    printf("Productions:\n");
    for (int i = 0; i < prodCount; i++) {
        printf("%c -> %s\n", prod[i].lhs, prod[i].rhs);
    }
}

void addLR1Item(char lhs, char *rhs, int dotPos, char lookahead) {
    LR1Item item;
    item.lhs = lhs;
    strcpy(item.rhs, rhs);
    item.dotPos = dotPos;
    item.lookahead = lookahead;

    // Check for duplicates
    for (int i = 0; i < itemCount; i++) {
        if (itemSet[i].lhs == item.lhs &&
            strcmp(itemSet[i].rhs, item.rhs) == 0 &&
            itemSet[i].dotPos == item.dotPos &&
            itemSet[i].lookahead == item.lookahead) {
            return;
        }
    }

    itemSet[itemCount++] = item;
}

void printItemSet() {
    printf("\nCanonical LR(1) Items:\n");
    for (int i = 0; i < itemCount; i++) {
        printf("[%c -> ", itemSet[i].lhs);
        for (int j = 0; j < strlen(itemSet[i].rhs); j++) {
            if (j == itemSet[i].dotPos)
                printf(".");
            printf("%c", itemSet[i].rhs[j]);
        }
        if (itemSet[i].dotPos == strlen(itemSet[i].rhs))
            printf(".");
        printf(", %c]\n", itemSet[i].lookahead);
    }
}

void closure() {
    // Simple closure for starting item only
    for (int i = 0; i < itemCount; i++) {
        char symbol = itemSet[i].rhs[itemSet[i].dotPos];
        if (isupper(symbol)) {
            for (int j = 0; j < prodCount; j++) {
                if (prod[j].lhs == symbol) {
                    addLR1Item(prod[j].lhs, prod[j].rhs, 0, itemSet[i].lookahead);
                }
            }
        }
    }
}

int main() {
    // Augmented Grammar: S' → E
    addProduction('S', "E");
    addProduction('E', "E+T");
    addProduction('E', "T");
    addProduction('T', "T*F");
    addProduction('T', "F");
    addProduction('F', "(E)");
    addProduction('F', "i");  // id = i

    displayProductions();

    // Initial LR(1) item: [S → .E, $]
    addLR1Item('S', "E", 0, '$');
    closure();

    printItemSet();

    return 0;
}
