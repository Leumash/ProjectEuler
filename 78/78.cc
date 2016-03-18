/*

Let p(n) represent the number of different ways in which n coins can be separated into piles. For example, five coins can be separated into piles in exactly seven different ways, so p(5)=7.

             OOOOO

          OOOO   O

           OOO  OO

       OOO   O   O

        OO  OO   O

     OO  O   O   O

  O  O   O   O   O

Find the least value of n for which p(n) is divisible by one million.

*/

/*

How many unique ways to fit N indistinguishable balls into K indistinguishable boxes where each box contains at least 1 ball?
p(n) = Summation of above where 1 <= m <= n

https://en.wikipedia.org/wiki/Partition_%28number_theory%29

In number theory, the partition function p(n) represents the number of possible partitions of a natural number n, which is to say the number of distinct ways of representing n as a sum of natural numbers (with order irrelevant). By convention p(0) = 1, p(n) = 0 for n negative.

*/

#include <iostream>
#include <map>
#include <utility>

#define SIZE_LIMIT 10000000ll

using namespace std;

bool IsDivisible(int n, int divisor)
{
    return n % divisor == 0;
}

long long GetPn(long long n, long long arr[])
{
    long long total = 0;
    long long multiplier = 1;

    for (long long k=1; k<=n; ++k)
    {
        long long inner1 = n - (k * (3 * k - 1)) / 2;
        long long inner2 = n - (k * (3 * k + 1)) / 2;
        if (inner1 >= 0)
        {
            total += multiplier * arr[inner1];
        }

        if (inner2 >= 0)
        {
            total += multiplier * arr[inner2];
        }

        if (inner1 < 0)
        {
            break;
        }

        multiplier *= -1;
        total %= SIZE_LIMIT;
    }

    arr[n] = total % SIZE_LIMIT;

    return arr[n];
}

int GetNForWhichPnIsDivisibleBy(int divisor)
{
    long long arr[100000];

    arr[0] = 1;

    for (long long n=1; ; ++n)
    {
        long long Pn = GetPn(n, arr);

        if (IsDivisible(Pn, divisor))
        {
            return n;
        }
    }
}

int main()
{
    cout << GetNForWhichPnIsDivisibleBy(1000000) << endl;
    return 0;
}

