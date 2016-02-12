/*
Starting with 1 and spiralling anticlockwise in the following way, a square spiral with side length 7 is formed.

37 36 35 34 33 32 31
38 17 16 15 14 13 30
39 18  5  4  3 12 29
40 19  6  1  2 11 28
41 20  7  8  9 10 27
42 21 22 23 24 25 26
43 44 45 46 47 48 49

It is interesting to note that the odd squares lie along the bottom right diagonal, but what is more interesting is that 8 out of the 13 numbers lying along both diagonals are prime; that is, a ratio of 8/13 ≈ 62%.

If one complete new layer is wrapped around the spiral above, a square spiral with side length 9 will be formed. If this process is continued, what is the side length of the square spiral for which the ratio of primes along both diagonals first falls below 10%?
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool IsRatioBelowTenPercent(int top, int bottom)
{
    double ratio = top * 1.0 / bottom;

    return ratio < 0.1;

}

bool IsPrime(int num)
{
    if (num < 2 || num % 2 == 0)
    {
        return false;
    }

    for (int i=3; i<=sqrt(num); i += 2)
    {
        if (num % i == 0)
        {
            return false;
        }
    }

    return true;
}

int GetSideLengthWhereRatioOfPrimesAlongDigonalsFallsBelowTenPercent()
{
    int num = 1;
    int length = 1;
    int countOfPrimes = 0;
    int total = 1;

    while (true)
    {
        length += 2;
        int additive = length - 1;

        for (int i=0; i<4; ++i)
        {
            num += additive;

            if (IsPrime(num))
            {
                ++countOfPrimes;
            }
        }

        total += 4;

        if (IsRatioBelowTenPercent(countOfPrimes, total))
        {
            return length;
        }
    }
}

int main()
{
    cout << GetSideLengthWhereRatioOfPrimesAlongDigonalsFallsBelowTenPercent() << endl;

    return 0;
}

