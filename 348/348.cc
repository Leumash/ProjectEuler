/*
Many numbers can be expressed as the sum of a square and a cube. Some of them in more than one way.

Consider the palindromic numbers that can be expressed as the sum of a square and a cube, both greater than 1, in exactly 4 different ways.
For example, 5229225 is a palindromic number and it can be expressed in exactly 4 different ways:

2285 ^ 2 + 20 ^ 3
2223 ^ 2 + 66 ^ 3
1810 ^ 2 + 125 ^ 3
1197 ^ 2 + 156 ^ 3

Find the sum of the five smallest such palindromic numbers.
*/

/*
a ^ 2 + b ^ 3 = Palindrome
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

bool IsSquare(long long n)
{
    long long squareRoot = sqrt(n);

    return pow(squareRoot,2) == n;
}

int GetWaysToExpressAsSumOfSquareAndCube(long long n)
{
    int count = 0;

    for (int b = 2; pow(b, 3) < n; ++b)
    {
        int cubeOfB = pow(b, 3);
        int potentialSquareOfA = n - cubeOfB;

        if (potentialSquareOfA > 1)
        {
            if (IsSquare(potentialSquareOfA))
            {
                ++count;
            }
        }
    }

    return count;
}

vector<int> ConvertToVector(long long n)
{
    vector<int> toReturn;

    if (n == 0)
    {
        toReturn.push_back(0);
        return toReturn;
    }

    while (n)
    {
        toReturn.push_back(n % 10);
        n /= 10;
    }

    reverse(toReturn.begin(), toReturn.end());

    return toReturn;
}

bool IsValidPalindrome(long long n)
{
    int countOfWaysToExpressAsSumOfSquareAndCube = 0;

    countOfWaysToExpressAsSumOfSquareAndCube = GetWaysToExpressAsSumOfSquareAndCube(n);

    return countOfWaysToExpressAsSumOfSquareAndCube == 4;

}

bool IsOdd(vector<int> n)
{
    return n.size() % 2;
}
vector<int> RemoveBottomHalfOfNumber(vector<int> n)
{
    int popCount = n.size() / 2;

    for (int i=0; i<popCount; ++i)
    {
        n.pop_back();
    }

    return n;
}

long long ConvertToInt(vector<int> n)
{
    long long number = 0;
    int pos = 0;

    for (int i=n.size() - 1; i >= 0; --i, ++pos)
    {
        number += n[i] * pow(10, pos);
    }

    return number;
}

vector<int> IncrementNumber(vector<int> n)
{
    long long number = ConvertToInt(n);

    ++number;

    return ConvertToVector(number);

}

bool CheckIfIncreaseOccurred(vector<int> n)
{
    if (n[0] != 1)
    {
        return false;
    }

    for (int i=1; i<n.size(); ++i)
    {
        if (n[i] != 0)
        {
            return false;
        }
    }

    return true;
}

vector<int> AddBottomHalfOfNumber(vector<int> n, bool isOdd)
{
    vector<int> toReturn = n;

    bool increasedOccurred = CheckIfIncreaseOccurred(n);

    if (increasedOccurred)
    {
        if (isOdd)
        {
            toReturn.pop_back();
            n.pop_back();
        }

        isOdd = !isOdd;
    }

    long long i = n.size() - 1;
    if (isOdd)
    {
        --i;
    }

    for (; i>=0; --i)
    {
        toReturn.push_back(n[i]);
    }

    return toReturn;
}

vector<int> GetNextPalindrome(vector<int> n)
{
    bool isOdd = IsOdd(n);
    vector<int> toReturn;

    toReturn = RemoveBottomHalfOfNumber(n);

    toReturn = IncrementNumber(toReturn);

    toReturn = AddBottomHalfOfNumber(toReturn, isOdd);

    return toReturn;
}

long long GetNextPalindrome(long long n)
{
    vector<int> number = ConvertToVector(n);

    number = GetNextPalindrome(number);

    return ConvertToInt(number);
}

int GetSum()
{
    int sum = 0;
    int found = 0;
    long long currentPalindrome = 1;

    while (found < 5)
    {
        currentPalindrome = GetNextPalindrome(currentPalindrome);

        if (IsValidPalindrome(currentPalindrome))
        {
            ++found;
            sum += currentPalindrome;
        }
    }

    return sum;
}

int main()
{
    cout << GetSum() << endl;
}

