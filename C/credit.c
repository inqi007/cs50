#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <strings.h>

int main(void)
{
    //Declaring variables to count the addition of numbers within the credit card
    int sum = 0;
    int total = 0;

    //Assigning long int because the number is large
    long int number = get_long("Number: ");

    //Variables to make calculations simpler
    long int fifteen = 1000000000000000;
    long int fourteen = 100000000000000;
    long int thirteen = 10000000000000;
    long int twelve = 1000000000000;

    //To store the value of number inserted
    long int Number = number;

    while (Number != 0)
    {
        //Gets the last number
        int x = Number % 10;
        //Removes the last number
        Number /= 10;
        int y = Number % 10;
        Number /= 10;
        //Adds the remaining numbers
        sum += x;
        //Multiplies second-to-last digits
        int digits = y * 2;
        //Separate the product into individual digits to be added
        while (digits != 0)
        {
            int z = digits % 10;
            digits /= 10;
            total += z;
        }
    }
    int check_sum = sum + total;
    //Checks if the last digit of checksum is zero
    int valid = check_sum % 10;
    if (valid != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    if (number / fifteen == 4 || number / twelve == 4)
    {
        printf("VISA\n");
    }
    else if (number / thirteen == 34 || number / thirteen == 37)
    {
        printf("AMEX\n");
    }
    else if (number / fourteen == 51 || number / fourteen == 52 || number / fourteen == 53 || number / fourteen == 54 || number / fourteen == 55)
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }

}
