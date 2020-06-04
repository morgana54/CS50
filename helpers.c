#include "helpers.h"
#include "math.h"
#include "stdlib.h"

// w helpers.h jest bmp.h, więc mogę używać stworzonych tam structów

// every pixel is just a struct that has different values of rgbtRed, Green albo Blue
// np. image[2][3].rgbtRed = 0; (jeśli wszystkie na zero to czarny kolor)

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // all colours must have equal value to make a grayfilter pixel
            int gray = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtBlue = gray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // all colours must have a specified sepia formula
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if(sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if(sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if(sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])

{
    for (int i = 0; i < height; i++)
    {
        // if odd number of horizontal pixels (width) - don't switch the middle one
        // if even number - switch every pixel
        // integer divided by two always rounds down, so if we have odd number, the middle will stay the same
        // this algorithm assigns new values successively from both sides of the row! (and stops in the middle, so no value will overwrite)
        for (int j = 0; j < (width/2); j++)
        {
            int tempRed = image[i][j].rgbtRed;
            int tempGreen = image[i][j].rgbtGreen;
            int tempBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width-j-1].rgbtRed;
            image[i][j].rgbtGreen= image[i][width-j-1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width-j-1].rgbtBlue;

            image[i][width-j-1].rgbtRed = tempRed;
            image[i][width-j-1].rgbtGreen= tempGreen;
            image[i][width-j-1].rgbtBlue = tempBlue;
        }
    }
    return;
}

// Blur image - ABY TO IDEALNIE ZROZUMIEĆ musisz mieć to narysowane na kartce
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // 3 bytes because that is the size of RGBTRIPLE struct type
    // int *tempArray = malloc(3 * height * width);
    
    // you can use this later if you want  roundAllExisting({{i, j - 1}}, image, ) {
    // if(> 0 && > length)

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // case #1: count every pixel around to our sum (so then divide by 9)
            if ((i-1) >= 0 && (j-1) >= 0 && (j+1) <= (width-1) && (i+1) <= (height-1))
            {
                int averageRed = round((image[i][j].rgbtRed + image[i-1][j-1].rgbtRed + image[i][j-1].rgbtRed + image[i-1][j].rgbtRed + 
                                        image[i+1][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j+1].rgbtRed + image[i+1][j-1].rgbtRed + 
                                        image[i-1][j+1].rgbtRed) / 9);
                int averageGreen = round((image[i][j].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i][j-1].rgbtGreen + image[i-1][j].rgbtGreen + 
                                        image[i+1][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen + 
                                        image[i-1][j+1].rgbtGreen) / 9);
                int averageBlue = round((image[i][j].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i][j-1].rgbtBlue + image[i-1][j].rgbtBlue + 
                                        image[i+1][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue + 
                                        image[i-1][j+1].rgbtBlue) / 9);

                image[i][j].rgbtRed = averageRed;
                image[i][j].rgbtGreen = averageGreen;
                image[i][j].rgbtBlue = averageBlue;
            }

             // case #2: don't count 5 pixels at the top left corner
            else if ((i-1) < 0 && (j-1) < 0)
            {
                int averageRed = round((image[i][j].rgbtRed + image[i+1][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j+1].rgbtRed) / 4);
                int averageGreen = round((image[i][j].rgbtGreen + image[i+1][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j+1].rgbtGreen) / 4);
                int averageBlue = round((image[i][j].rgbtBlue + image[i+1][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j+1].rgbtBlue) / 4);

                image[i][j].rgbtRed = averageRed;
                image[i][j].rgbtGreen = averageGreen;
                image[i][j].rgbtBlue = averageBlue;
            }
            // case #3: don't count 5 pixels at the top right corner
            else if ((i-1) < 0 && (j+1) > (width-1))
            {
                int averageRed = round((image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j-1].rgbtRed) / 4);
                int averageGreen = round((image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j-1].rgbtGreen) / 4);
                int averageBlue = round((image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j-1].rgbtBlue) / 4);

                image[i][j].rgbtRed = averageRed;
                image[i][j].rgbtGreen = averageGreen;
                image[i][j].rgbtBlue = averageBlue;
            }
            // case #4: don't count 5 pixels at the bottom left corner
            else if ((i+1) > (height-1) && (j-1) < 0)
            {
                int averageRed = round((image[i][j].rgbtRed + image[i-1][j].rgbtRed + image[i][j+1].rgbtRed + image[i-1][j+1].rgbtRed) / 4);
                int averageGreen = round((image[i][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i-1][j+1].rgbtGreen) / 4);
                int averageBlue = round((image[i][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i-1][j+1].rgbtBlue) / 4);

                image[i][j].rgbtRed = averageRed;
                image[i][j].rgbtGreen = averageGreen;
                image[i][j].rgbtBlue = averageBlue;
            }
            // case #5: don't count 5 pixels at the bottom right corner
            else if ((i+1) > (height-1) && (j+1) > (width-1))
            {
                int averageRed = round((image[i][j].rgbtRed + image[i-1][j-1].rgbtRed + image[i][j-1].rgbtRed + image[i-1][j].rgbtRed) / 4);
                int averageGreen = round((image[i][j].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i][j-1].rgbtGreen + image[i-1][j].rgbtGreen) / 4);
                int averageBlue = round((image[i][j].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i][j-1].rgbtBlue + image[i-1][j].rgbtBlue) / 4);

                image[i][j].rgbtRed = averageRed;
                image[i][j].rgbtGreen = averageGreen;
                image[i][j].rgbtBlue = averageBlue;
            }
            // case #6: don't count 3 pixels above (so divide by 6); it is enough if we know that only upper edge is not in the image
            else if ((i-1) < 0)
            {
                int averageRed = round((image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i][j+1].rgbtRed + 
                                        image[i+1][j+1].rgbtRed + image[i+1][j-1].rgbtRed) / 6);
                int averageGreen = round((image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i][j+1].rgbtGreen + 
                                        image[i+1][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen) / 6);
                int averageBlue = round((image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i][j+1].rgbtBlue + 
                                        image[i+1][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue) / 6);

                image[i][j].rgbtRed = averageRed;
                image[i][j].rgbtGreen = averageGreen;
                image[i][j].rgbtBlue = averageBlue;
            }
            //   case #7: don't count 3 pixels under
            else if ((i+1) > (height-1))
            {
                int averageRed = round((image[i][j].rgbtRed + image[i-1][j-1].rgbtRed + image[i][j-1].rgbtRed + image[i-1][j].rgbtRed + 
                                        image[i][j+1].rgbtRed + image[i-1][j+1].rgbtRed) / 6);
                int averageGreen = round((image[i][j].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i][j-1].rgbtGreen + image[i-1][j].rgbtGreen + 
                                        image[i][j+1].rgbtGreen + image[i-1][j+1].rgbtGreen) / 6);
                int averageBlue = round((image[i][j].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i][j-1].rgbtBlue + image[i-1][j].rgbtBlue + 
                                        image[i][j+1].rgbtBlue + image[i-1][j+1].rgbtBlue) / 6);
                                        
                image[i][j].rgbtRed = averageRed;
                image[i][j].rgbtGreen = averageGreen;
                image[i][j].rgbtBlue = averageBlue;
            }
             // case #8: don't count 3 pixels to the right
            else if ((j+1) > (width-1))
            {
                int averageRed = round((image[i][j].rgbtRed + image[i-1][j-1].rgbtRed + image[i][j-1].rgbtRed + image[i-1][j].rgbtRed + 
                                        image[i+1][j].rgbtRed + image[i+1][j-1].rgbtRed) / 6);
                int averageGreen = round((image[i][j].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i][j-1].rgbtGreen + image[i-1][j].rgbtGreen + 
                                        image[i+1][j].rgbtGreen + image[i+1][j-1].rgbtGreen) / 6);
                int averageBlue = round((image[i][j].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i][j-1].rgbtBlue + image[i-1][j].rgbtBlue + 
                                        image[i+1][j].rgbtBlue + image[i+1][j-1].rgbtBlue) / 6);

                image[i][j].rgbtRed = averageRed;
                image[i][j].rgbtGreen = averageGreen;
                image[i][j].rgbtBlue = averageBlue;
            }
             // case #9: don't count 3 pixels to the left
            else if ((j-1) < 0)
            {
                int averageRed = round((image[i][j].rgbtRed + image[i-1][j].rgbtRed + image[i+1][j].rgbtRed + image[i][j+1].rgbtRed + 
                                        image[i+1][j+1].rgbtRed + image[i-1][j+1].rgbtRed) / 9);
                int averageGreen = round((image[i][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i+1][j].rgbtGreen + image[i][j+1].rgbtGreen + 
                                        image[i+1][j+1].rgbtGreen + image[i-1][j+1].rgbtGreen) / 9);
                int averageBlue = round((image[i][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i+1][j].rgbtBlue + image[i][j+1].rgbtBlue + 
                                        image[i+1][j+1].rgbtBlue + image[i-1][j+1].rgbtBlue) / 9);

                image[i][j].rgbtRed = averageRed;
                image[i][j].rgbtGreen = averageGreen;
                image[i][j].rgbtBlue = averageBlue;
            }
        }

    }
    // free(tempArray);

    // na koniec użyj valgrinda i poogarniaj czy masz spoko kodzik

    return;
}






