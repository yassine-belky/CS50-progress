#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

const char *WAV_FORMAT = "WAVE";

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage : %s input_file.wav output_file.wav\n", argv[0]);
        return 1;
    }

    // Open input file for reading
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        printf("Error when attempted to read file '%s'\n", argv[1]);
        return 1;
    }

    // Read header
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, input_file);

    // Use check_format to ensure WAV format
    if (!check_format(header))
    {
        printf("Unsupported file format\n");
        return 1;
    }

    // Open output file for writing
    FILE *output_file = fopen(argv[2], "w");
    if (output_file == NULL)
    {
        printf("Error when attempted to read file '%s'\n", argv[2]);
        return 1;
    }

    // Write header to file
    fwrite(&header, sizeof(WAVHEADER), 1, output_file);

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(header);

    // Write reversed audio to file
    BYTE *buffer = malloc(sizeof(BYTE) * block_size);
    long end_of_header_pos = ftell(input_file);
    fseek(input_file, -block_size, SEEK_END);
    while (ftell(input_file) != end_of_header_pos)
    {
        fread(buffer, sizeof(BYTE), block_size, input_file);
        fwrite(buffer, sizeof(BYTE), block_size, output_file);
        fseek(input_file, -2 * block_size, SEEK_CUR);
    }

    free(buffer);
    fclose(input_file);
    fclose(output_file);
}

int check_format(WAVHEADER header)
{
    char *format = (char *)header.format;
    if (strstr(format, WAV_FORMAT) != NULL)
    {
        return 1;
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    return (int)header.numChannels * (int)header.bitsPerSample / 8;
}