/*
It is possible to write ten as the sum of primes in exactly five different ways:

7 + 3
5 + 5
5 + 3 + 2
3 + 3 + 2 + 2
2 + 2 + 2 + 2 + 2

What is the first value which can be written as the sum of primes in over five thousand different ways?
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<bool> GetSievePrimes(int limit)
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

vector<int> GetPrimes(int limit)
{
    vector<bool> primes = GetSievePrimes(limit);
    vector<int> primesToReturn;

    for (int i=0; i<primes.size(); ++i)
    {
        if (primes[i] == true)
        {
            primesToReturn.push_back(i);
        }
    }

    return primesToReturn;
}

int GetValueThatCanBeWrittenAsSumOfPrimes(int ways)
{
    for (int size=10; ; size *= 10)
    {
        int arr[size] = {0};

        arr[0] = 1;

        vector<int> primes = GetPrimes(size);

        for (int prime : primes)
        {
            for (int i=0; i+prime < size; ++i)
            {
                arr[i+prime] += arr[i];
            }
        }

        for (int i=0; i<size; ++i)
        {
            if (arr[i] > ways)
            {
                return i;
            }
        }
    }
}

int main()
{
    cout << GetValueThatCanBeWrittenAsSumOfPrimes(5000) << endl;

    return 0;
}

