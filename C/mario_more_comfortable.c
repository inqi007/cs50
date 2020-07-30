#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do 
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (i + j < height - 1)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
            //Needs to less than the value which terminates the loop
            if (i + j == height + i - 1)
            {
                //Gives two spces
                printf("  ");
                //Prints after the space
                for (int x = 0; x <= i; x++)
                {
                    printf("#");
                }
            }
        }
        printf("\n");
    }
    
}
