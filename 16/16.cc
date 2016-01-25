/*
2 ^ 15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2 ^ 1000?
*/

#include <iostream>
#include <vector>

using namespace std;

vector<int> MultiplyEachElementByTwo(vector<int> n)
{
    for (int i=0; i<n.size(); ++i)
    {
        n[i] = n[i] * 2;
    }

    return n;
}

vector<int> PerformCarryOver(vector<int> n)
{
    n.push_back(0);

    for (int i=0; i<n.size()-1; ++i)
    {
        if (n[i] > 9)
        {
            n[i] -= 10;
            ++n[i+1];
        }
    }

    if (n[n.size() - 1] == 0)
    {
        n.pop_back();
    }

    return n;
}

vector<int> MultiplyByTwo(vector<int> n)
{
    n = MultiplyEachElementByTwo(n);

    n = PerformCarryOver(n);

    return n;
}

int GetSum(const vector<int> &n)
{
    int sum = 0;

    for (int i=0; i<n.size(); ++i)
    {
        sum += n[i];
    }

    return sum;
}

int GetSumOfPowerOfTwo(int n)
{
    vector<int> number;
    number.push_back(1);

    for (int i=0; i<n; ++i)
    {
        number = MultiplyByTwo(number);
    }

    
    return GetSum(number);
}

int main()
{
    cout << GetSumOfPowerOfTwo(1000) << endl;
}

