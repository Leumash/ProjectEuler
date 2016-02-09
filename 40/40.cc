/*
An irrational decimal fraction is created by concatenating the positive integers:

0.123456789101112131415161718192021...
             ^

It can be seen that the 12th digit of the fractional part is 1.

If dn represents the nth digit of the fractional part, find the value of the following expression.

d1 × d10 × d100 × d1000 × d10000 × d100000 × d1000000
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> GetDigits(int n)
{
    vector<int> toReturn;

    while (n)
    {
        toReturn.push_back(n % 10);

        n /= 10;
    }

    reverse(toReturn.begin(), toReturn.end());

    return toReturn;
}

int GetNumberAtPosition(int pos)
{
    int currentPos = 0;
    for (int i=1; ; ++i)
    {
        vector<int> digits = GetDigits(i);

        for (int j=0; j<digits.size(); ++j)
        {
            ++currentPos;

            if (currentPos == pos)
            {
                return digits[j];
            }
        }
    }
}

int GetAnswer(int digitsToCheck)
{
    int answer = 1;

    for (int pos=1; pos <= pow(10,digitsToCheck); pos *= 10)
    {
        int num = GetNumberAtPosition(pos);

        answer *= num;
    }

    return answer;
}

int main()
{
    cout << GetAnswer(6) << endl;

    return 0;
}

