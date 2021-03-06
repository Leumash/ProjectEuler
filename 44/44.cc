/*
Pentagonal numbers are generated by the formula, Pn=n(3n−1)/2. The first ten pentagonal numbers are:

1, 5, 12, 22, 35, 51, 70, 92, 117, 145, ...

It can be seen that P4 + P7 = 22 + 70 = 92 = P8. However, their difference, 70 − 22 = 48, is not pentagonal.

Find the pair of pentagonal numbers, Pj and Pk, for which their sum and difference are pentagonal and D = |Pk − Pj| is minimised; what is the value of D?
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_set>

using namespace std;

int GetPentagonalNumber(int n)
{
    return (n * (3 * n - 1)) / 2;
}

bool IsPentagonalNumber(int potential)
{
    static unordered_set<int> pentagonalNumbers;
    static int largestPentagonalNumber = 0;
    static int i = 1;

    while (potential > largestPentagonalNumber)
    {
        int pentagonalNumber = GetPentagonalNumber(i);

        pentagonalNumbers.insert(pentagonalNumber);

        largestPentagonalNumber = pentagonalNumber;
        ++i;
    }

    return pentagonalNumbers.count(potential) > 0;
}

int GetMinimisedDifference()
{
    vector<int> pentagonalNumbers;

    for (int i=1; ; ++i)
    {
        int pentagonalNumber = GetPentagonalNumber(i);

        for (int i=pentagonalNumbers.size()-1; i >= 0; --i)
        {
            int difference = pentagonalNumber - pentagonalNumbers[i];
            int sum = pentagonalNumber + pentagonalNumbers[i];

            if (IsPentagonalNumber(difference) && IsPentagonalNumber(sum))
            {
                return difference;
            }
        }

        pentagonalNumbers.push_back(pentagonalNumber);
    }
}

int main()
{
    cout << GetMinimisedDifference() << endl;

    return 0;
}

