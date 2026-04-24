#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char prod[MAX][10];
int n;

// Structure for LR(0) item
typedef struct
{
    char lhs;
    char rhs[10];
    int dot;
} Item;

Item states[20][20];
int stateCount = 0;
int itemCount[20];

// Add item if not already present
int exists(int s, Item it)
{
    for (int i = 0; i < itemCount[s]; i++)
    {
        if (states[s][i].lhs == it.lhs &&
            strcmp(states[s][i].rhs, it.rhs) == 0 &&
            states[s][i].dot == it.dot)
            return 1;
    }
    return 0;
}

// Closure function
void closure(int s)
{
    for (int i = 0; i < itemCount[s]; i++)
    {
        Item it = states[s][i];

        if (it.dot < strlen(it.rhs))
        {
            char next = it.rhs[it.dot];

            if (isupper(next))
            {
                for (int j = 0; j < n; j++)
                {
                    if (prod[j][0] == next)
                    {
                        Item newItem;
                        newItem.lhs = next;
                        strcpy(newItem.rhs, prod[j] + 3);
                        newItem.dot = 0;

                        if (!exists(s, newItem))
                        {
                            states[s][itemCount[s]++] = newItem;
                        }
                    }
                }
            }
        }
    }
}

// Print state
void printState(int s)
{
    printf("\nI%d:\n", s);
    for (int i = 0; i < itemCount[s]; i++)
    {
        Item it = states[s][i];
        printf("%c -> ", it.lhs);

        for (int j = 0; j < strlen(it.rhs); j++)
        {
            if (j == it.dot)
                printf(".");
            printf("%c", it.rhs[j]);
        }
        if (it.dot == strlen(it.rhs))
            printf(".");
        printf("\n");
    }
}

// Compare states
int sameState(int s1, int s2)
{
    if (itemCount[s1] != itemCount[s2])
        return 0;

    for (int i = 0; i < itemCount[s1]; i++)
    {
        if (!exists(s2, states[s1][i]))
            return 0;
    }
    return 1;
}

// GOTO function
int goTo(int s, char X)
{
    int newState = stateCount;
    itemCount[newState] = 0;

    for (int i = 0; i < itemCount[s]; i++)
    {
        Item it = states[s][i];

        if (it.dot < strlen(it.rhs) && it.rhs[it.dot] == X)
        {
            Item moved = it;
            moved.dot++;

            states[newState][itemCount[newState]++] = moved;
        }
    }

    closure(newState);

    // Check if already exists
    for (int i = 0; i < stateCount; i++)
    {
        if (sameState(i, newState))
        {
            return i;
        }
    }

    stateCount++;
    return newState;
}

int main()
{
    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (e.g., S->AA):\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%s", prod[i]);
    }

    // Numbering
    printf("\n1. Numbering the productions:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d. %c -> %s\n", i + 1, prod[i][0], prod[i] + 3);
    }

    // Augmented grammar
    printf("\n2. Augmented Grammar:\n");
    printf("S' -> %c\n", prod[0][0]);
    for (int i = 0; i < n; i++)
    {
        printf("%c -> %s\n", prod[i][0], prod[i] + 3);
    }

    printf("\n3. LR(0) Items\n");

    // Initial state I0
    states[0][0].lhs = 'Z'; // use Z as S'
    strcpy(states[0][0].rhs, "S");
    states[0][0].dot = 0;

    itemCount[0] = 1;
    stateCount = 1;

    closure(0);
    printState(0);

    // Generate states
    for (int s = 0; s < stateCount; s++)
    {
        char symbols[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

        for (int k = 0; k < strlen(symbols); k++)
        {
            char X = symbols[k];
            int next = goTo(s, X);

            if (next != s && itemCount[next] > 0)
            {
                printf("\nGoto(I%d, %c)\n", s, X);
                printState(next);
            }
        }
    }

    return 0;
}