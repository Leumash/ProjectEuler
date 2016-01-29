/*
   The first two consecutive numbers to have two distinct prime factors are:

   14 = 2 × 7
   15 = 3 × 5

   The first three consecutive numbers to have three distinct prime factors are:

   644 = 2² × 7 × 23
   645 = 3 × 5 × 43
   646 = 2 × 17 × 19.

   Find the first four consecutive integers to have four distinct prime factors. What is the first of these numbers?
 */

#include <iostream>
#include <cmath>
#include <set>

using namespace std;

class PrimeTester
{
    public:
        PrimeTester();
        bool IsPrime(int);
        int GetNextPrime(int);  // O(log n)
    private:
        void GetNextPrime();
        bool TestIfPrime(int);

        set<int> primes;
        int currentLargestPrime;
};

int GetNumberOfDistinctPrimeFactors(int n)
{
    static PrimeTester primeTester;
    int currentPrime = 2;
    int numberOfDistinctPrimeFactors = 0;

    while (n > 1)
    {
        if (n % currentPrime == 0)
        {
            ++numberOfDistinctPrimeFactors;

            while (n % currentPrime == 0)
            {
                n /= currentPrime;
            }
        }

        currentPrime = primeTester.GetNextPrime(currentPrime);
    }

    return numberOfDistinctPrimeFactors;
}

int DoIt(int n)
{
    int consecutiveIntegersWithNDistinctPrimeFactors = 0;
    for (int i=2; ; ++i)
    {
        int numberOfDistinctPrimeFactors = GetNumberOfDistinctPrimeFactors(i);

        if (numberOfDistinctPrimeFactors == n)
        {
            ++consecutiveIntegersWithNDistinctPrimeFactors;
        }
        else
        {
            consecutiveIntegersWithNDistinctPrimeFactors = 0;
        }

        if (consecutiveIntegersWithNDistinctPrimeFactors == n)
        {
            return i - (n - 1);
        }
    }
}

int main()
{
    cout << DoIt(4) << endl;

    return 0;
}

PrimeTester::PrimeTester()
{
    primes.insert(2);
    primes.insert(3);

    currentLargestPrime = 3;
}

bool PrimeTester::IsPrime(int candidate)
{
    if (candidate < 2)
    {
        return false;
    }

    while (currentLargestPrime < sqrt(candidate))
    {
        GetNextPrime();
    }

    return TestIfPrime(candidate);
}

int PrimeTester::GetNextPrime(int previousPrime)
{
    while (currentLargestPrime <= previousPrime)
    {
        GetNextPrime();
    }

    set<int>::iterator sit = primes.find(previousPrime);

    if (sit == primes.end())
    {
        cout << previousPrime << " is not a prime!!!" << endl;
        exit(1);
    }

    return *(++sit);
}

bool PrimeTester::TestIfPrime(int candidate)
{
    for (set<int>::iterator sit = primes.begin(); *sit <= sqrt(candidate); ++sit)
    {
        if (candidate % *sit == 0)
        {
            return false;
        }
    }

    return true;
}

void PrimeTester::GetNextPrime()
{
    int candidate = currentLargestPrime + 2;

    while (!TestIfPrime(candidate))
    {
        candidate += 2;
    }

    currentLargestPrime = candidate;
    primes.insert(candidate);
}

