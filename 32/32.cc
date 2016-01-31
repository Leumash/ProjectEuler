/*
We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once; for example, the 5-digit number, 15234, is 1 through 5 pandigital.

The product 7254 is unusual, as the identity, 39 × 186 = 7254, containing multiplicand, multiplier, and product is 1 through 9 pandigital.

Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.

HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.
*/

#include <iostream>
#include <numeric>
#include <cstring>
#include <set>

using namespace std;

bool IsProductPandigitalNumber(int a, int b)
{
    int arr[10];

    memset(arr, 0, sizeof(int)*10);

    int c = a*b;

    while (c)
    {
        ++arr[c%10];
        c /=10;
    }

    while (b)
    {
        ++arr[b%10];
        b /=10;
    }

    while (a)
    {
        ++arr[a%10];
        a /=10;
    }

    if (arr[0] != 0)
    {
        return false;
    }

    for (int i=1; i<10; ++i)
    {
        if (arr[i] != 1)
        {
            return false;
        }
    }

    return true;
}

int GetSumOfAllProductPandigitalNumbers()
{
    set<int> productPandigitalNumbers;

    for (int a=1; a<100; ++a)
    {
        for (int b=a+1; b<10000; ++b)
        {
            if (IsProductPandigitalNumber(a, b))
            {
                productPandigitalNumbers.insert(a*b);
            }
        }
    }

    return accumulate(productPandigitalNumbers.begin(), productPandigitalNumbers.end(), 0);
}

int main()
{
    cout << GetSumOfAllProductPandigitalNumbers() << endl;

    return 0;
}

