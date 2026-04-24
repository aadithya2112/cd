#include <stdio.h>
#include <string.h>

int main()
{
    char input[20], stack[20];
    char prod[20], lhs, rhs[10];
    int i = 0, top = 0;

    // Input production
    printf("Enter production (e.g., S->aSb): ");
    scanf("%s", prod);

    lhs = prod[0];         // Left side (S)
    strcpy(rhs, prod + 3); // Right side (aSb)

    // Input string
    printf("Enter input string: ");
    scanf("%s", input);
    strcat(input, "$");

    // Initialize stack
    stack[top++] = '$';
    stack[top] = '\0';

    printf("\nStack\tInput\tAction\n");
    printf("----------------------------------------\n");

    while (1)
    {
        // SHIFT
        stack[top++] = input[i++];
        stack[top] = '\0';
        printf("%s\t%s\tShift\n", stack, input + i);

        // Try reductions repeatedly
        int reduced;
        do
        {
            reduced = 0;

            int len = strlen(rhs);

            // Check for given production (e.g., aSb)
            if (top >= len && strncmp(stack + top - len, rhs, len) == 0)
            {
                top -= len;
                stack[top++] = lhs;
                stack[top] = '\0';

                printf("%s\t%s\tReduce %c->%s\n", stack, input + i, lhs, rhs);
                reduced = 1;
            }

            // Extra base case: ab -> S (needed for grammar S->aSb)
            else if (top >= 2 &&
                     stack[top - 2] == 'a' &&
                     stack[top - 1] == 'b')
            {

                top -= 2;
                stack[top++] = lhs;
                stack[top] = '\0';

                printf("%s\t%s\tReduce %c->ab\n", stack, input + i, lhs);
                reduced = 1;
            }

        } while (reduced);

        // ACCEPT
        if (strcmp(stack, "$S") == 0 && input[i] == '$')
        {
            printf("%s\t%s\tAccept\n", stack, input + i);
            break;
        }

        // REJECT
        if (input[i] == '$')
        {
            printf("%s\t%s\tReject\n", stack, input + i);
            break;
        }
    }

    return 0;
}