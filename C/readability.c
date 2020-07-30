#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int main(void)
{
    string text = get_string("Text: ");
    
    int element = 0;
    
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            element += 1;
        }
        if (text[i] >= 'A' && text[i] <= 'Z')
        {
            element += 1;
        }
    }
    
    int w = 0; 
    
    if ((isalpha(text[0])))
    {
        w += 1;
    }
    else
    {
        w = 0;
    }
    for (int i = 0; i < strlen(text); i++)
    {
        if ((isspace(text[i])) && (isalpha(text[i + 1])))
        {
            w += 1;
        }
        if (text[i] == '"' && (isalpha(text[i + 1])))
        {
            w += 1;
        }
    }
    
    int sen = 0;
    
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sen += 1;
        }
    }
    
    float L = ((float)element / (float)w) * 100;
    float S = ((float)sen / (float)w) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else 
    {
        printf("Grade %i\n", index);
    }
}
