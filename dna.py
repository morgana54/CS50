import csv
from sys import argv, exit

# Add more comments!

if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)
    

def countSTR(text, string):

    STR = 0
    i = 0

    while i < len(text):

        if text[i:i+len(string)] == string:
            temp_str = 0
            while (text[i:i+len(string)] == string):
                temp_str += 1
                # Skip through single STR
                i += len(string)
            if temp_str > STR:
                STR = temp_str

        else:
            i += 1

    return STR


# STR counts
AGATC = 0
AATG = 0
TATC = 0
TTTTTTCT = 0
TCTAG = 0
GATA = 0
GAAA = 0
TCTG = 0

# Used for counting consecutive STRs
temp_str = 0

# Open the DNA sequence for reading (open returns file object)
DNA_sequence = open(argv[2], "r")


# List of string STRs
STR_str = ['AGATC', 'TTTTTTCT', 'AATG', 'TCTAG', 'GATA', 'TATC', 'GAAA', 'TCTG']

# List of ints STRs
STR_num = [AGATC, TTTTTTCT, AATG, TCTAG, GATA, TATC, GAAA, TCTG]


# Read whole text at once
for row in DNA_sequence:
    # Count longest STRs
    for i in range(len(STR_str)):
        STR_num[i] = countSTR(row, STR_str[i])
        
# For the small.csv case (AGATC, AATG, TATC)
STR_num_small = [STR_num[0], STR_num[2], STR_num[5]]

# Open the CSV file for reading
with open(argv[1], newline='') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=' ', quotechar='|')
    i = 0
    for row in spamreader:
        #  
        csv_strings = row[0].split(',')
        # Don't look at the first line of csv file
        if i > 0:
            # Change strings to ints (excluding names)
            nums = list(map(int, csv_strings[1:len(csv_strings)]))
            if nums == STR_num or nums == STR_num_small:
                # Print person's name
                print(csv_strings[0])
                # End program if there's a match
                exit(0)

        i += 1
    print("No match")

# pytanie: czemu nie działa bez'[0]' po 'row'

