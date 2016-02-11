/*
The number, 1406357289, is a 0 to 9 pandigital number because it is made up of each of the digits 0 to 9 in some order, but it also has a rather interesting sub-string divisibility property.

Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way, we note the following:

d2d3d4=406 is divisible by 2
d3d4d5=063 is divisible by 3
d4d5d6=635 is divisible by 5
d5d6d7=357 is divisible by 7
d6d7d8=572 is divisible by 11
d7d8d9=728 is divisible by 13
d8d9d10=289 is divisible by 17
Find the sum of all 0 to 9 pandigital numbers with this property.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool IsDivisible(int divisor, char num[], int pos)
{
    bool toReturn;
    char temp = num[pos + 3];
    num[pos+3] = '\0';

    toReturn = (atoi(num + pos) % divisor == 0);

    num[pos+3] = temp;

    return toReturn;
}

bool IsInterestingSubStringDivisibilityProperty(char num[])
{
    int primes[] = {2,3,5,7,11,13,17};
    int numPrimes = sizeof(primes) / sizeof(int);

    for (int i=0; i<numPrimes; ++i)
    {
        if (!IsDivisible(primes[i], num, i + 1))
        {
            return false;
        }
    }

    return true;
}

long long GetSum()
{
    long long sum = 0;
    char permutation[10];

    for (int i=0; i<10; ++i)
    {
        permutation[i] = i + '0';
    }

    do
    {
        if (IsInterestingSubStringDivisibilityProperty(permutation))
        {
            sum += atoll(permutation);
        }

    } while (next_permutation(permutation, permutation + 10));

    return sum;
}

int main()
{
    cout << GetSum() << endl;

    return 0;
}

