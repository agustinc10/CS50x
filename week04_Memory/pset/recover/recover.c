#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    int BLOCK_SIZE = 512;
    uint8_t buffer[BLOCK_SIZE];

    int count = 0;

    char *filename = malloc(8 * sizeof(char));
    if (filename == NULL)
        return 1;
    FILE *img;

    while (fread(&buffer, sizeof(uint8_t), BLOCK_SIZE, inptr) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (count == 0)
            {
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                if (img == NULL)
                {
                    printf("Could not open file.\n");
                    return 1;
                }
                fwrite(&buffer, sizeof(uint8_t), BLOCK_SIZE, img);
                count++;
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                if (img == NULL)
                {
                    printf("Could not open file.\n");
                    return 1;
                }
                fwrite(&buffer, sizeof(uint8_t), BLOCK_SIZE, img);
                count++;
            }
        }
        else if (count != 0)
        {
            fwrite(&buffer, sizeof(uint8_t), BLOCK_SIZE, img);
        }
    }
    fclose(img);
    fclose(inptr);
    free(filename);
    return 0;
}