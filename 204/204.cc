/*
A Hamming number is a positive number which has no prime factor larger than 5.
So the first few Hamming numbers are 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15.
There are 1105 Hamming numbers not exceeding 10^8.

We will call a positive number a generalised Hamming number of type n, if it has no prime factor larger than n.
Hence the Hamming numbers are the generalised Hamming numbers of type 5.

How many generalised Hamming numbers of type 100 are there which don't exceed 10^9?
*/

/*
Primes under 100
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 
*/

/*
for each prime
    while divisible by prime
        divide out the prime
Is left over number > 1?
*/

#include <iostream>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

vector<long long> GetPrimesUnder100()
{
    int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    vector<long long> prime(primes, primes + sizeof(primes) / sizeof(primes[0]));
    return prime;
}

int GeneralisedHammingNumbers(int limit)
{
    vector<long long> prime = GetPrimesUnder100();
    set<long long> hammingNumber;

    hammingNumber.insert(1);

    for (int p=0; p<prime.size(); ++p)
    {
        long long primeExponent = prime[p];

        while (primeExponent <= limit)
        {
            vector<long long> toAdd;

            for(set<long long>::iterator it=hammingNumber.begin();
                it != hammingNumber.end(); ++it)
            {
                long long candidate = *it * primeExponent;
                if (candidate <= limit)
                {
                    toAdd.push_back(candidate);
                }
            }

            for (int i=0; i<toAdd.size(); ++i)
            {
                hammingNumber.insert(toAdd[i]);
            }

            primeExponent *= prime[p];
        }
    }

    return hammingNumber.size();
}

int main()
{
    cout << GeneralisedHammingNumbers(1000000000) << endl;
}

