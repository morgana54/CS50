#include <cs50.h>
#include <stdio.h>

int get_positive_int(string prompt);

int main(void)   
// Your first "nest" loop yeah
{
    int h = get_positive_int("Height:"); 
// This line of code below mówi, że tyle razy wykonana zostanie jedna linijka i potem \n (jak wpiszesz dwa, to dwie linijki)
    for (int i = 0; i < h; i++)
    {
        for (int d = 7; d > i; d--)
        {
            printf(" ");                        
        }
        for (int hash = -1; hash < i; hash++)
        {
            printf("#");
        }
        printf("\n");
        
    }

}

//declaring function that I used in the first scope (loop for returning the right h)
int get_positive_int(string prompt)
{
    int n;
    do
    {
        n = get_int("%s", prompt);
    }
    while (n > 8 || n < 1);
    return n;
}

    

