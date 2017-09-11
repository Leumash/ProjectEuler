#!/usr/bin/python

def getUsableFiveDigitNumbers():
    l = []
    for i in range(0, 100000):
        squared = i * i
        N = list(str(squared))
        if len(N) >= 5 and N[-1] == '9' and N[-3] == '8' and N[-5] == '7':
            l.append(str(i).zfill(5))
    return l

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

def getConcealedSquare():
    suffixes = getUsableFiveDigitNumbers()
    i = 1000
    while True:
        for suffix in suffixes:
            num = str(i) + suffix
            if doesFitForm(int(num)):
                return num + '0'
        i +=1

print getConcealedSquare()

