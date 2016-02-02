/*
The number 3797 has an interesting property. Being prime itself, it is possible to continuously remove digits from left to right, and remain prime at each stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.

Find the sum of the only eleven primes that are both truncatable from left to right and right to left.

NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<bool> GetPrimes(int size)
{
    if (size == 0)
    {
        size = 10;
    }

    vector<bool> primes(size, true);

    primes[0] = false;
    primes[1] = false;

    for (int i=0; i<primes.size(); ++i)
    {
        if (primes[i] == true)
        {
            for (int j=2; j*i < primes.size(); ++j)
            {
                primes[j*i] = false;
            }
        }
    }

    return primes;
}

int GetNextPrime(int prime, vector<bool> &primes)
{
    int searchPos = prime + 1;

    while (true)
    {
        while (searchPos >= primes.size())
        {
            primes = GetPrimes(primes.size() * 10);
        }

        if (primes[searchPos] == true)
        {
            return searchPos;
        }

        ++searchPos;
    }
}

bool IsTruncatablePrime(int prime, const vector<bool> &primes)
{
    int temp = prime;

    while (temp)
    {
        if (primes[temp] == false)
        {
            return false;
        }

        temp /= 10;
    }

    int digits = floor(log10(prime)) + 1;
    temp = prime;

    while (digits)
    {
        if (primes[temp] == false)
        {
            return false;
        }

        temp %= (int) pow(10,digits - 1);

        --digits;
    }

    return true;
}

int GetSumOfTruncatablePrimes()
{
    int sum = 0;
    int totalTruncatablePrimes = 11;
    int prime = 7;
    vector<bool> primes;

    prime = GetNextPrime(prime, primes);

    for (int found=0; found<totalTruncatablePrimes; prime = GetNextPrime(prime, primes))
    {
        if (IsTruncatablePrime(prime, primes))
        {
            sum += prime;
            ++found;
        }
    }

    return sum;
}

int main()
{
    cout << GetSumOfTruncatablePrimes() << endl;

    return 0;
}

