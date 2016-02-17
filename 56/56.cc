/*
A googol (10^100) is a massive number: one followed by one-hundred zeros; 100^100 is almost unimaginably large: one followed by two-hundred zeros. Despite their size, the sum of the digits in each number is only 1.

Considering natural numbers of the form, a^b, where a, b < 100, what is the maximum digital sum?
*/

#include <iostream>
#include <vector>

using namespace std;

int GetSum(vector<int> &num)
{
    int sum = 0;

    for (int n : num)
    {
        sum += n;
    }

    return sum;
}

vector<int> ConvertToVector(int num)
{
    if (num == 0)
    {
        return vector<int>(1,0);
    }

    vector<int> toReturn;

    while (num)
    {
        toReturn.push_back(num % 10);

        num /= 10;
    }

    return toReturn;
}

vector<int> GetAddition(vector< vector<int> > &toAdd)
{
    vector<int> toReturn;

    for (vector<int> &num : toAdd)
    {
        for (int i=0; i<num.size(); ++i)
        {
            if (toReturn.size() <= i)
            {
                toReturn.push_back(0);
            }

            toReturn[i] += num[i];
        }
    }

    toReturn.push_back(0);

    for (int i=0; i<toReturn.size(); ++i)
    {
        while (toReturn[i] > 9)
        {
            toReturn[i] -= 10;
            ++toReturn[i+1];
        }
    }

    if (toReturn[toReturn.size()-1] == 0)
    {
        toReturn.pop_back();
    }

    return toReturn;
}

vector<int> Multiply(vector<int> &a, vector<int> &b)
{
    vector< vector<int> > total;

    for (int i=0; i<b.size(); ++i)
    {
        vector<int> toAdd(i,0);

        for (int j=0; j<a.size(); ++j)
        {
            toAdd.push_back(b[i] * a[j]);
        }

        total.push_back(toAdd);
    }

    return GetAddition(total);
}

vector<int> pow(int base, int exponent)
{
    vector<int> baseVector = ConvertToVector(base);
    vector<int> toReturn = baseVector;


    for (int i=0; i<exponent; ++i)
    {
        toReturn = Multiply(toReturn, baseVector);
    }

    return toReturn;
}

int GetMaximumDigitalSum()
{
    int max = 0;

    for (int base=10; base<100; ++base)
    {
        for (int exponent=1; exponent<100; ++exponent)
        {
            vector<int> num = pow(base, exponent);

            int sum = GetSum(num);

            if (sum > max)
            {
                max = sum;
            }
        }
    }

    return max;
}

int main()
{
    cout << GetMaximumDigitalSum() << endl;

    return 0;
}

