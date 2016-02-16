/*
There are exactly ten ways of selecting three from five, 12345:

123, 124, 125, 134, 135, 145, 234, 235, 245, and 345

In combinatorics, we use the notation, 5C3 = 10.

In general,

nCr = n! / (r!(n−r)!) where r ≤ n, n! = n×(n−1)×...×3×2×1, and 0! = 1.

It is not until n = 23, that a value exceeds one-million: 23C10 = 1144066.

How many, not necessarily distinct, values of  nCr, for 1 ≤ n ≤ 100, are greater than one-million?
*/

#include <iostream>

using namespace std;

double factorial(int n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }

    return n * factorial(n - 1);
}

double GetCombinations(int n, int r)
{
    return factorial(n) / (factorial(r) * factorial(n-r));
}

int GetCombinationsGreaterThanMillion()
{
    int count = 0;

    for (int n=1; n<=100; ++n)
    {
        for (int r=1; r<=n; ++r)
        {
            if (GetCombinations(n,r) > 1000000)
            {
                ++count;
            }
        }
    }

    return count;
}

int main()
{
    cout << GetCombinationsGreaterThanMillion() << endl;
    return 0;
}

