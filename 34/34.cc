/*
145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.

Find the sum of all numbers which are equal to the sum of the factorial of their digits.

Note: as 1! = 1 and 2! = 2 are not sums they are not included.
*/

#include <iostream>

using namespace std;

int Factorial(int n)
{
    int factorial[10] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880 };

    return factorial[n];
}

int GetSumOfFactorialOfItsDigits(int n)
{
    if (n == 0)
    {
        return 1;
    }

    int sum = 0;

    while (n != 0)
    {
        sum += Factorial(n % 10);
        n /= 10;
    }

    return sum;
}

bool IsSumOfDigits(int n)
{
    int sumOfFactorialOfItsDigits = GetSumOfFactorialOfItsDigits(n);

    return sumOfFactorialOfItsDigits == n;
}

int GetSumOfAllNumbersThatEqualSumOfFactorialOfDigits()
{
    int sum = 0;

    for (int i=10; i<3000000; ++i)
    {
        if (IsSumOfDigits(i))
        {
            sum += i;
        }
    }

    return sum;
}

int main()
{
    cout << GetSumOfAllNumbersThatEqualSumOfFactorialOfDigits() << endl;
    return 0;
}

