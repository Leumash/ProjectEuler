#!/usr/bin/python

from fractions import gcd

def getNumerator(partialDenominators):
    numerator = 1
    denominator = 0
    for partial in reversed(partialDenominators):
        numerator, denominator = denominator, numerator
        numerator = denominator * partial + numerator
        GCD = gcd(numerator, denominator)
        numerator /= GCD
        denominator /= GCD
    return numerator

def getPartialDenominatorsOfE(n):
    partialDenominators = [2]
    for i in range(2,n+1):
        partialDenominators.append(1 if i % 3 else i / 3 * 2)
    return partialDenominators

def sumOfDigits(n):
    sum = 0
    while n:
        sum += n % 10
        n /= 10
    return sum

def getSumOfDigitsInNumerator(n):
    partialDenominators = getPartialDenominatorsOfE(n)
    numerator = getNumerator(partialDenominators)
    return sumOfDigits(numerator)

print getSumOfDigitsInNumerator(100)

