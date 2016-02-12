/*
The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330, is unusual in two ways: (i) each of the three terms are prime, and, (ii) each of the 4-digit numbers are permutations of one another.

There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes, exhibiting this property, but there is one other 4-digit increasing sequence.

What 12-digit number do you form by concatenating the three terms in this sequence?
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <cmath>

using namespace std;

vector<bool> GetPrimes(int limit)
{
    vector<bool> primes(limit, true);

    primes[0] = false;
    primes[1] = false;

    for (int i=2; i<=sqrt(limit); ++i)
    {
        if (primes[i] == true)
        {
            for (int multiplier = 2; multiplier * i < limit; ++multiplier)
            {
                primes[i * multiplier] = false;
            }
        }
    }

    return primes;
}

vector<int> GetPrimes(int start, int end)
{
    vector<int> toReturn;
    vector<bool> primes = GetPrimes(end);

    for (int i=start; i<end; ++i)
    {
        if (primes[i] == true)
        {
            toReturn.push_back(i);
        }
    }

    return toReturn;
}

unordered_set<int> GetLargerPrimePermutations(int prime, const vector<bool> &primes)
{
    unordered_set<int> toReturn;

    char permutation[5];

    itoa(prime, permutation, 10);

    while (next_permutation(permutation, permutation + 4))
    {
        if (primes[atoi(permutation)] == true)
        {
            toReturn.insert(atoi(permutation));
        }
    }

    return toReturn;
}

long long GetConcatenation(const vector<int> &list)
{
    long long toReturn;
    stringstream ss;

    for (int num : list)
    {
        ss << num;
    }

    ss >> toReturn;

    return toReturn;
}

vector<long long> GetConcatenatedTriplePermutationPrimes()
{
    int start = 1000;
    int end = 10000;
    vector<long long> toReturn;
    vector<bool> primes = GetPrimes(end);

    for (int i=start; i<end; ++i)
    {
        if (primes[i] == true)
        {
            int prime = i;

            unordered_set<int> largerPrimePermutations = GetLargerPrimePermutations(prime, primes);

            for (int largerPrimePermutation : largerPrimePermutations)
            {
                int difference = largerPrimePermutation - prime;

                if (largerPrimePermutations.count(prime + difference * 2) > 0)
                {
                    vector<int> toConcatenate;

                    toConcatenate.push_back(prime);
                    toConcatenate.push_back(prime + difference);
                    toConcatenate.push_back(prime + difference * 2);

                    toReturn.push_back(GetConcatenation(toConcatenate));
                }
            }
        }
    }

    return toReturn;
}

int main()
{
    vector<long long> answers = GetConcatenatedTriplePermutationPrimes();

    for (auto answer : answers)
    {
        cout << answer << endl;
    }

    return 0;
}

