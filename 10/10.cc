/*
The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
*/

#include <iostream>
#include <set>
#include <cmath>

using namespace std;

bool IsPrime(long long candidatePrime, const set<long long> &prime)
{
    long long squareRoot = sqrt(candidatePrime);

    for (set<long long>::const_iterator cit = prime.begin(); cit != prime.end(); ++cit)
    {
        if (candidatePrime % *cit == 0)
        {
            return false;
        }

        if (*cit > squareRoot)
        {
            break;
        }
    }

    return true;
}

long long GetSum(const set<long long> &prime)
{
    long long sum = 0;

    for (set<long long>::const_iterator cit = prime.begin(); cit != prime.end(); ++cit)
    {
        sum += *cit;
    }

    return sum;
}


long long GetSumOfPrimesLessThan(long long limit)
{
    if (limit <= 2)
    {
        return 0;
    }
    else if (limit == 3)
    {
        return 2;
    }

    long long candidatePrime = 3;
    set<long long> prime;

    prime.insert(2);

    while (candidatePrime < limit)
    {
        if (IsPrime(candidatePrime, prime))
        {
            prime.insert(candidatePrime);
        }

        candidatePrime += 2;
    }

    return GetSum(prime);
}

int main()
{
    cout << GetSumOfPrimesLessThan(2000000) << endl;
}

