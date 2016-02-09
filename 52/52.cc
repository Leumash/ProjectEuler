/*
It can be seen that the number, 125874, and its double, 251748, contain exactly the same digits, but in a different order.

Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, contain the same digits.
*/

#include <iostream>

using namespace std;

bool ContainsSameDigits(int a, int b)
{
    int digits[10] = {0};

    while (a)
    {
        ++digits[a % 10];

        a /= 10;
    }

    while (b)
    {
        --digits[b % 10];

        b /= 10;
    }

    for (int i=0; i<10; ++i)
    {
        if (digits[i] != 0)
        {
            return false;
        }
    }

    return true;
}

int GetAnswer(int multiples)
{
    for (int i=1; ; ++i)
    {
        bool found = true;

        for (int multiplier=2; multiplier<=multiples; ++multiplier)
        {
            if (!ContainsSameDigits(i, i * multiplier))
            {
                found = false;

                break;
            }
        }

        if (found)
        {
            return i;
        }
    }
}

int main()
{
    cout << GetAnswer(6) << endl;

    return 0;
}

