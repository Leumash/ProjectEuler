/*
The proper divisors of a number are all the divisors excluding the number itself. For example, the proper divisors of 28 are 1, 2, 4, 7, and 14. As the sum of these divisors is equal to 28, we call it a perfect number.

Interestingly the sum of the proper divisors of 220 is 284 and the sum of the proper divisors of 284 is 220, forming a chain of two numbers. For this reason, 220 and 284 are called an amicable pair.

Perhaps less well known are longer chains. For example, starting with 12496, we form a chain of five numbers:

12496 → 14288 → 15472 → 14536 → 14264 (→ 12496 → ...)

Since this chain returns to its starting point, it is called an amicable chain.

Find the smallest member of the longest amicable chain with no element exceeding one million.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

pair<int,int> GetSmallestMemberAndLength(int n, vector<bool> &processed, int maxNumber, const vector<int> &numberToSumOfDivisors)
{
    bool invalidCondition = false;
    vector<int> membersInChain;

    while (find(membersInChain.begin(), membersInChain.end(), n) == membersInChain.end())
    {
        membersInChain.push_back(n);

        n = numberToSumOfDivisors.at(n);

        if (n > maxNumber || n == 1 || processed[n])
        {
            invalidCondition = true;
            break;
        }
    }

    for (int element : membersInChain)
    {
        processed[element] = true;
    }

    if (invalidCondition)
    {
        return make_pair(0,0);
    }

    membersInChain.clear();

    while (find(membersInChain.begin(), membersInChain.end(), n) == membersInChain.end())
    {
        membersInChain.push_back(n);

        n = numberToSumOfDivisors.at(n);
    }

    return make_pair(*min_element(membersInChain.begin(), membersInChain.end()), membersInChain.size());
}

void GetNumberToSumOfDivisors(int maxNumber, vector<int> &numberToSumOfDivisors)
{
    numberToSumOfDivisors.resize(maxNumber + 1);

    for (int i=2; i<=maxNumber; ++i)
    {
        numberToSumOfDivisors[i] = 1;
    }

    for (int divisor=2; divisor<=maxNumber/2; ++divisor)
    {
        for (int multiplier=2; multiplier*divisor <= maxNumber; ++multiplier)
        {
            numberToSumOfDivisors[multiplier * divisor] += divisor;
        }
    }
}

int GetSmallestMemberOfLongestAmicableChain(int maxElement)
{
    int smallestMember = 0;
    int longestLength = 0;
    vector<bool> processed(maxElement + 1, false);
    vector<int> numberToSumOfDivisors;

    GetNumberToSumOfDivisors(maxElement, numberToSumOfDivisors);

    processed[1] = true;

    for (int i=2; i<=maxElement; ++i)
    {
        if (processed[i])
        {
            continue;
        }

        pair<int,int> smallestMemberAndLength = GetSmallestMemberAndLength(i, processed, maxElement, numberToSumOfDivisors);

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
    cout << GetSmallestMemberOfLongestAmicableChain(1000000) << endl;

    return 0;
}

