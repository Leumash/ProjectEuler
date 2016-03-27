#!/usr/bin/python

# Notes:
# len(str(10 ^ x)) = x + 1
# Thus only bases < 10 are viable

x = set({1,5})

nDigitPositiveIntegersThatAreAlsoNthPower = set()

for base in range(1, 10):
    for exponent in range(1, 30):
        if (len(str(base ** exponent)) == exponent): nDigitPositiveIntegersThatAreAlsoNthPower.add(base ** exponent)


print (len(nDigitPositiveIntegersThatAreAlsoNthPower))

