#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    //Opening the file to be checked
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        return 2;
    }
    //Boolean expression to determine first jpeg
    bool (first) = false;

    unsigned char data[512];
    int number = 0;
    //File that stores 8 bytes
    char filename[8];
    FILE *new_file = NULL;


    while (fread(data, 512, 1, file) != 0x00)
    {
        if (data[0] == 0xff && data[1] == 0xd8 && data[2] == 0xff && (data[3] & 0xf0) == 0xe0)
        {
            if (first == false)
            {
                //Create new file
                sprintf(filename, "%03i.jpg", number);
                new_file = fopen(filename, "w");
                if (new_file == NULL)
                {
                    return 3;
                }
                fwrite(data, 1, 512, new_file);
                number++;
                first = true;
            }

            else if (first == true)
            {
                //Close old file
                fclose(new_file);
                //Create new file
                sprintf(filename, "%03i.jpg", number);
                new_file = fopen(filename, "w");
                if (new_file == NULL)
                {
                    return 4;
                }
                fwrite(data, 1, 512, new_file);
                number++;
            }


        }
        else
        {
            if (first == true)
            {
                fwrite(data, 512, 1, new_file);
            }
            else if (first == false)
            {
                continue;
            }
        }

    }
    fclose(file);
    fclose(new_file);
}
