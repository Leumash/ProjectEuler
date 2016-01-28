/*
A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions with denominators 2 to 10 are given:

1/2 =   0.5
1/3 =   0.(3)
1/4 =   0.25
1/5 =   0.2
1/6 =   0.1(6)
1/7 =   0.(142857)
1/8 =   0.125
1/9 =   0.(1)
1/10    =   0.1
Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has a 6-digit recurring cycle.

Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> GetListOfDecimals(int n, int length)
{
    vector<int> toReturn;

    int remainder = 1;
    int divisor = n;

    for (int i=0; i<length; ++i)
    {
        remainder *= 10;
        toReturn.push_back(remainder / divisor);

        remainder %= divisor;

        if (remainder == 0)
        {
            return toReturn;
        }
    }

    return toReturn;
}

bool RepeatPatternDetected(const vector<int> &toCheck, int repeatLength, int repeatThreshold)
{
    for (int repeat=1; repeat<repeatThreshold; ++repeat)
    {
        for (int pos=0, repeatPos=repeat * repeatLength; pos<repeatLength; ++pos, ++repeatPos)
        {
            if (toCheck[pos] != toCheck[repeatPos])
            {
                return false;
            }
        }
    }

    return true;
}

int GetRepeatLength(vector<int> listOfDecimals)
{
    int repeatThreshold = 3;
    vector<int> toCheck = listOfDecimals;

    reverse(toCheck.begin(), toCheck.end());

    int pos = 1;

    for (int pos = 1; pos < toCheck.size(); ++pos)
    {
        if (RepeatPatternDetected(toCheck, pos, repeatThreshold))
        {
            return pos;
        }
    }

    return 0;
}


int GetRecurringCycleLength(int n)
{
    int numberOfDecimals = 10000;
    vector<int> listOfDecimals = GetListOfDecimals(n, numberOfDecimals);

    if (listOfDecimals.size() < numberOfDecimals)
    {
        return 0;
    }

    return GetRepeatLength(listOfDecimals);
}

int GetLongestRecurringCycle(int n)
{
    int longestRecurringCycleNumber = 0;
    int longestRecurringCycle = 0;

    for (int i=1; i<n; ++i)
    {
        int recurringCycleLength = GetRecurringCycleLength(i);

        if (recurringCycleLength > longestRecurringCycle)
        {
            longestRecurringCycle = recurringCycleLength;
            longestRecurringCycleNumber = i;
        }
    }

    return longestRecurringCycleNumber;
}

int main()
{
    cout << GetLongestRecurringCycle(1000) << endl;

    return 0;
}

