/*
The fraction 49/98 is a curious fraction, as an inexperienced mathematician in attempting to simplify it may incorrectly believe that 49/98 = 4/8, which is correct, is obtained by cancelling the 9s.

We shall consider fractions like, 30/50 = 3/5, to be trivial examples.

There are exactly four non-trivial examples of this type of fraction, less than one in value, and containing two digits in the numerator and denominator.

If the product of these four fractions is given in its lowest common terms, find the value of the denominator.
*/

/*
Fraction: ab/cd

a != 0
b != 0
c != 0
d != 0

ab < cd

a < c


*/

#include <iostream>

using namespace std;

int GetGCD(int a, int b)
{
    return b == 0 ? a : GetGCD(b, a % b);
}

bool HasCommonDigit(int numerator, int denominator)
{
    bool seen[] = { false, false, false, false, false, false, false, false, false, false };

    seen[numerator % 10] = true;
    seen[numerator / 10] = true;

    return seen[denominator / 10] == true || seen[denominator % 10] == true;
}

int GetCommonDigit(int a, int b)
{
    if (a % 10 == b % 10)
    {
        return a % 10;
    }
    else if (a / 10 == b / 10)
    {
        return a / 10;
    }
    else if (a / 10 == b % 10)
    {
        return a / 10;
    }
    else if (a % 10 == b / 10)
    {
        return a % 10;
    }

    cout << "What happened?" << endl;
}

int RemoveDigit(int n, int toRemove)
{
    if (n % 10 == toRemove)
    {
        n /= 10;
    }
    else
    {
        n = n % 10;
    }

    return n;
}

bool IsDigitCancellingFraction(int numerator, int denominator)
{
    if (numerator % 10 == 0 || denominator % 10 == 0)
    {
        return false;
    }

    if (!HasCommonDigit(numerator, denominator))
    {
        return false;
    }

    int commonDigit = GetCommonDigit(numerator, denominator);
    int numeratorPrime = RemoveDigit(numerator, commonDigit);
    int denominatorPrime = RemoveDigit(denominator, commonDigit);
    int gcd = GetGCD(numerator, denominator);
    int gcdPrime = GetGCD(numeratorPrime, denominatorPrime);

    return numerator / gcd == numeratorPrime / gcdPrime && denominator / gcd == denominatorPrime / gcdPrime;
}

int GetAnswer()
{
    int top = 1;

    int bottom = 1;

    for (int numerator = 10; numerator < 99; ++numerator)
    {
        for (int denominator = numerator + 1; denominator < 100; ++denominator)
        {
            if (IsDigitCancellingFraction(numerator, denominator))
            {
                top *= numerator;
                bottom  *= denominator;
            }
        }
    }

    int gcd = GetGCD(top, bottom);

    return bottom / gcd;
}

int main()
{
    cout << GetAnswer() << endl;

    return 0;
}

