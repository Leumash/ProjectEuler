/*
We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is also prime.

What is the largest n-digit pandigital prime that exists?
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<int> GetDecreasingPermutations(int n)
{
    vector<int> toReturn;

    char permutation[n];

    for (int i=0; i<n; ++i)
    {
        permutation[i] = (n - i) + '0';
    }

    do
    {
        int toInsert = atoi(permutation);

        toReturn.push_back(toInsert);

    } while (prev_permutation(permutation, permutation + n));

    return toReturn;
}

bool IsPrime(int candidatePrime)
{
    if (candidatePrime < 2 || candidatePrime % 2 == 0)
    {
        return false;
    }

    for (int i=3; i<=sqrt(candidatePrime); i += 2)
    {
        if (candidatePrime % i == 0)
        {
            return false;
        }
    }

    return true;
}

int GetLargestPandigitalPrime()
{
    // Start with 7 because 1+2+3+4+5+6+7+8+9 and 1+2+3+4+5+6+7+8 are both always divisible by 3

    for (int i=7; i>0; --i)
    {
        vector<int> permutations = GetDecreasingPermutations(i);

        for (int j=0; j<permutations.size(); ++j)
        {
            if (IsPrime(permutations[j]))
            {
                return permutations[j];
            }
        }
    }

    return -1;
}

int main()
{
    cout << GetLargestPandigitalPrime() << endl;

    return 0;
}

