/*
Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:

1634 = 1^4 + 6^4 + 3^4 + 4^4
8208 = 8^4 + 2^4 + 0^4 + 8^4
9474 = 9^4 + 4^4 + 7^4 + 4^4
As 1 = 1^4 is not a sum it is not included.

The sum of these numbers is 1634 + 8208 + 9474 = 19316.

Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.
*/

/*
We care about the number of digits


                        number of digits
______________________|________1_________2________3_______4_______5_______6
 max value possible   |     6561     13122    19683   26244   32805   39366

 Limit : 40000



                        number of digits
______________________|__________1__________2__________3_________4_________5_________6
 max value possible   |      59049     118098     177147    236196    295245    354294

 Limit : 400000

*/

#include <iostream>
#include <cmath>

using namespace std;

int GetLimit(int power)
{
    int digits = 1;
    int nineToPower = pow(9, power);

    while (nineToPower * digits > pow(10, digits))
    {
        ++digits;
    }

    return nineToPower * digits;
}

bool IsSumOfPowersOfDigits(int n, int power)
{
    int sum = 0;
    int temp = n;

    while (temp)
    {
        sum += pow(temp % 10, power);

        temp /= 10;
    }

    return sum == n;
}

int GetSum(int power)
{
    int sum = 0;
    int limit = GetLimit(power);

    for (int i=10; i<limit; ++i)
    {
        if (IsSumOfPowersOfDigits(i, power))
        {
            sum += i;
        }
    }

    return sum;
}

int main()
{
    cout << GetSum(5) << endl;

    return 0;
}

