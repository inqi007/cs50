#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;
            //Ensure float
            int average = round((double)(r + g + b) / 3);
            if (average > 255)
            {
                average = 255;
            }
            
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;
            
            int sr = round(.393 * r + .769 * g + .189 * b);
            int sg = round(.349 * r + .686 * g + .168 * b);
            int sb = round(.272 * r + .534 * g + .131 * b);
            
            if (sr > 255)
            {
                sr = 255;
            }
            if (sg > 255)
            {
                sg = 255;
            }
            if (sb > 255)
            {
                sb = 255;
            }
            
            image[i][j].rgbtRed = sr;
            image[i][j].rgbtGreen = sg;
            image[i][j].rgbtBlue = sb;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            //Swap using a new variable
            tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
            
        }
    }
    
    return;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum_red = 0;
            int sum_green = 0;
            int sum_blue = 0;
            
            float total = 0.0;
            //For {-1, 0, 1}
            for (int y = -1; y < 2; y++)
            {
                int y_range = i + y;
                
                for (int x = -1; x < 2; x++)
                {
                    
                    int x_range = j + x;
                    
                    if (y_range >= 0 && y_range < height && x_range >= 0 && x_range < width)
                    {
                        sum_red += image[y_range][x_range].rgbtRed;
                        
                        sum_green += image[y_range][x_range].rgbtGreen;
                        sum_blue += image[y_range][x_range].rgbtBlue;
                        total += 1.0;
                    }
                }
            }
            
            int average_red = round((double) sum_red / total);
            if (average_red > 255)
            {
                average_red = 255;
            }
            int average_green = round((double) sum_green / total);
            if (average_green > 255)
            {
                average_green = 255;
            }
            int average_blue = round((double) sum_blue / total);
            if (average_blue > 255)
            {
                average_blue = 255;
            }
            
            tmp[i][j].rgbtRed = average_red;
            tmp[i][j].rgbtGreen = average_green;
            tmp[i][j].rgbtBlue = average_blue; 
        }
    }
    //To avoid loops overlapping 
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
            
        }
    }
    
    return;
}
