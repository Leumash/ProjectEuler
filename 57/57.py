#!/usr/bin/python

count=0;

def swap(n,m):
    return (m,n)

def GetGCD(a,b):
    while (b != 0):
        r = a % b
        a = b
        b = r
    return a

def DigitCount(n):
    count=0
    while (n > 0):
        count +=1
        n //= 10
    return count

for expansion in range(0,1000):
    num=1
    denom=2;
    for i in range(0, expansion):
        num += denom*2;
        num, denom = swap(num, denom)
    num += denom
    gcd=GetGCD(num, denom)
    num //= gcd
    denom //= gcd
    if (DigitCount(num) > DigitCount(denom)):
        count += 1

print (count)
