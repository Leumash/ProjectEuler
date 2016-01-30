#!/usr/bin/python

def DoIt(n):
    s = set()
    for a in range(2, n+1):
        for b in range(2, n+1):
            s.add(a**b)
    return len(s)

print (DoIt(100))

