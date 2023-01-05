/* Let’s write a program called called reverse that enables us to reverse a WAV file given by the user and create a new WAV file that contains 
the resulting reversed audio. For simplicity’s sake, we’ll limit the files we deal with to the WAV format. At the time the user executes the program, 
they should provide, using two command-line arguments, the name of the input file to be read and reversed, and the name of the output file they would 
like to save the resulting audio in. A successfully executed program should not output any text, and should create a WAV file with the user-specified 
name that plays the audio of the input WAV file in reverse. 

1. In the first TODO, you should ensure the program accepts two command-line arguments: the name of the input WAV file and the name of the output WAV file. 
If the program does not meet these conditions, you should print an appropriate error message and return 1, ending the program.
Hint
2. In the second TODO, you should open your input file. We’ll need to open the input file in “read-only” mode, since we’ll only read data from the input file. 
It may be wise to check that the file has been opened successfully. Otherwise, you should print an appropriate error message and return 1, exiting the program. 
3. In the third TODO, you should read the header from the input file. Recall that, in wav.h, we’ve already implemented a struct that can store a WAV file’s header. 
4. In the fourth TODO, you should complete the check_format function. check_format takes a single argument, a WAVHEADER called header, representing a struct 
containing the input file’s header. If header indicates the file is indeed a WAV file, the check_format function should return true. If not, check_format should 
return false. To check if a file is of the WAV format, we can compare the elements from the input file header to those we would expect from a WAV file. 
It suffices to show the “WAVE” marker characters are found in the format member of the WAVHEADER struct.
5. In the fifth TODO, you can now safely open the output file for writing. It would still be wise to check that the file has been opened successfully.
6. The sixth TODO tells us to write the header to the output file. The reversed WAV file will still have the same underlying file structure as the input file 
7. In the seventh TODO, you should implement the get_block_size function. get_block_size, like check_format, takes a single argument: this is a WAVHEADER called 
header, representing the struct containing the input file’s header. get_block_size should return an integer representing the block size of the given WAV file, 
in bytes. For audio, we calculate the size of each block with the following calculation: number of channels multiplied by bytes per sample.
8. The eighth and final TODO is where the actual reversing of the audio takes place. To do this, we need to read in each block of auditory data starting from 
the very end of the input file and moving backwards, simultaneously writing each block to the output file so they are written in reverse order. 
First, we should declare an array to store each block we read in. Then, it’s up to you to iterate through the input file audio data. You’ll want to be sure you 
read through all of the audio, but don’t erroneously copy any of the data from the header!
Keep in mind that after you use fread to load in a block of data, the input pointer will be pointing at the location where the read concluded. 
In other words, the input pointer may need to be moved back two block sizes after each fread, one to move back to where the fread began, and the second 
to move to the previous, unread block.
9. Finally, be sure to close any files you’ve opened!*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // TODO #3
    //WAV header struct buffer to store data that you’ll read from the input file.
    WAVHEADER wavHeader;

    // Read header into an array
    fread(&wavHeader, sizeof(WAVHEADER), 1, input);

    //calc the begining of audio data
    int header_end = ftell(input);

    // Use check_format to ensure WAV format
    // TODO #4
    int check_f = check_format(wavHeader);
    if (check_f != 1)
    {
        printf("Input is not a WAV file.\n");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&wavHeader, sizeof(WAVHEADER), 1, output);


    // Use get_block_size to calculate size of block
    // TODO #7
    int block = get_block_size(wavHeader);

    //create buffer to store first block of audio data to compare is copying is correct later
    uint8_t begining[block];
    fread(&begining, sizeof(block), 1, input);

    // Write reversed audio to file
    // TODO #8
    //buffer to store bytes from reading one block
    uint8_t buffer[block];

    // Moving pointer to end of file, with ofset of one block size
    fseek(input, -1 * block, SEEK_END);

    //initializing pointer = current pointer value
    //check if pointer has not reached the end of first block of audio data (header_end + block)
    //after executing the body moving the file pointer 2 block forward - one to move back to where the fread began,
    //and the second to move to the previous, unread block
    //because we are reading in reverse order pointer has negative sign
    for (int pointer = ftell(input); pointer != header_end + block; fseek(input, -2 * block, SEEK_CUR))
    {
        //read one block from input file and write it to the output
        fread(&buffer, sizeof(block), 1, input);
        fwrite(&buffer, sizeof(block), 1, output);
        //updating pointer value
        pointer = ftell(input);
    }

    //check if copying is correct
    //compare last read block with the first read audio block after the header

    for (int i = 0; i < block; i ++)
    {
        if (begining[i] != buffer[i])
        {
            printf("Not reading file properly.\n");
            return 1;
        }
    }

    // Close files
    fclose(input);
    fclose(output);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    //For audio, we calculate the size of each block with the following calculation: number of channels multiplied by bytes per sample.
    //One of the members of WAVHEADER is bitsPerSample. But to calculate block size, you’ll need bytes per sample (divide bitsPerSample by 8 to calc bytesPerSample)
    int block_size = header.numChannels * (header.bitsPerSample / 8);
    printf("Block %d\n", block_size);
    return block_size;
}
