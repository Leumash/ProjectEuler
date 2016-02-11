/*
It was proposed by Christian Goldbach that every odd composite number can be written as the sum of a prime and twice a square.

9 = 7 + 2×1²
15 = 7 + 2×2²
21 = 3 + 2×3²
25 = 7 + 2×3²
27 = 19 + 2×2²
33 = 31 + 2×1²

It turns out that the conjecture was false.

What is the smallest odd composite that cannot be written as the sum of a prime and twice a square?
*/

#include <iostream>
#include <vector>

using namespace std;

vector<bool> GetPrimes(int size)
{
    vector<bool> primes(size, true);

    primes[0] = false;
    primes[1] = false;

    for (int i=2; i<size; ++i)
    {
        if (primes[i])
        {
            for (int multiplier = 2; multiplier * i < size; ++multiplier)
            {
                primes[multiplier * i] = false;
            }
        }
    }

    return primes;
}

bool IsPrime(int potentialPrime)
{
    static int size = 1;
    static vector<bool> primes;

    if (size < potentialPrime)
    {
        while (size < potentialPrime)
        {
            size *= 10;
        }

        primes = GetPrimes(size);
    }

    return primes[potentialPrime];
}

int GetSmallestOddComposite()
{
    for (int i=9; ; i += 2)
    {
        if (!IsPrime(i))
        {
            bool isSum = false;

            for (int j=1; 2*j*j < i; ++j)
            {
                int potentialPrime = i - 2*j*j;

                if (IsPrime(potentialPrime))
                {
                    isSum = true;
                }
            }

            if (!isSum)
            {
                return i;
            }
        }
    }
}

int main()
{
    cout << GetSmallestOddComposite() << endl;
    return 0;
}

