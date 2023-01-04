/* WAV files are a common file format for representing audio. WAV files store audio as a sequence of “samples”: numbers that represent the 
value of some audio signal at a particular point in time. WAV files begin with a 44-byte “header” that contains information about the file itself, 
including the size of the file, the number of samples per second, and the size of each sample. After the header, the WAV file contains a sequence of samples, 
each a single 2-byte (16-bit) integer representing the audio signal at a particular point in time.
Scaling each sample value by a given factor has the effect of changing the volume of the audio. Multiplying each sample value by 2.0, for example, 
will have the effect of doubling the volume of the origin audio. Multiplying each sample by 0.5, meanwhile, will have the effect of cutting the volume in half.

Complete the implementation of volume.c, such that it changes the volume of a sound file by a given factor.
- The program accepts three command-line arguments: input represents the name of the original audio file, output represents the name of the new audio 
file that should be generated, and factor is the amount by which the volume of the original audio file should be scaled.
For example, if factor is 2.0, then your program should double the volume of the audio file in input and save the newly generated audio file in output.
- Your program should first read the header from the input file and write the header to the output file. Recall that this header is always exactly 44 bytes long.
Note that volume.c already defines a variable for you called HEADER_SIZE, equal to the number of bytes in the header.
- Your program should then read the rest of the data from the WAV file, one 16-bit (2-byte) sample at a time. Your program should multiply each sample 
by the factor and write the new sample to the output file. You may assume that the WAV file will use 16-bit signed values as samples. 
In practice, WAV files can have varying numbers of bits per sample, but we’ll assume 16-bit samples for this lab.
- Your program, if it uses malloc, must not leak any memory. */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    //array of bytes to store the data from the WAV file header that you’ll read from the input file.
    uint8_t header[HEADER_SIZE];

    // TODO: Copy header from input file to output file
    fread(header, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);

    //buffer to store audio samples that you read from the WAV file
    int16_t buffer;

    // TODO: Read samples from input file and write updated data to output file
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
