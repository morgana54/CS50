#include <stdio.h>
#include <cs50.h>

int main(void)

// Prompts the user for name and then prints it with hello,
{
    string name = get_string("What is your name?\n");
    printf("hello, %s\n", name);
}
