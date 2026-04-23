#include <stdio.h>

int main()
{
    int n;
    char s[10][10];

    printf("Enter number of statements: ");
    scanf("%d", &n);

    printf("Enter the statements:\n");
    for (int i = 0; i < n; i++)
        scanf("%s", s[i]);

    printf("\nQuadruple Representation\n");
    printf("Op\tArg1\tArg2\tResult\n");

    for (int i = 0; i < n; i++)
        printf("%c\t%c\t%c\t%c\n", s[i][3], s[i][2], s[i][4], s[i][0]);

    printf("\nTriple Representation\n");
    printf("Index\tOp\tArg1\tArg2\n");

    for (int i = 0; i < n; i++)
        printf("%d\t%c\t%c\t%c\n", i, s[i][3], s[i][2], s[i][4]);

    printf("\nIndirect Triple Representation\n");
    printf("Pointer\tIndex\n");

    for (int i = 0; i < n; i++)
        printf("%d\t%d\n", i, i);
}