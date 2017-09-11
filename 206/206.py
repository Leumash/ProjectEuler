#!/usr/bin/python

def doesFitForm(n):
    squared = n * n
    N = list(str(squared))
    return N[0] == '1' \
        and N[2] == '2' \
        and N[4] == '3' \
        and N[6] == '4' \
        and N[8] == '5' \
        and N[10] == '6' \
        and N[12] == '7' \
        and N[14] == '8' \
        and N[16] == '9'

def doIt():
    i = 100000000
    while True:
        if doesFitForm(i):
            return i * 10
        i += 1

print doIt()

