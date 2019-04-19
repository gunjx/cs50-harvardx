#include <stdio.h>

// Typical blocksize of FAT system
#define FATSIZE 512

int main(int argc, char *argv[])
{
    // Check for correct number of arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover infile\n");
        return 1;
    }

    // Save infile name
    char *infile = argv[1];

    // Open infile
    FILE *inptr = fopen(infile, "r");
    if (!inptr)
    {
        fprintf(stderr, "Error: Could not open file %s\n", infile);
        return 2;
    }

    // Read file to stack memory
    unsigned char buffer[FATSIZE];

    // Allocate memory for jpeg filename
    char filename[9] = {0};

    // Remember jpeg file count
    int count = 0;

    // Initialize jpeg file pointer
    FILE *img = NULL;

    // Read file to buffer until EOF
    while (fread(buffer, FATSIZE, 1, inptr) == 1)
    {
        // Check for jpeg signature
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // Close jpeg file before creating new one
            if (img)
            {
                fclose(img);
            }

            // Name jpeg file, increment file count
            sprintf(filename, "%03i.jpg", count);
            count++;

            // Create jpeg file
            img = fopen(filename, "w");
            if (!img)
            {
                fclose(inptr);
                fprintf(stderr, "Error: Could create file %s\n", filename);
                return 5;
            }
        }
        // Write blocks to jpeg file
        if (img)
        {
            fwrite(buffer, FATSIZE, 1, img);
        }
    }

    // Close files
    fclose(inptr);
    fclose(img);
    return 0;
}
