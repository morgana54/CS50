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

    // open memory card
    FILE *recovered = fopen(argv[1], "r");
    if (recovered == NULL)
    {
        printf("No file found\n");
        return 2;
    }

    // declaring a pointer to the memory (heap)
    // it will store the current data that is being read by fread function
    BYTE *buffer = malloc(BLOCK_SIZE);
    
    // counting JPEGs to name each one correctly 
    int jpeg_count = 0;
    
    // 8 because your string used to name the seperate images will have 8 chars: "xxx.jpg'\0'"
    // *NULL character counts as one
    char temp_filename[8]; 
    
    FILE *new_JPEG = NULL;
    
    // repeat until the end of the file
    // feof returns 1 when recovered points to the end of the file and 0 when it's not
    while (feof(recovered) == 0)
    // LUB jak zwrócona wartość jest większa lub równa 256
    {
        fread(buffer, BLOCK_SIZE, 1, recovered);

        // start writing when you encounter JPEG header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // CREATE a new file do którego zapiszesz tego JPEGA
            if (jpeg_count == 0)
            {
                sprintf(temp_filename, "%03i.jpg", jpeg_count);
                jpeg_count++; 
                
                // you can't open a file that has been aleady opened (that recovered points to)
                new_JPEG = fopen(temp_filename, "w");
                if (new_JPEG == NULL)
                {
                    return 3;
                }
            
                // write data until meeting the next header
                fwrite(buffer, BLOCK_SIZE, 1, new_JPEG);
                
            }
            else
            {
                sprintf(temp_filename, "%03i.jpg", jpeg_count);
                jpeg_count++; 
                
                new_JPEG = fopen(temp_filename, "w");
                if (new_JPEG == NULL)
                {
                    return 3;
                }
            
                fwrite(buffer, BLOCK_SIZE, 1, new_JPEG);
            }
            fclose(new_JPEG);
            
        }
    }
    free(buffer);
    return 0;
}


// JPEGs are stored back to back
// iterate through 512 byte chunks of memory
// if the header of JPEG start writing
// write until meeting the next JPEG header
// then: close the old one and start writing to a new JPEG file
// repeat this process until you reach the end of the memory card
