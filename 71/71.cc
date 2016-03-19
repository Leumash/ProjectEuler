/*
Consider the fraction, n/d, where n and d are positive integers. If n<d and HCF(n,d)=1, it is called a reduced proper fraction.

If we list the set of reduced proper fractions for d ≤ 8 in ascending order of size, we get:

1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8

It can be seen that 2/5 is the fraction immediately to the left of 3/7.

By listing the set of reduced proper fractions for d ≤ 1,000,000 in ascending order of size, find the numerator of the fraction immediately to the left of 3/7.
*/

#include <iostream>
#include <unordered_set>
#include <set>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

int GetGcd(int a, int b)
{
    return b == 0 ? a : GetGcd(b, a % b);
}

pair<int,int> GetLargestFraction(vector< pair<int,int> > &fractions)
{
    double largestValue = 0;
    pair<int,int> largestFraction;

    for (auto fraction : fractions)
    {
        double val = fraction.first * 1.0 / fraction.second;

        if (val > largestValue)
        {
            largestValue = val;
            largestFraction = fraction;
        }
    }

    return largestFraction;
}

int BinarySearch(int front, int end, int denominator)
{
    int middle = (end - front) / 2 + front;

    double threeOverSeven = 3.0 / 7;
    double searchVal = middle * 1.0 / denominator;

    if (searchVal == threeOverSeven)
    {
        return middle - 1;
    }

    if (searchVal < threeOverSeven)
    {
        if ((middle + 1.0) / denominator > threeOverSeven)
        {
            return middle;
        }

        return BinarySearch(middle + 1, end, denominator);
    }
    else
    {
        if ((middle - 1.0) / denominator < threeOverSeven)
        {
            return middle - 1;
        }

        return BinarySearch(front, middle, denominator);
    }
}

int GetLargestNumeratorSmallerThanThreeOverSeven(int denominator)
{
    return BinarySearch(1, denominator, denominator);
}

vector< pair<int,int> > GetLargestFractionsSmallerThanThreeOverSeven(int limit)
{
    vector< pair<int,int> > fractions;

    for (int denominator = 2; denominator <= limit; ++denominator)
    {
        int largestNumerator;

        if (denominator % 7 == 0)
        {
            largestNumerator = (denominator / 7) * 3 - 1;
        }
        else
        {
            largestNumerator = GetLargestNumeratorSmallerThanThreeOverSeven(denominator);
        }

        int gcd = GetGcd(largestNumerator, denominator);

        fractions.push_back(make_pair(largestNumerator / gcd, denominator / gcd));
    }

    return fractions;
}

int GetNumeratorOfFractionToLeftOfThreeOverSeven(int limit)
{
    vector< pair<int,int> > fractionsLesThanThreeOverSeven =
        GetLargestFractionsSmallerThanThreeOverSeven(limit);

    pair<int,int> largestFraction = GetLargestFraction(fractionsLesThanThreeOverSeven);

    return largestFraction.first;
}

int main()
{
    cout << GetNumeratorOfFractionToLeftOfThreeOverSeven(1000000) << endl;

    return 0;
}
