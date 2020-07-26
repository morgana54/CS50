from cs50 import get_int

height = get_int("Height: ")

while height > 8 or height < 1:
    height = get_int("Height: ")
    
for i in range(height):
    
    # Print spaces (always height - 1)
    for d in range(height-1, i, -1):
        print(" ", end="")
        
    # "i+1" because "i" equals 0 in the first loop
    for h in range(i+1):
        print("#", end="")
        
    print()
    