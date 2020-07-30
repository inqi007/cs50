#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage:./caesar key\n");
        return 1;
    }
    
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if ((isalpha(argv[1][i])))
        {
            printf("Usage:./caesar key\n");
            return 1;
        }
    }
    int key = atoi(argv[1]);

    string p = get_string("plaintext: ");
    
    printf("ciphertext: ");
    for (int i = 0; i < strlen(p); i++)
    {
        if ((isalpha(p[i])) && (isupper(p[i])))
        {
            p[i] = ((((p[i] - 65) + key) % 26) + 65);
            printf("%c", p[i]);
        }
        else if ((isalpha(p[i])) && (islower(p[i])))
        {
            p[i] = ((((p[i] - 97) + key) % 26) + 97);
            printf("%c", p[i]);
        }
        else
        {
            printf("%c", p[i]);
        }
    }
    printf("\n");
}
