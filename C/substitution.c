#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    int count = 0;
    //Exits program if there is less than or more than 2 command line arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //Exits program if the key is not an alphabet
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!(isalpha(argv[1][i])))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
        //Counts the number of characters in the key
        count++;
    }
    //Exits program if key has more than or less than 26 characters
    if (count != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    if (count == 26)
    {
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            //Exits program if key has digits 
            if (isdigit(argv[1][i]))
            {
                printf("Key must only contain alphabetic characters.\n");
                return 1;
            }
        }
    }
    //Exits program if there are repeated characters in the key
    //Iterates two times to match characters
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        for (int j = 0; j < strlen(argv[1]); j++)
        {
            //To avoid matching the same character the first time it appears
            if (i != j)
            {
                if (argv[1][i] == argv[1][j])
                {
                    printf("Key must not contain repeated characters.\n");
                    return 1;
                }
            }
        }
    }
    
    string text = get_string("plaintext: ");
    printf("ciphertext: ");
    
    //Assign two arrays to store alphabets
    string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string lower = "abcdefghijklmnopqrstuvwxyz";
    
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]) && isupper(text[i]))
        {
            //Iterates over the array with uppercase alphabets
            for (int j = 0; j < strlen(upper); j++)
            {
                //Identifies the position of the alphabet inputted 
                if (text[i] == upper[j])
                {
                    //Converts the inputted alphabet with the key and converts it into the size of the inputted alphabet
                    printf("%c", toupper(argv[1][j]));
                }
            }
        }
        else if (isalpha(text[i]) && islower(text[i]))
        {
            //Iterates over the array with lowercase alphabets
            for (int k = 0; k < strlen(lower); k++)
            {
                //Identifies the position of the alphabet inputted
                if (text[i] == lower[k])
                {
                    //Converts the inputted alphabet with the key and converts it into the size of the inputted alphabet
                    printf("%c", tolower(argv[1][k]));
                }
            }
        }
        else 
        {
            //Prints all the other non-alphabetic characters as is
            printf("%c", text[i]);
        }
    }
    printf("\n");
    return 0;
}
