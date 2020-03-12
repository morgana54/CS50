#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // Checking if the number of command-line arguments equals 2
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Checking if each character in the argv[1] string is a decimal (0-9) (isdigit returns 0 if argument is not a decimal)
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isdigit(argv[1][i]) == 0 )
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    
    // Storing converted argv[1] in the new variable key
    int key = atoi(argv[1]);

    
    string plaintext = get_string("plaintext: ");
    
    // Shifting only alphabetical characters of plaintext by value of key and printing it
    // Substracting and adding of 97 and 65 changes temporarily changes plaintext ASCII index to 0-25
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (islower(plaintext[i]) != 0)
        {
            plaintext[i] = plaintext[i] - 97;
            plaintext[i] = (plaintext[i] + key) % 26;
            plaintext[i] = plaintext[i] + 97;
        }
        else if(isupper(plaintext[i]) != 0)
        {
            plaintext[i] = plaintext[i] - 65;
            plaintext[i] = (plaintext[i] + key) % 26;
            plaintext[i] = plaintext[i] + 65;
        }
    }
    printf("ciphertext: %s\n", plaintext);

    return 0;

}