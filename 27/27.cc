/*
   Euler discovered the remarkable quadratic formula:

   n² + n + 41

   It turns out that the formula will produce 40 primes for the consecutive values n = 0 to 39. However, when n = 40, 402 + 40 + 41 = 40(40 + 1) + 41 is divisible by 41, and certainly when n = 41, 41² + 41 + 41 is clearly divisible by 41.

   The incredible formula  n² − 79n + 1601 was discovered, which produces 80 primes for the consecutive values n = 0 to 79. The product of the coefficients, −79 and 1601, is −126479.

   Considering quadratics of the form:

   n² + an + b, where |a| < 1000 and |b| < 1000

   where |n| is the modulus/absolute value of n
   e.g. |11| = 11 and |−4| = 4
   Find the product of the coefficients, a and b, for the quadratic expression that produces the maximum number of primes for consecutive values of n, starting with n = 0.
 */

/*
 max n = 500

 500 499 498 ...

 maxn = 1000

 1000 999 998 997....

 500
 p p p p p p np np p p np np
 p p p np np np np np p p np np
 */

#include <iostream>
#include <set>
#include <cmath>

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

int SolveQuadratic(int n, int a, int b)
{
    // n² + an + b
    return pow(n, 2) + a * n + b;
}

int GetConsecutivePrimes(int a, int b)
{
    static PrimeTester primeTester;

    for (int n=0; ; ++n)
    {
        int result = SolveQuadratic(n, a, b);

        if (!primeTester.IsPrime(result))
        {
            return n;
        }
    }
}

int DoIt()
{
    int a;
    int b;
    int maximumCountOfConsecutivePrimes = 0;

    for (int currentA = -999; currentA < 1000; ++currentA)
    {
        for (int currentB = -999; currentB < 1000; ++currentB)
        {
            int consecutivePrimes = GetConsecutivePrimes(currentA, currentB);

            if (consecutivePrimes > maximumCountOfConsecutivePrimes)
            {
                maximumCountOfConsecutivePrimes = consecutivePrimes;

                a = currentA;
                b = currentB;
            }
        }
    }

    return a * b;
}

int main()
{
    cout << DoIt() << endl;

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

