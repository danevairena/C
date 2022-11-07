#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    // Checking if the user entered a correct input:
    if (argc != 2)
    {
        printf("You're not using it correctly!\n");
        return 1;
    }

    // Opening the file in argv[1]
    FILE *f = fopen(argv[1], "r");

    // Validating that there's a file in argv[1]
    if (f == NULL)
    {
        printf("File hasn't found\n");
        return 1;
    }

    //initializing variables
    unsigned char bytes[512];
    int counter = 0;
    FILE *img = NULL;

    //go though card file untill there aren't any blocks left
    while (fread(bytes, 512, 1, f) == 1)
    {
        //check for begining of a jpeg image
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            if (img != NULL)
            {
                fclose(img);
            }

            char filename[8];

            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Couldn't open file\n");
                return 1;
            }
            counter++;
        }

        if (img != NULL)
        {
            fwrite(bytes, 512, 1, img);
        }
    }

    if (img != NULL)
    {
        fclose(img);
    }
    fclose(f);
}
