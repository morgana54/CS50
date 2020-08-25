# Produce class roster
from cs50 import SQL
import csv
from sys import argv, exit


if len(argv) != 2:
    print("Usage: python roster.py house")
    exit(1)

# Give access to database (students) by a variable db
db = SQL("sqlite:///students.db")

# Assign values to a list of dicts
if argv[1] == "Gryffindor":
    names = db.execute("SELECT first, middle, last, birth FROM students WHERE house = 'Gryffindor' ORDER BY last, first")

if argv[1] == "Slytherin":
    names = db.execute("SELECT first, middle, last, birth FROM students WHERE house = 'Slytherin' ORDER BY last, first")
    
if argv[1] == "Ravenclaw":
    names = db.execute("SELECT first, middle, last, birth FROM students WHERE house = 'Ravenclaw' ORDER BY last, first")
    
if argv[1] == "Hufflepuff":
    names = db.execute("SELECT first, middle, last, birth FROM students WHERE house = 'Hufflepuff' ORDER BY last, first")

for row in names:
    if row['middle'] == None:
        print(f"{row['first']} {row['last']}, born {row['birth']}")
    else:
        print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")