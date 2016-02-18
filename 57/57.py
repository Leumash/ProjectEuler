#!/usr/bin/python

count=0;

def GetGCD(a,b):
    while (b != 0):
        r = a % b
        a = b
        b = r
    return a

for expansion in range(0,1000):
    num=1
    denom=2;
    for i in range(0, expansion):
        num += denom*2;
        num, denom = denom, num
    num += denom
    if (len(str(num)) > len(str(denom))):
        count += 1

print (count)
