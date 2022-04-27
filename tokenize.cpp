#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <Shlwapi.h>
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma pack(1)

typedef struct
{
    char token[50];
} tokens;

void tokenize(const char file_path[])
{
    FILE *pfile;
    char ch;
    char temp_token[50];
    char *ptemp_token = temp_token;
    tokens *ptokens;
    int i = 0, token_complete = 0;
    char *mloc = temp_token;

    pfile = fopen(file_path, "r");
    fseek(pfile, 0, SEEK_END);
    long size = ftell(pfile);

    ptokens = (tokens *)malloc(100 * sizeof(tokens));
    printf("size:  %ld\n", size);
    rewind(pfile);

    if (pfile == NULL)
    {
        printf("file can't be opened\n");
        exit(0);
    }

    do
    {
        ch = fgetc(pfile);
        // printf("%c", ch);
        if (ch == ' ')
        {
            token_complete = 1;
            continue;
        }

        if (token_complete && temp_token)
        {
            strcpy(ptokens->token, temp_token);
            i++;
            token_complete = 0;
            ptemp_token = temp_token;
        }

        if (isalnum(ch) || (ch == '_'))
        {
            *ptemp_token = ch;
            ptemp_token++;
        }
        else if (!isalnum(ch))
        {
            strcpy((ptokens + i)->token, &ch);
            i++;
            // ptokens++;
            token_complete = 1;
        }
    } while (ch != EOF);

    // if (ch == EOF) {
    //     *tokens = '\0';
    // }
    printf("tokens => \n\t");

    for (int count = 0; count < 5; count++)
    {
        printf("%S", (ptokens + count)->token);
    }

    fclose(pfile);
    free(ptokens);
}

int main()
{
    const char file_path[] = "C:\\Users\\Microsoft\\Desktop\\cppTest\\test.txt";

    tokenize(file_path);
    return 0;
}
