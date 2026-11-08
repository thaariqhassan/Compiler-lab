#include <stdio.h>
#include <string.h>

int isKeyword(char word[])
{
    char keywords[][20] = {
        "auto","break","case","char","const","continue",
        "default","do","double","else","enum","extern",
        "float","for","goto","if","int","long",
        "register","return","short","signed","sizeof",
        "static","struct","switch","typedef","union",
        "unsigned","void","volatile","while"
    };

    int n = sizeof(keywords) / sizeof(keywords[0]);

    for(int i = 0; i < n; i++)
    {
        if(strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main()
{
    FILE *fp;
    char ch, word[50];
    int i = 0;

    fp = fopen("input.c", "r");

    if(fp == NULL)
    {
        printf("File not found.\n");
        return 0;
    }

    while((ch = fgetc(fp)) != EOF)
    {
        if(isalpha(ch))
        {
            i = 0;
            word[i++] = ch;

            while((ch = fgetc(fp)) != EOF &&
                  (isalnum(ch) || ch == '_'))
            {
                word[i++] = ch;
            }

            word[i] = '\0';

            if(isKeyword(word))
                printf("%s : Keyword\n", word);
        }
    }

    fclose(fp);
    return 0;
}
