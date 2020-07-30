#include <stdio.h>
#include <cs50.h>
#include <math.h>
int main(void)
{
    float x;
    int p = 1;
    int n = 5;
    int d = 10;
    int q = 25;
    int u;
    int i;
    int k;
    int e;
    int y;
    
    do 
    {
        x = get_float("Change owed: ");
    }
    while (x < 0);
    y = round(x * 100);
    for (u = 0; y > q || y == q; u++)
    {
        y = y - q; 
       
    }
    for (i = 0; y > d || y == d; i++)
    {
        y = y - d;
    }
    for (k = 0; y > n || y == n; k++)
    {
        y = y - n;
    }
    for (e = 0; y > p || y == p; e++)
    {
        y = y - p;
    }
    printf("%i\n", u + i + k + e);
}
