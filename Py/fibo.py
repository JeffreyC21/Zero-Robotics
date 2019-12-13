total = 0
num = 1
prevNum = 1
while num < 4000000:
    if (num % 2 == 0):
        total += num
    temp = num
    num += prevNum
    prevNum = temp

print(total)
