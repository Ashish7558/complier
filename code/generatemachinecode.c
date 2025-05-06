#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char statement[100];
    char var1, var2, var3, operator;

    printf("Enter a simple C statement (e.g., a = b + c): ");
    fgets(statement, sizeof(statement), stdin);

    // Remove trailing newline if present
    size_t len = strlen(statement);
    if (len > 0 && statement[len - 1] == '\n') {
        statement[len - 1] = '\0';
    }

    // Parse the statement, allowing for optional spaces
    if (sscanf(statement, " %c = %c %c %c", &var1, &var2, &operator, &var3) != 4) {
        printf("Invalid statement format. Please enter in format: a = b + c\n");
        return 1;
    }

    // Ensure all are alphabetic characters and operator is valid
    if (!isalpha(var1) || !isalpha(var2) || !isalpha(var3)) {
        printf("Variables must be alphabetic characters.\n");
        return 1;
    }

    printf("\nGenerated Machine Code (Simulated):\n");

    // Simulate 3-address machine code
    printf("MOV R1, %c\n", var2);
    switch (operator) {
        case '+':
            printf("ADD R1, %c\n", var3);
            break;
        case '-':
            printf("SUB R1, %c\n", var3);
            break;
        case '*':
            printf("MUL R1, %c\n", var3);
            break;
        case '/':
            printf("DIV R1, %c\n", var3);
            break;
        default:
            printf("Unsupported operator '%c'!\n", operator);
            return 1;
    }
    printf("MOV %c, R1\n", var1);

    return 0;
}
