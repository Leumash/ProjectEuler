/*
A natural number, N, that can be written as the sum and product of a given set of at least two natural numbers, {a1, a2, ... , ak} is called a product-sum number: N = a1 + a2 + ... + ak = a1 × a2 × ... × ak.

For example, 6 = 1 + 2 + 3 = 1 × 2 × 3.

For a given set of size, k, we shall call the smallest N with this property a minimal product-sum number. The minimal product-sum numbers for sets of size, k = 2, 3, 4, 5, and 6 are as follows.

k=2: 4 = 2 × 2 = 2 + 2
k=3: 6 = 1 × 2 × 3 = 1 + 2 + 3
k=4: 8 = 1 × 1 × 2 × 4 = 1 + 1 + 2 + 4
k=5: 8 = 1 × 1 × 2 × 2 × 2 = 1 + 1 + 2 + 2 + 2
k=6: 12 = 1 × 1 × 1 × 1 × 2 × 6 = 1 + 1 + 1 + 1 + 2 + 6

Hence for 2≤k≤6, the sum of all the minimal product-sum numbers is 4+6+8+12 = 30; note that 8 is only counted once in the sum.

In fact, as the complete set of minimal product-sum numbers for 2≤k≤12 is {4, 6, 8, 12, 15, 16}, the sum is 61.

What is the sum of all the minimal product-sum numbers for 2≤k≤12000?
*/

/*

1. Given a number n, find the minimum size of k that can form that from n
    Basically, given n, find k
    - Find the first prime divisor p
        - k = n - (n/p + p) + 2
2. Given n and k, find all n k' pairs where k' > k
    - Generate using previous solutions
        - Find all factors a and b | n = a * b
            - For every possible k of a and b, generate a k that n can become
3. Find the limit of n (where to stop)
    - I have to find all n for 2 <= k <= 12000
        - Iterate with increasing n's, find k's
        - Once all k's in the range 2 <= k <= 12000 have been found stop
            - You can stop because any further n's which find k, increase the value of n

*/

#include <iostream>
#include <vector>
#include <utility>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int GetUniqueSums(const unordered_map<int,int> &kToN)
{
    int sum = 0;
    unordered_set<int> uniqueValues;

    for (const auto &a : kToN)
    {
        uniqueValues.insert(a.second);
    }

    for (int uniqueValue : uniqueValues)
    {
        sum += uniqueValue;
    }

    return sum;
}

vector<pair<int,int>> GetFactors(int n)
{
    vector<pair<int,int>> factors;

    for (int a = 2; ; ++a)
    {
        int b = n / a;

        if (a > b)
        {
            break;
        }

        if (a * b == n)
        {
            factors.push_back(make_pair(a,b));
        }
    }

    return factors;
}

int GetSumOfMinimalProductSumNumbers(unsigned int maxK)
{
    unordered_map<int,unordered_set<int>> nToPossibleKs;
    unordered_map<int,int> kToN;

    int n = 1;

    while (kToN.size() <= maxK - 2)
    {
        ++n;

        unordered_set<int> possibleKs;
        vector<pair<int,int>> allFactors = GetFactors(n);

        if (allFactors.size() == 0)
        {
            nToPossibleKs[n] = unordered_set<int>({1});
            continue;
        }

        for (const pair<int,int> &factors : allFactors)
        {
            int numberOfOnesToAdd = n - (factors.first + factors.second);

            for (const int &k1 : nToPossibleKs[factors.first])
            {
                for (const int &k2 : nToPossibleKs[factors.second])
                {
                    possibleKs.insert(k1 - 1 + k2 - 1 + numberOfOnesToAdd + 2);
                }
            }
        }

        for (unsigned int k : possibleKs)
        {
            if (kToN.count(k) == 0 && 2 <= k && k <= maxK)
            {
                kToN[k] = n;
            }
        }

        possibleKs.insert(1);


        nToPossibleKs[n] = possibleKs;
    }

    return GetUniqueSums(kToN);
}

int main()
{
    cout << GetSumOfMinimalProductSumNumbers(12000) << endl;

    return 0;
}

