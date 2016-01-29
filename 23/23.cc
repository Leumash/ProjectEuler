/*
A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.

A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.

As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers is 24. By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers. However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.

Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
*/

#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<int> GetDivisors(int n)
{
    // Inefficient algorithm

    vector<int> toReturn;

    for (int i=1; i<=n/2; ++i)
    {
        if (n % i == 0)
        {
            toReturn.push_back(i);
        }
    }

    return toReturn;
}

int GetSum(vector<int> list)
{
    int sum = 0;

    for (int i=0; i<list.size(); ++i)
    {
        sum += list[i];
    }

    return sum;
}

int GetSumOfDivisors(int n)
{
    vector<int> divisors = GetDivisors(n);

    return GetSum(divisors);
}

bool IsAbundantNumber(int n)
{
    int sum = GetSumOfDivisors(n);

    return sum > n;
}

set<int> GetAbundantNumbers(int n)
{
    set<int> toReturn;

    for (int i=1; i<n; ++i)
    {
        if (IsAbundantNumber(i))
        {
            toReturn.insert(i);
        }
    }

    return toReturn;
}

bool IsSumOfTwoAbundantNumbers(int n, const set<int> &abundantNumbers)
{
    for (auto sit = abundantNumbers.cbegin();
        sit != abundantNumbers.cend() && *sit <= n / 2; ++sit)
    {
        // n = a + b
        int a = *sit;
        int b = n - a;

        //if (abundantNumbers.count(n - *sit) == 1)
        if (abundantNumbers.count(b) == 1)
        {
            return true;
        }
    }

    return false;
}

int GetSumOfAllPositiveIntegersThatIsNotSumOfTwoAbundantNumbers(int n)
{
    int sum = 0;
    set<int> abundantNumbers = GetAbundantNumbers(n);

    for (int i=1; i<=n; ++i)
    {
        if (!IsSumOfTwoAbundantNumbers(i, abundantNumbers))
        {
            sum += i;
        }
    }

    return sum;
}

int main()
{
    cout << GetSumOfAllPositiveIntegersThatIsNotSumOfTwoAbundantNumbers(28123) << endl;

    return 0;
}

