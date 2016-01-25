#!/usr/bin/python
# 40! / (20! * (40-20)!)

def Factorial(n):
    if n == 1:
        return 1
    if n == 0:
        return 1
    return Factorial(n-1) * n

print (Factorial(40) / (Factorial(20) * Factorial(40-20)))

