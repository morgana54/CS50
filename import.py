# Import data from a CSV speadsheet to a database
from cs50 import SQL
import csv
from sys import argv, exit


if len(argv) != 2:
    print("Usage: python import.py characters.csv")
    exit(1)

# Give access to database (students) by a variable db
db = SQL("sqlite:///students.db")

# Read command-line argument
with open(argv[1], 'r') as file:

    reader = csv.DictReader(file, delimiter=",")

    for row in reader:

        # Count spaces in names
        spaces = row['name'].count(' ')
        
        # If there is no middle name assign 'None'
        if spaces == 2:
            first = (row['name'].split()[0])
            middle = (row['name'].split()[1])
            last = (row['name'].split()[2])
        else:
            first = (row['name'].split()[0])
            middle = None
            last = (row['name'].split()[1])
      
      
        # Insert values into students database  
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle, last, row['house'], row['birth'])
