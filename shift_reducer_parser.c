#include <stdio.h>
#include <string.h>

char stack[20], input[20];
int top = -1;

void push(char c) {
    stack[++top] = c;
    stack[top + 1] = '\0';
}

// Function to check and perform reductions based on grammar rules
void reduce() {
    int flag = 1;
    while (flag) {
        flag = 0;
        
        // Rule: id -> E
        if (top >= 1 && stack[top - 1] == 'i' && stack[top] == 'd') {
            stack[top - 1] = 'E';
            stack[top] = '\0';
            top--;
            printf("$%-10s\t\tReduce: E -> id\n", stack);
            flag = 1;
        }
        // Rule: E + E -> E
        else if (top >= 2 && stack[top - 2] == 'E' && stack[top - 1] == '+' && stack[top] == 'E') {
            stack[top - 2] = 'E';
            stack[top - 1] = '\0';
            stack[top] = '\0';
            top -= 2;
            printf("$%-10s\t\tReduce: E -> E + E\n", stack);
            flag = 1;
        }
        // Rule: E * E -> E
        else if (top >= 2 && stack[top - 2] == 'E' && stack[top - 1] == '*' && stack[top] == 'E') {
            stack[top - 2] = 'E';
            stack[top - 1] = '\0';
            stack[top] = '\0';
            top -= 2;
            printf("$%-10s\t\tReduce: E -> E + E\n", stack); // Or E -> E * E
            flag = 1;
        }
    }
}

int main() {
    int i = 0;
    
    printf("--- Shift Reduce Parser ---\n");
    printf("Grammar:\n");
    printf("  E -> E + E\n");
    printf("  E -> E * E\n");
    printf("  E -> id\n\n");

    printf("Enter input string (e.g., id+id*id): ");
    scanf("%s", input);

    printf("\n%-12s\t\t%-12s\t\t%-15s\n", "STACK", "INPUT", "ACTION");
    printf("----------------------------------------------------\n");

    int len = strlen(input);
    while (i < len) {
        // Shift tokens
        if (input[i] == 'i' && input[i + 1] == 'd') {
            push('i');
            push('d');
            i += 2;
            printf("$%-10s\t\t", stack);
            for (int j = i; j < len; j++) printf("%c", input[j]);
            printf("$\tShift id\n");
        } else {
            push(input[i]);
            i++;
            printf("$%-10s\t\t", stack);
            for (int j = i; j < len; j++) printf("%c", input[j]);
            printf("$\tShift %c\n", stack[top]);
        }

        // Attempt to reduce after each shift operation
        reduce();
    }

    // Final check for acceptance
    if (top == 0 && stack[0] == 'E') {
        printf("\nParsing Successful: The string is accepted!\n");
    } else {
        printf("\nParsing Failed: Syntax error or invalid input string.\n");
    }

    return 0;
}