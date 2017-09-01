#!/usr/bin/python

from math import sqrt

def isPerfectSquare(n):
    return int(sqrt(n)) ** 2 == n

def isIrrationalSquareRoot(n):
    return not isPerfectSquare(n)

def getSumOfDecimals(n):
    num = int(sqrt(n))
    target = n
    while len(str(num)) <= 102:
        target *= 100
        num *= 10
        while (num + 1) ** 2 < target:
            num += 1
        num -= 1
    sum = 0
    for i in str(num)[0:100]:
        sum += int(i)
    return sum

def getTotalSumOfDecimals(n):
    sum = 0
    for i in range(1, 100):
        if (isIrrationalSquareRoot(i)):
            sum += getSumOfDecimals(i)
    return sum

print getTotalSumOfDecimals(100)

