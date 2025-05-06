#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    if (top == -1) return '\0';
    return stack[top--];
}

char peek() {
    if (top == -1) return '\0';
    return stack[top];
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        default: return 0;
    }
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Convert infix to postfix
void infixToPostfix(char* infix, char* postfix) {
    int i, j = 0;
    char c;

    for (i = 0; infix[i]; i++) {
        c = infix[i];
        if (isalnum(c)) {
            postfix[j++] = c;
        }
        else if (c == '(') {
            push(c);
        }
        else if (c == ')') {
            while (peek() != '(') {
                postfix[j++] = pop();
            }
            pop(); // Remove '('
        }
        else if (isOperator(c)) {
            while (precedence(peek()) >= precedence(c)) {
                postfix[j++] = pop();
            }
            push(c);
        }
    }

    while (top != -1) {
        postfix[j++] = pop();
    }

    postfix[j] = '\0';
}

// Convert infix to prefix
void reverse(char* str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char tmp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = tmp;
    }
}

void replaceParens(char* expr) {
    for (int i = 0; expr[i]; i++) {
        if (expr[i] == '(')
            expr[i] = ')';
        else if (expr[i] == ')')
            expr[i] = '(';
    }
}

void infixToPrefix(char* infix, char* prefix) {
    char revInfix[MAX], revPostfix[MAX];
    strcpy(revInfix, infix);

    reverse(revInfix);
    replaceParens(revInfix);

    top = -1;  // Reset stack
    infixToPostfix(revInfix, revPostfix);

    reverse(revPostfix);
    strcpy(prefix, revPostfix);
}

int main() {
    char infix[MAX], postfix[MAX], prefix[MAX];

    printf("Enter infix expression (e.g., a+(b*c)): ");
    fgets(infix, sizeof(infix), stdin);
    infix[strcspn(infix, "\n")] = '\0'; // Remove newline

    infixToPostfix(infix, postfix);
    infixToPrefix(infix, prefix);

    printf("\nIntermediate Code Generation:\n");
    printf("Postfix (RPN): %s\n", postfix);
    printf("Prefix  (PN):  %s\n", prefix);

    return 0;
}
