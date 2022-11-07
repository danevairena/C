#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //check arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    else
    {
        return 0;
    }

    FILE *infile = fopen(argv[1], "r");

    //check if could not open the file
    if (infile == NULL)
    {
        printf("Error: can not oper %s file.\n", argv[1]);
        return 2;
    }
    else
    {
        return 0;
    }

    //initialize variables
    int file_index = 0;
    FILE *outfile;
    char jpeg_name[8];
    const int BLOCK_SIZE = 512;

    //buffer for reading data
    BYTE buf[BLOCK_SIZE];

    //go though card file untill there aren't any blocks left
    while (fread(buf, BLOCK_SIZE, 1, infile) == 1)
    {
        //check for begining of a jpeg image
        if (buf[0] == 0xff && buf[1] == 0xd8 && buf[2] == 0xff && (buf[3] & 0xf0) == 0xe0)
        {
            if (file_index > 0)
            {
                fclose(outfile);
            }
            //close opened image unless it's the first
            if (file_index == 0)
            {
                sprintf(jpeg_name, "%03i.jpg", file_index);
                outfile = fopen(jpeg_name, "w");
                file_index++;
            }
        }
        else if (file_index > 0)
        {
            fwrite(&buf, BLOCK_SIZE, 1, outfile);
        }
    }

    //close all opened files
    fclose(infile);
    fclose(outfile);

    return 0;
}
