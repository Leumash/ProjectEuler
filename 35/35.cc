/*
The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.

There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.

How many circular primes are there below one million?
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<bool> GetPrimes(int n)
{
    vector<bool> primes(n, true);

    primes[0] = false;
    primes[1] = false;

    for (int i=2; i<primes.size(); ++i)
    {
        if (primes[i] == true)
        {
            for (int notPrime = i*2; notPrime < primes.size(); notPrime += i)
            {
                primes[notPrime] = false;
            }
        }
    }

    return primes;
}

int RotateNumber(int n)
{
    int digits = floor(log10(n)) + 1;
    int ones = n % 10;

    n /= 10;

    return n + ones * pow(10, digits - 1);
}

bool IsCircularPrime(int prime, const vector<bool> &primes)
{
    int rotations = floor(log10(prime));
    int circularPrime = prime;

    for (int i=0; i<rotations; ++i)
    {
        circularPrime = RotateNumber(circularPrime);

        if (!primes[circularPrime])
        {
            return false;
        }
    }

    return true;
}

int GetCountOfCircularPrimes(const vector<bool> &primes)
{
    int count = 0;

    for (int i=0; i<primes.size(); ++i)
    {
        if (primes[i] && IsCircularPrime(i, primes))
        {
            ++count;
        }
    }

    return count;
}

int GetCountOfCircularPrimes(int n)
{
    vector<bool> primes = GetPrimes(n);

    return GetCountOfCircularPrimes(primes);
}

int main()
{
    cout << GetCountOfCircularPrimes(1000000) << endl;

    return 0;
}

