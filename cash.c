#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
// Prompting user for positive float (change)   
    float ch;
    do
    {
        ch = get_float("Change owed: ");
    }
    while (ch <= 0);
    
// Converting dollars to cents so that value can be an integer from now on
    int ce = round(ch * 100);
    
// Declaring four integers that will add up at the enp and make the final number of coins used
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    
    while (ce >= 25)
    {
        ce = ce - 25;
        a++;
    }
    
    while (ce >= 10)
    {
        ce = ce - 10;
        b++;
    }
    
    while (ce >= 5)
    {
        ce = ce - 5;
        c++;
    }
    
    while (ce >= 1)
    {
        ce = ce - 1;
        d++;
    }
    
    int coins = a + b + c + d;
// Printing the final number of coins
    printf("I have %i coin(s)\n", coins);
}
