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
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, inptr);

    // Use check_format to ensure WAV format
    // TODO #4
    if ((check_format(header)) == 0)
        return 1;

    // Open output file for writing
    // TODO #5
    FILE *outptr = fopen(argv[2], "w");
    if (outptr == NULL)
    {
        printf("Could not open %s.\n", argv[2]);
        return 1;
    }
    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(header), 1, outptr);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(header);

    // Write reversed audio to file
    // TODO #8
    long p1 = ftell(inptr);
    fseek(inptr, -1 * block_size, SEEK_END);
    int buffer[block_size];

    while (ftell(inptr) >= p1)
    {
        fread(&buffer, block_size, 1, inptr);
        fwrite(&buffer, block_size, 1, outptr);
        fseek(inptr, -2 * block_size, SEEK_CUR);
    }
    fclose(inptr);
    fclose(outptr);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
        return 1;
    else
        return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int bs = header.numChannels * header.bitsPerSample / 8;
    return bs;
}