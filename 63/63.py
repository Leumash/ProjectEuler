#!/usr/bin/python

# Notes:
# len(str(10 ^ x)) = x + 1
# Thus only bases < 10 are viable

nDigitPositiveIntegersThatAreAlsoNthPower = set()

for base in range(1, 10):
    for exponent in range(1, 30):
        n = base ** exponent
        if (len(str(n)) == exponent):
            nDigitPositiveIntegersThatAreAlsoNthPower.add(n)


print (len(nDigitPositiveIntegersThatAreAlsoNthPower))

