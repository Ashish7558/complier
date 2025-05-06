#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int nextinstr = 0;

typedef struct {
    int index;
    char code[50];
} Quad;

Quad quads[MAX];

typedef struct {
    int list[MAX];
    int size;
} List;

// Generate new instruction and return its index
int gen(const char *code) {
    strcpy(quads[nextinstr].code, code);
    quads[nextinstr].index = nextinstr;
    return nextinstr++;
}

// Create a list with one instruction address
List makelist(int i) {
    List l;
    l.size = 1;
    l.list[0] = i;
    return l;
}

// Merge two lists
List merge(List l1, List l2) {
    List l;
    l.size = 0;
    for (int i = 0; i < l1.size; i++)
        l.list[l.size++] = l1.list[i];
    for (int i = 0; i < l2.size; i++)
        l.list[l.size++] = l2.list[i];
    return l;
}

// Backpatch a list of instruction addresses with target
void backpatch(List l, int target) {
    char op[30];
    char newCode[50];
    for (int i = 0; i < l.size; i++) {
        // Extract the part before "goto"
        sscanf(quads[l.list[i]].code, "%s", op);
        if (strstr(quads[l.list[i]].code, "goto") != NULL) {
            sprintf(newCode, "%s %d", quads[l.list[i]].code, target);
            strcpy(quads[l.list[i]].code, newCode);
        }
    }
}

void printCode() {
    printf("\nGenerated Quadruples (with Backpatching):\n");
    for (int i = 0; i < nextinstr; i++) {
        printf("%d: %s\n", quads[i].index, quads[i].code);
    }
}

int main() {
    // Simulate a condition and jump
    int i = gen("if a < b goto");
    List trueList = makelist(i);

    int j = gen("goto");  // false case
    List falseList = makelist(j);

    // Simulate next instruction (beginning of body)
    int body = nextinstr;
    gen("x = x + 1");

    int k = gen("goto");  // loop back
    List loopBack = makelist(k);

    // Backpatch true list to body
    backpatch(trueList, body);

    // Backpatch loop to start of condition
    backpatch(loopBack, i);

    // Next instruction after loop
    int next = nextinstr;

    // Backpatch false list to next
    backpatch(falseList, next);

    printCode();

    return 0;
}

