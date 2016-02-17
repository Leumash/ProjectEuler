#!/usr/bin/python

def GetDigitalSum(n):
    sum = 0
    while (n):
        sum += n % 10
        n //= 10
    return sum

max = 0;

for base in range(1,100):
    for exponent in range(1,100):
        total = base ** exponent
        sum = GetDigitalSum(total)
        if (sum > max):
            max = sum

print (max)

