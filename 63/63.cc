/*
The 5-digit number, 16807=7^5, is also a fifth power. Similarly, the 9-digit number, 134217728=8^9, is a ninth power.

How many n-digit positive integers exist which are also an nth power?
*/

#include <iostream>
#include <unordered_set>
#include <cmath>

using namespace std;

int GetNumberOfDigits(int n)
{
    return to_string(n).size();
}

int GetCountOfNDigitPositiveIntegersWhichAreAlsoNthPower()
{
    int count = 0;
    int baseLimit = 10;     // Limit because len(10 ^ x) == x + 1
    int exponentLimit = 25;

    int n, m;

    for (int base = 1; base < baseLimit; ++base)
    {
        for (int exponent = 1; exponent < exponentLimit; ++exponent)
        {
            if ((int)(exponent * log10(base)) + 1 == exponent)
            {
                ++count;
            }
        }
    }

    return count;
}

int main()
{
    cout << GetCountOfNDigitPositiveIntegersWhichAreAlsoNthPower() << endl;
    return 0;
}

