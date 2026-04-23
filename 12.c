#include <stdio.h>
#include <string.h>

int main()
{
    char s[2][10];

    printf("Enter 2 statements:\n");
    scanf("%s %s", s[0], s[1]);

    for (int i = 0; i < 2; i++)
    {
        char r = s[i][0], a = s[i][2];

        if (strlen(s[i]) == 3)
            printf("LOAD %c\nSTORE %c\n\n", a, r);
        else
        {
            char op = s[i][3], b = s[i][4];
            printf("LOAD %c\n", a);

            if (op == '+')
                printf("ADD ");
            else if (op == '-')
                printf("SUB ");
            else if (op == '*')
                printf("MUL ");
            else if (op == '/')
                printf("DIV ");

            printf("%c\nSTORE %c\n\n", b, r);
        }
    }
}