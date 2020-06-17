#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("correct usage: ./recover filename\n");
        return 1;
    }

    // open memory card and 
    FILE *recovered = fopen(argv[1], "r");
    if (recovered == NULL)
    {
        printf("No file found\n");
        return 2;
    }

    // declaring a pointer to the memory (heap)
    // it will temporarily store the current data that is being read by fread function
    BYTE *buffer = malloc(BLOCK_SIZE);

    // counting JPEGs to name each one correctly
    // it also allows you (below) to say if you've already found the first JPEG
    int jpeg_count = 0;

    // 8 because your string used to name the seperate images will have 8 chars: "xxx.jpg'\0'"
    // *NULL character counts as one
    char initial_filename[8];

    // declaring new file for recovering consecutive JPEGs
    FILE *new_JPEG;

    // repeat until the end of the file
    // feof returns 1 when recovered points to the end of the file and 0 when it doesn't
    while (fread(buffer, BLOCK_SIZE, 1, recovered))
    {
        // start writing when you encounter JPEG header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // close previous JPEG file so next one can be opened
            if (jpeg_count != 0)
            {
                fclose(new_JPEG);
            }
            
            // renaming current file
            sprintf(initial_filename, "%03i.jpg", jpeg_count);
            jpeg_count++;

            // opening above created file
            // *you can't open a file that has been aleady opened (that recovered points to)
            new_JPEG = fopen(initial_filename, "w");
            if (new_JPEG == NULL)
            {
                return 1;
            }

            // write data until meeting the next header
            fwrite(buffer, BLOCK_SIZE, 1, new_JPEG);
        }
        // writing every 512 BYTE chunks that are not JPEG headers
        else if (jpeg_count != 0)
        {
            // continue writing the current image
            fwrite(buffer, BLOCK_SIZE, 1, new_JPEG);
        }
    }
    fclose(new_JPEG);
    fclose(recovered);
    free(buffer);
    return 0;
}