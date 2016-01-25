#!/usr/bin/python

def GetSum(n):
    total = 2 ** n
    sum = 0

    while (total > 0):
        sum += total % 10
        total //= 10
    return sum

print (GetSum(1000))

