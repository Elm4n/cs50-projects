from cs50 import get_float

while True:
    cash = get_float("Change owed: ")
    if cash > 0:
        break
    else:
        continue

cent = round(cash * 100)
coins = 0
while cent > 0:
    if cent >= 25:
        cent -= 25
    elif cent >= 10:
        cent -= 10
    elif cent >= 5:
        cent -= 5
    else:
        cent -= 1

    coins +=1
print(coins)
