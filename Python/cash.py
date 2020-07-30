from cs50 import get_float

while True:
    change = get_float("Change owed: ")
    if change > 0:
        break
change = round(change * 100)
count = 0
while change >= 25:
    change -= 25
    count += 1
while change >= 10:
    change -= 10
    count += 1
while change >= 5:
    change -= 5
    count += 1
while change >= 1:
    change -= 1
    count += 1
print(count)
