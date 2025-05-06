#include <stdio.h>
#include <string.h>

#define MAX 100

int tempCount = 0;
int tripleCount = 0;

char expr[100];

// Quadruple structure
typedef struct {
    char op[5];
    char arg1[10];
    char arg2[10];
    char result[10];
} Quad;

// Triple structure
typedef struct {
    char op[5];
    char arg1[10];
    char arg2[10];
} Triple;

Quad quadruples[MAX];
Triple triples[MAX];
int tripleIndex[MAX]; // For indirect triples

// Generate a new temporary variable like t1, t2, ...
void newTemp(char *temp) {
    sprintf(temp, "t%d", ++tempCount);
}

// Generate quadruples
void generateQuadruples(char *input) {
    char a, b, c, op;
    char temp1[10], temp2[10];

    printf("\nGenerating Quadruples:\n");

    // Sample fixed pattern: a = b + c * d
    // We assume: + is lower precedence than *
    // So compute c * d first

    sscanf(input, "%c = %c %c %c %c %c", &a, &b, &op, &c, &op, &b); // not general, just placeholder
    // We'll handle more correctly below:

    char lhs, arg1, arg2, op1, op2, arg3;
    sscanf(input, "%c = %c %c %c %c %c", &lhs, &arg1, &op1, &arg2, &op2, &arg3);

    // First c * d => t1
    newTemp(temp1);
    strcpy(quadruples[0].op, "*");
    sprintf(quadruples[0].arg1, "%c", arg2);
    sprintf(quadruples[0].arg2, "%c", arg3);
    strcpy(quadruples[0].result, temp1);

    // Then b + t1 => t2
    newTemp(temp2);
    strcpy(quadruples[1].op, "+");
    sprintf(quadruples[1].arg1, "%c", arg1);
    strcpy(quadruples[1].arg2, temp1);
    strcpy(quadruples[1].result, temp2);

    // Then a = t2
    strcpy(quadruples[2].op, "=");
    strcpy(quadruples[2].arg1, temp2);
    strcpy(quadruples[2].arg2, "-");
    sprintf(quadruples[2].result, "%c", lhs);

    for (int i = 0; i < 3; i++) {
        printf("(%s, %s, %s, %s)\n", quadruples[i].op, quadruples[i].arg1, quadruples[i].arg2, quadruples[i].result);
    }
}

// Generate triples
void generateTriples() {
    printf("\nGenerating Triples:\n");

    // Use same operation order as above
    // Index 0: c * d
    strcpy(triples[0].op, "*");
    strcpy(triples[0].arg1, "c");
    strcpy(triples[0].arg2, "d");

    // Index 1: b + (0)
    strcpy(triples[1].op, "+");
    strcpy(triples[1].arg1, "b");
    sprintf(triples[1].arg2, "(0)");

    // Index 2: a = (1)
    strcpy(triples[2].op, "=");
    sprintf(triples[2].arg1, "(1)");
    strcpy(triples[2].arg2, "-");

    for (int i = 0; i < 3; i++) {
        printf("(%d) (%s, %s, %s)\n", i, triples[i].op, triples[i].arg1, triples[i].arg2);
    }
}

// Generate indirect triples
void generateIndirectTriples() {
    printf("\nGenerating Indirect Triples:\n");

    // Initialize index table
    for (int i = 0; i < 3; i++) {
        tripleIndex[i] = i;
    }

    printf("Index Table:\n");
    for (int i = 0; i < 3; i++) {
        printf("[%d] -> %d\n", i, tripleIndex[i]);
    }

    printf("\nTriples:\n");
    for (int i = 0; i < 3; i++) {
        int idx = tripleIndex[i];
        printf("(%d) (%s, %s, %s)\n", i, triples[idx].op, triples[idx].arg1, triples[idx].arg2);
    }
}

int main() {
    printf("Enter an expression (e.g., a = b + c * d): ");
    fgets(expr, sizeof(expr), stdin);
    expr[strcspn(expr, "\n")] = '\0'; // remove newline

    generateQuadruples(expr);
    generateTriples();
    generateIndirectTriples();

    return 0;
}
