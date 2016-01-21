#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

vector<int> GetSumOfSelfAndReverse(const vector<int> &n)
{
    vector<int> toReturn;
    bool carryOver = false;

    for (int i=0; i<n.size(); ++i)
    {
        toReturn.push_back(n[i] + n[n.size() - 1 - i]);

        if (carryOver)
        {
            ++toReturn[toReturn.size()-1];
            carryOver = false;
        }

        if (toReturn[toReturn.size()-1] >= 10)
        {
            toReturn[toReturn.size()-1] -= 10;
            carryOver = true;
        }
    }

    if (carryOver)
    {
        toReturn.push_back(1);
    }

    return toReturn;
}

bool IsPalindrome(const vector<int> &n)
{
    for (int i=0; i<n.size()/2; ++i)
    {
        if (n[i] != (n[n.size() - 1 - i]))
        {
            return false;
        }
    }

    return true;
}

bool IsLychrelNumber(const vector<int> &n, int depth)
{
    vector<int> sumOfNAndReverse = GetSumOfSelfAndReverse(n);

    if (IsPalindrome(sumOfNAndReverse))
    {
        return false;
    }
    else if (depth < 50)
    {
        return IsLychrelNumber(sumOfNAndReverse, depth + 1);
    }

    return true;

}

vector<int> ConvertToVector(int n)
{
    vector<int> toReturn;

    if (n == 0)
    {
        toReturn.push_back(0);
    }
    else
    {
        while (n > 0)
        {
            toReturn.push_back(n%10);
            n /= 10;
        }
    }

    return toReturn;
}

bool IsLychrelNumber(int n)
{
    vector<int> vectorizedN = ConvertToVector(n);

    return IsLychrelNumber(vectorizedN, 0);
}

int CountLychrelNumbers(int n)
{
    int count = 0;

    for (int i=78; i<n; ++i)
    {
        if (IsLychrelNumber(i))
        {
            ++count;
        }
    }

    return count;
}

int main()
{
    cout << CountLychrelNumbers(10000) << endl;
}

