#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Declaring the function which counts the letters (body of the function is below the main)
int count_letters(string txt);
int count_words(string txt);
int count_sent(string txt);

int main(void)
{
    // Function first takes string from user, stores it in "usertxt" and then takes it to the function count_letters
    // which returns the number of letters and stores it in a variable "letters"
    string usertxt = get_string("Text: ");
    
    int letters = count_letters(usertxt);
    int words = count_words(usertxt);
    int sent = count_sent(usertxt);
  
    float l = 100 * letters / words;
    float s = 100 * sent / words;
  
    float index = 0.0588 * l - 0.296 * s - 15.8;
 
    float ind = round(index);
  
  
    if(ind >= 1 && ind <= 15)
    {
        printf("Grade %.0f\n", ind);
    }
    else if (ind < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (ind >= 16)
    {
        printf("Grade 16+\n");
    }
}

// Defining the function
int count_letters(string txt)
{
    int sum = 0;

    // Loop that checks every character in a text given by the user (which is actually an array of chars) if it is a letter
    for (int i = 0; txt[i] != '\0'; i++)
    {
      if ((txt[i] >= 'a' && txt[i] <= 'z') || (txt[i] >= 'A' && txt[i] <= 'Z'))
      {
        sum++;
      }
    }

    return sum;
}

// Defining the function
int count_words(string txt)
{
    int sum = 0;

    // If a "i"th character is a non-space, add one word, THEN: increment the number of chars in array until you encounter space
    // By doing this in a loop you get what you want babyyyy
    for (int i = 0; txt[i] != '\0'; i++)
    {
      if (txt[i] != ' ')
      {
        sum++;

        for (int n = 0; txt[i] != ' '; n++)
        {
            if (txt[i] == '\0')
            {
                break;
            }
            i++;
        }
      }
    }
    return sum;

}

// Defining the function
int count_sent(string txt)
{
    int sum = 0;

    // Loop for sentences, only three conditions needed
    for (int i = 0; txt[i] != '\0'; i++)
    {
      if (txt[i] == '.' || txt[i] == '!' || txt[i] == '?')
      {
        sum++;
      }
    }
    return sum;
}