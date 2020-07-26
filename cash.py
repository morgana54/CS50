from cs50 import get_float

while True:
    change = get_float("Change owed: ")
    if change > 0:
        break

cents = round(change*100)

a, b, c, d = 0, 0, 0, 0

while cents >= 25:
    cents -= 25
    a += 1
    
while cents >= 10:
    cents -= 10
    b += 1

while cents >= 5:
    cents -= 5
    b += 1
    
while cents >= 1:
    cents -= 1
    b += 1
    
coins = a + b + c + d

print (f"I have {coins} coin(s)")