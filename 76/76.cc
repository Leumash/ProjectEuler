/*
It is possible to write five as a sum in exactly six different ways:

4 + 1
3 + 2
3 + 1 + 1
2 + 2 + 1
2 + 1 + 1 + 1
1 + 1 + 1 + 1 + 1

How many different ways can one hundred be written as a sum of at least two positive integers?
*/

#include <iostream>

using namespace std;

int GetWaysToGetSumOfAtLeastTwoPositiveIntegers(int n)
{
    int arr[n+1] = {0};

    arr[0] = 1;

    for (int i=1; i<n; ++i)
    {
        for (int j=0; i+j < n+1; ++j)
        {
            arr[i+j] += arr[j];
        }
    }

    return arr[n];
}

int main()
{
    cout << GetWaysToGetSumOfAtLeastTwoPositiveIntegers(100) << endl;

    return 0;
}

