/*
In the following equation x, y, and n are positive integers.

    1   1   1
    - + - = -
    x   y   n

It can be verified that when n = 1260 there are 113 distinct solutions and this is the least value of n for which the total number of distinct solutions exceeds one hundred.

What is the least value of n for which the number of distinct solutions exceeds four million?

NOTE: This problem is a much more difficult version of Problem 108 and as it is well beyond the limitations of a brute force approach it requires a clever implementation.
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <unordered_map>

using namespace std;

bool IsPrime(int n)
{
    for (int i=2; i<=sqrt(n); ++i)
    {
        if (n % i == 0)
        {
            return false;
        }
    }

    return true;
}

int GetNextPrime(int prime)
{
    for (int i=prime+1; ; ++i)
    {
        if (IsPrime(i))
        {
            return i;
        }
    }
}

int GetNumberOfDistinctSolutions(const unordered_map<int,int> &primeFactorization)
{
    int numberOfFactors = 1;

    for (const auto &primeFactor : primeFactorization)
    {
        numberOfFactors *= ((primeFactor.second * 2) + 1);
    }

    return (numberOfFactors + 1) / 2;
}

vector<int> GetPrimeNumbersForSolution(int numberOfDistinctSolutions)
{
    vector<int> primes;
    unordered_map<int,int> primeFactorization;
    int prime = 1;

    while (GetNumberOfDistinctSolutions(primeFactorization) <= numberOfDistinctSolutions)
    {
        prime = GetNextPrime(prime);

        primes.push_back(prime);
        primeFactorization[prime] = 1;
    }

    return primes;
}

unsigned long long GetProduct(const vector<int> &numbers)
{
    unsigned long long product = 1;

    for (int n : numbers)
    {
        product *= n;
    }

    return product;
}

unordered_map<int,int> MakeInitialMap(const vector<int> &primeNumbers)
{
    unordered_map<int,int> toReturn;

    for (int prime : primeNumbers)
    {
        toReturn[prime] = 0;
    }

    return toReturn;
}

void FindMinimumN(const vector<int> &primeNumbers, unsigned int index, unsigned long long upperBoundOfN, unsigned long long &minimumN, unordered_map<int,int> &primeFactorization, int numberOfDistinctSolutions, unsigned long long currentN)
{
    if (index >= primeNumbers.size())
    {
        if (GetNumberOfDistinctSolutions(primeFactorization) > numberOfDistinctSolutions)
        {
            minimumN = min(minimumN, currentN);
        }

        return;
    }

    int maxNumberOfExponents = index == 0 ? numeric_limits<int>::max() : primeFactorization[primeNumbers[index - 1]];

    for (int exponents = 0; exponents <= maxNumberOfExponents; ++exponents)
    {
        primeFactorization[primeNumbers[index]] = exponents;

        if (exponents > 0)
        {
            currentN = currentN * primeNumbers[index];
        }

        if (currentN > upperBoundOfN)
        {
            break;
        }

        FindMinimumN(primeNumbers, index + 1, upperBoundOfN, minimumN, primeFactorization, numberOfDistinctSolutions, currentN);
    }

    primeFactorization[primeNumbers[index]] = 0;
}

unsigned long long GetLeastValueWhereDistinctSolutionsExceeds(int numberOfDistinctSolutions)
{
    vector<int> primeNumbers = GetPrimeNumbersForSolution(numberOfDistinctSolutions);

    unsigned long long upperBoundOfN = GetProduct(primeNumbers);
    unsigned long long minimumN = upperBoundOfN;
    unsigned long long currentN = 1;

    unordered_map<int,int> primeFactorization = MakeInitialMap(primeNumbers);

    FindMinimumN(primeNumbers, 0, upperBoundOfN, minimumN, primeFactorization, numberOfDistinctSolutions, currentN);

    return minimumN;
}

int main()
{
    cout << GetLeastValueWhereDistinctSolutionsExceeds(4000000) << endl;

    return 0;
}

