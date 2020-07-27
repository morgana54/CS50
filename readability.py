from cs50 import get_string

def countLetters(text):

    number = 0

    # Lower each character to have shorter condition
    txt = text.lower()

    for i in range(len(txt)):
        if (txt[i] >= 'a' and txt[i] <= 'z'):
            number += 1

    return number


# ANALIZE IT CAREFULLY ONCE AGAIN + opisac dla siebie lepiej while loop
def countWords(text):
    number = 0
    i = 0 
    
    while i < len(text):
        number += 1

        # iterate through word until space or end of string
        # while not executes while expression between the parentheses is FALSE (so both have to be false for loop to go through)
        while not (i == len(text) or text[i] == ' '):
            i += 1

        # iterate through space to the next char
        i += 1

    return number

def countSentences(text):

    number = 0
    
    for i in range(len(text)):
        if text[i] == '.' or text[i] == '!' or text[i] == '?':
            number += 1
    
    return number




usertext = get_string("Text: ")

letters = countLetters(usertext);
words = countWords(usertext);
sentences = countSentences(usertext);

L = float(100 * letters/words)
S = float(100 * sentences / words)

index = round(float(0.0588 * L - 0.296 * S - 15.8))
if index >= 1 and index <= 15:
    print(f"Grade {index}")
elif index < 1:
    print("Before Grade 1")
elif index >= 16:
    print ("Grade 16+")


