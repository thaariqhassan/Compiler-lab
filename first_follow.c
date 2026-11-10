#include <stdio.h>
#include <ctype.h>
#include <string.h>

int n;
char production[10][20];
char first[10], follow[10];

void findFirst(char c, int q1, int q2);
void findFollow(char c);

int firstIndex, followIndex;

int main()
{
    int i;
    char ch;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (Example: E=TR):\n");
    for(i = 0; i < n; i++)
        scanf("%s", production[i]);

    printf("\nFIRST Sets:\n");
    for(i = 0; i < n; i++)
    {
        ch = production[i][0];

        firstIndex = 0;
        findFirst(ch, 0, 0);

        printf("FIRST(%c) = { ", ch);
        for(int j = 0; j < firstIndex; j++)
            printf("%c ", first[j]);
        printf("}\n");
    }

    printf("\nFOLLOW Sets:\n");
    for(i = 0; i < n; i++)
    {
        ch = production[i][0];

        followIndex = 0;
        findFollow(ch);

        printf("FOLLOW(%c) = { ", ch);
        for(int j = 0; j < followIndex; j++)
            printf("%c ", follow[j]);
        printf("}\n");
    }

    return 0;
}

void findFirst(char c, int q1, int q2)
{
    int j;

    if(!isupper(c))
    {
        first[firstIndex++] = c;
        return;
    }

    for(j = 0; j < n; j++)
    {
        if(production[j][0] == c)
        {
            if(production[j][2] == '#')
            {
                if(production[q1][q2] == '\0')
                    first[firstIndex++] = '#';
                else
                    findFirst(production[q1][q2], q1, q2 + 1);
            }
            else if(!isupper(production[j][2]))
            {
                first[firstIndex++] = production[j][2];
            }
            else
            {
                findFirst(production[j][2], j, 3);
            }
        }
    }
}

void findFollow(char c)
{
    int i, j;

    if(production[0][0] == c)
        follow[followIndex++] = '$';

    for(i = 0; i < n; i++)
    {
        for(j = 2; production[i][j] != '\0'; j++)
        {
            if(production[i][j] == c)
            {
                if(production[i][j + 1] != '\0')
                {
                    findFirst(production[i][j + 1], i, j + 2);
                }

                if(production[i][j + 1] == '\0' &&
                   c != production[i][0])
                {
                    findFollow(production[i][0]);
                }
            }
        }
    }
}