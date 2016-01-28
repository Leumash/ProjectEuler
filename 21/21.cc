/*
Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair and each of a and b are called amicable numbers.

For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.

Evaluate the sum of all the amicable numbers under 10000.
*/

#include <iostream>
#include <vector>

using namespace std;

int GetSum(vector<int> n)
{
    int sum = 0;

    for (int i=0; i<n.size(); ++i)
    {
        sum += n[i];
    }

    return sum;
}

vector<int> GetDivisors(int n)
{
    // There are better methods, but since it's < 10000, simply iterating thorugh is good enough

    vector<int> toReturn;

    for (int i=1; i<n; ++i)
    {
        if (n%i == 0)
        {
            toReturn.push_back(i);
        }
    }

    return toReturn;
}

int GetSumOfProperDivisors(int n)
{
    vector<int> divisors = GetDivisors(n);

    return GetSum(divisors);
}

bool IsAmicableNumber(int a)
{
    int da = GetSumOfProperDivisors(a);     // b
    int db = GetSumOfProperDivisors(da);    // Should be a

    if (da != a && db == a)
    {
        return true;
    }

    return false;
}

int GetSumOfAmicableNumbers(int n)
{
    int sum = 0;

    for (int i=1; i<n; ++i)
    {
        if (IsAmicableNumber(i))
        {
            sum += i;
        }
    }

    return sum;
}

int main()
{
    cout << GetSumOfAmicableNumbers(10000) << endl;

    return 0;
}

