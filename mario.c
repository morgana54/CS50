#include <cs50.h>
#include <stdio.h>

int get_positive_int(string prompt);

int main(void)
{
    // Taking input (with the rules defined below) from the user and setting the right loop 
    int n = get_positive_int("Height: ");

    // Ważna zależność: ilość spacji niezależnie od inputu usera jest na starcie zawsze mniejsza o 1 od tego inputu i zmniejsza się on o 1
    for (int f = 0; f < n; f++)
    {
        for (int d = n - 1; d > f; d--)
        {
            printf(" ");
        }
        for (int h = -1; h < f; h++)
        {
            printf("#");
        }
        printf("\n");
    }
}

// Defining the function which was declared at the top
int get_positive_int(string prompt)
{
    // Prompting the user for integer between 1 and 8 inclusive and making computer remember it
    int p;
    do
    {
        p = get_int("%s", prompt);
    }
    while (p > 8 || p < 1);
    return p;
}
