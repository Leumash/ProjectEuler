/*
The following iterative sequence is defined for the set of positive long longegers:

n → n/2 (n is even)
n → 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:

13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one million.
*/

#include <iostream>
#include <unordered_map>

using namespace std;

bool IsOdd(long long n)
{
    return n & 1;
}

long long GetChainForNumber(long long n, unordered_map<long long,long long> &numberToChain)
{
    if (n == 1)
    {
        numberToChain[1] = 1;
        return 1;
    }

    if (numberToChain.count(n) == 0)
    {
        int chainPrior;

        if (IsOdd(n))
        {
            chainPrior = GetChainForNumber(n * 3 + 1, numberToChain);
        }
        else
        {
            chainPrior = GetChainForNumber(n / 2, numberToChain);
        }

        numberToChain[n] = chainPrior + 1;
    }

    return numberToChain[n];
}

long long GetLargestChainUnder(long long n, const unordered_map<long long,long long> &numberToChain)
{
    long long number = 0;
    long long max = 0;

    for (unordered_map<long long,long long>::const_iterator mit = numberToChain.begin();
        mit != numberToChain.end(); ++mit)
    {
        if (mit->first < n && mit->second > max)
        {
            max = mit->second;
            number = mit->first;
        }
    }

    return number;
}

long long GetLongestChainUnder(long long n)
{
    unordered_map<long long,long long> numberToChain;

    for (int i=1; i<n; ++i)
    {
        GetChainForNumber(i, numberToChain);
    }

    return GetLargestChainUnder(n, numberToChain);
}

int main()
{
    cout << GetLongestChainUnder(1000000) << endl;

    return 0;
}

