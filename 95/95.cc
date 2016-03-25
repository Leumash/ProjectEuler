/*
The proper divisors of a number are all the divisors excluding the number itself. For example, the proper divisors of 28 are 1, 2, 4, 7, and 14. As the sum of these divisors is equal to 28, we call it a perfect number.

Interestingly the sum of the proper divisors of 220 is 284 and the sum of the proper divisors of 284 is 220, forming a chain of two numbers. For this reason, 220 and 284 are called an amicable pair.

Perhaps less well known are longer chains. For example, starting with 12496, we form a chain of five numbers:

12496 → 14288 → 15472 → 14536 → 14264 (→ 12496 → ...)

Since this chain returns to its starting point, it is called an amicable chain.

Find the smallest member of the longest amicable chain with no element exceeding one million.
*/

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

unordered_map<int,int> MakeMap(int maxNumber)
{
    unordered_map<int,int> numberToSumOfDivisors;

    for (int i=1; i<=maxNumber; ++i)
    {
        numberToSumOfDivisors[i] = 1;
    }

    for (int divisor=2; divisor<=maxNumber; ++divisor)
    {
        for (int multiplier=2; multiplier*divisor <= maxNumber; ++multiplier)
        {
            numberToSumOfDivisors[multiplier * divisor] += divisor;
        }
    }

    return numberToSumOfDivisors;
}

int GetSumOfDivisors(int n, int maxNumber)
{
    static unordered_map<int,int> numberToSumOfDivisors = MakeMap(maxNumber);

    return numberToSumOfDivisors[n];
}

pair<int,int> GetSmallestMemberAndLength(int n, unordered_set<int> &processed, int maxNumber)
{
    bool invalidCondition = false;
    unordered_set<int> membersInChain;

    while (membersInChain.count(n) == 0)
    {
        membersInChain.insert(n);

        n = GetSumOfDivisors(n, maxNumber);

        if (n > maxNumber || n == 1 || processed.count(n) > 0)
        {
            invalidCondition = true;
            break;
        }
    }

    for (int element : membersInChain)
    {
        processed.insert(element);
    }

    if (invalidCondition)
    {
        return make_pair(0,0);
    }

    membersInChain.clear();

    while (membersInChain.count(n) == 0)
    {
        membersInChain.insert(n);

        n = GetSumOfDivisors(n, maxNumber);
    }

    return make_pair(*min_element(membersInChain.begin(), membersInChain.end()), membersInChain.size());
}

int GetSmallestMemberOfLongestAmicableChain(int maxElement)
{
    int smallestMember = 0;
    int longestLength = 0;
    unordered_set<int> processed;

    processed.insert(1);

    for (int i=1; i<=maxElement; ++i)
    {
        if (processed.count(i) > 0)
        {
            continue;
        }

        pair<int,int> smallestMemberAndLength = GetSmallestMemberAndLength(i, processed, maxElement);

        if (smallestMemberAndLength.second > longestLength)
        {
            longestLength = smallestMemberAndLength.second;
            smallestMember = smallestMemberAndLength.first;
        }
    }

    return smallestMember;
}

int main()
{
    //cout << GetSmallestMemberOfLongestAmicableChain(1000000) << endl;

    GetSumOfDivisors(1,1000000);

    return 0;
}

