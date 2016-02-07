/*
The prime 41, can be written as the sum of six consecutive primes:

41 = 2 + 3 + 5 + 7 + 11 + 13
This is the longest sum of consecutive primes that adds to a prime below one-hundred.

The longest sum of consecutive primes below one-thousand that adds to a prime, contains 21 terms, and is equal to 953.

Which prime, below one-million, can be written as the sum of the most consecutive primes?
*/

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

vector<bool> GetPrimes(int limit)
{
    vector<bool> primes(limit, true);

    primes[0] = primes[1] = false;

    for (int i=2; i<limit; ++i)
    {
        if (primes[i] == true)
        {
            for (int multiplier = 2; multiplier * i < limit; ++multiplier)
            {
                primes[multiplier * i] = false;
            }
        }
    }

    return primes;
}

pair<int,int> GetPrimeAndConsecutivePrime(int startingPrime, vector<bool> &primes)
{
    int toReturnSum = 0;
    int toReturnCount = 0;
    int count = 0;
    int sum = 0;

    for (int i=startingPrime; i<primes.size(); ++i)
    {
        if (primes[i] == true)
        {
            sum += i;
            ++count;

            if (sum >= primes.size())
            {
                break;
            }

            if (primes[sum] == true)
            {
                toReturnSum = sum;
                toReturnCount = count;
            }
        }
    }

    return make_pair(toReturnSum, toReturnCount);
}

bool MyComp(pair<int,int> a, pair<int,int> b)
{
    return a.second < b.second;
}

int GetLargestSumOfMostConsecutivePrimes(int limit)
{
    vector<bool> primes = GetPrimes(limit);
    vector< pair<int,int> > primeAndConsecutivePrimes;

    for (int i=0; i<primes.size(); ++i)
    {
        if (primes[i] == true)
        {
            pair<int,int> primeAndConsecutivePrime = GetPrimeAndConsecutivePrime(i, primes);

            primeAndConsecutivePrimes.push_back(primeAndConsecutivePrime);
        }
    }

    auto max = max_element( primeAndConsecutivePrimes.begin(),
                            primeAndConsecutivePrimes.end(), MyComp);

    return max->first;
}

int main()
{
    cout << GetLargestSumOfMostConsecutivePrimes(1000000) << endl;

    return 0;
}

