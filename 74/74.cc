/*
The number 145 is well known for the property that the sum of the factorial of its digits is equal to 145:

1! + 4! + 5! = 1 + 24 + 120 = 145

Perhaps less well known is 169, in that it produces the longest chain of numbers that link back to 169; it turns out that there are only three such loops that exist:

169 → 363601 → 1454 → 169
871 → 45361 → 871
872 → 45362 → 872

It is not difficult to prove that EVERY starting number will eventually get stuck in a loop. For example,

69 → 363600 → 1454 → 169 → 363601 (→ 1454)
78 → 45360 → 871 → 45361 (→ 871)
540 → 145 (→ 145)

Starting with 69 produces a chain of five non-repeating terms, but the longest non-repeating chain with a starting number below one million is sixty terms.

How many chains, with a starting number below one million, contain exactly sixty non-repeating terms?
*/

#include <iostream>
#include <set>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int arr[10];

void LoadArray()
{
    arr[0] = 1;
    arr[1] = 1;
    arr[2] = 2;
    arr[3] = 6;
    arr[4] = 24;
    arr[5] = 120;
    arr[6] = 720;
    arr[7] = 5040;
    arr[8] = 40320;
    arr[9] = 362880;
}

int Factorial(int n)
{
    return arr[n];

    if (n == 0 || n == 1)
    {
        return 1;
    }

    return n * Factorial(n - 1);
}

int GetSumOfFactorialOfItsDigits(int n)
{
    if (n == 0)
    {
        return 1;
    }

    int sum = 0;

    while (n != 0)
    {
        sum += Factorial(n % 10);
        n /= 10;
    }

    return sum;
}

int GetNumberOfNonRepeatingTerms(int n, unordered_map<int,int> &integerToChainLength)
{
    if (integerToChainLength.count(n) == 0)
    {
        int nextTerm = GetSumOfFactorialOfItsDigits(n);

        if (nextTerm == n)
        {
            integerToChainLength[n] = 1;
        }

        int nextLinkChainLength = GetNumberOfNonRepeatingTerms(nextTerm, integerToChainLength);

        integerToChainLength[n] = nextLinkChainLength + 1;
    }

    return integerToChainLength[n];
}

unordered_map<int,int> LoadMap()
{
    unordered_map<int,int> toReturn;

    toReturn[169] = 3;
    toReturn[363601] = 3;
    toReturn[1454] = 3;

    toReturn[871] = 2;
    toReturn[45361] = 2;

    toReturn[872] = 2;
    toReturn[45362] = 2;

    return toReturn;

}

int GetNumberOfChanins(int target, int limit)
{
    unordered_map<int, int> integerToChainLength = LoadMap();
    int count = 0;

    for (int i=0; i<limit; ++i)
    {
        int nonRepeatingTerms = GetNumberOfNonRepeatingTerms(i, integerToChainLength);

        if (nonRepeatingTerms == target)
        {
            ++count;
        }
    }

    return count;
}

int main()
{
    LoadArray();
    cout << GetNumberOfChanins(60, 1000000) << endl;

    return 0;
}

