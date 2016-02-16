/*
By replacing the 1st digit of the 2-digit number *3, it turns out that six of the nine possible values: 13, 23, 43, 53, 73, and 83, are all prime.

By replacing the 3rd and 4th digits of 56**3 with the same digit, this 5-digit number is the first example having seven primes among the ten generated numbers, yielding the family: 56003, 56113, 56333, 56443, 56663, 56773, and 56993. Consequently 56003, being the first member of this family, is the smallest prime with this property.

Find the smallest prime which, by replacing part of the number (not necessarily adjacent digits) with the same digit, is part of an eight prime value family.
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<bool> GetPrimes(int limit)
{
    vector<bool> primes(limit, true);

    primes[0] = false;
    primes[1] = false;

    for (int i=2; i<=sqrt(limit); ++i)
    {
        for (int multiplier=2; i * multiplier < limit; ++multiplier)
        {
            primes[i * multiplier] = false;
        }
    }

    return primes;
}

int GetNextPrime(int previousPrime)
{
    int index = previousPrime + 1;
    static vector<bool> primes(1, false);

    while (true)
    {
        if (index >= primes.size())
        {
            primes = GetPrimes(primes.size() * 10);
        }

        if (primes[index] == true)
        {
            return index;
        }

        ++index;
    }
}

vector<int> GetIndicies(char num[], int numberToFind)
{
    vector<int> indices;

    for (int i=0; num[i] != '\0'; ++i)
    {
        if (num[i] == (numberToFind + '0'))
        {
            indices.push_back(i);
        }
    }

    return indices;
}

bool IsPrime(int candidatePrime)
{
    static vector<bool> primes(1, false);

    if (candidatePrime >= primes.size())
    {
        int size = primes.size();

        while (size < candidatePrime)
        {
            size *= 10;
        }

        primes = GetPrimes(size);
    }

    return primes[candidatePrime];
}

bool IsPartOfEightPrimeValueFamily(int prime, int numberToCheck)
{
    char num[15];
    itoa(prime, num, 10);
    vector<int> indices = GetIndicies(num, numberToCheck);
    int count = 0;

    if (indices.size() == 0)
    {
        return false;
    }

    for (char i = num[indices[0]]; i <= '9'; ++i)
    {
        if (IsPrime(atoi(num)))
        {
            ++count;
        }

        for (int index : indices)
        {
            ++num[index];
        }
    }

    return count >= 8;
}

bool IsPartOfEightPrimeValueFamily(int prime)
{
    for (int i=0; i<10; ++i)
    {
        if (IsPartOfEightPrimeValueFamily(prime, i))
        {
            return true;
        }
    }

    return false;
}

int GetSmallestSpecialPrime()
{
    for (int prime=2; ; prime = GetNextPrime(prime))
    {
        if (IsPartOfEightPrimeValueFamily(prime))
        {
            return prime;
        }
    }
}

int main()
{
    cout << GetSmallestSpecialPrime() << endl;

    return 0;
}

