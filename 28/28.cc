/*
Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:

21 22 23 24 25
20  7  8  9 10
19  6  1  2 11
18  5  4  3 12
17 16 15 14 13

It can be verified that the sum of the numbers on the diagonals is 101.

What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?
*/

/*

1x1                         1                                       (1 - 1) / 8 = 0
           1

3x3                         (1x1) + 3 + 5 + 7 + 9           +2      (9-1) / 8 = 1
         7 8 9              x + (x+2) + (x+4) + (x+6)
         6 1 2
         5 4 3

5x5                         (3x3) + 13 + 17 + 21 + 25       +4      (25-1) / 8 = 3
    21 22 23 24 25          
    20  7  8  9 10
    19  6  1  2 11
    18  5  4  3 12
    17 16 15 14 13

7x7                         (5x5) + 31 + 37 + 43 + 49       +6      (49-1) / 8 = 6 81

43 44 45 46 47 48 49
42 21 22 23 24 25 26
41 20  7  8  9 10 27
40 19  6  1  2 11 28
39 18  5  4  3 12 29
38 17 16 15 14 13 30
37 36 35 34 33 32 31

n * n + n * n - (n - 1) + n*n - 2 *(n-1) + n*n - 3* (n-1)
4 * n*n - 6 * (n-1)

4n^2 - 6n - 6

Sum_3^n n+=2 4n^2 - 6n - 6

*/

/*
a1 = 1

a2 = 3
a3 = 5
a4 = 7
a5 = 9

a6 = 13
a7 = 17
a8 = 21
a9 = 25

a10 = a31
*/

// func(n) 1 = 0, 2-5 = 2, 6-9 = 3, 10-13 = 4
// floor((n - 1)/4) - 1

// A_n = A_{n-1} + 2 * func(n)

// 1 + 2*N*(13+15*N+8*N*N)/3

#include <iostream>

using namespace std;

int GetSumOfDiagonals(int targetMatrixN)
{
    int sum = 1;
    int additive = 2;
    int current = 1;

    for (int currentMatrixN = 3; currentMatrixN <= targetMatrixN; currentMatrixN += 2)
    {
        for (int i=0; i<4; ++i)
        {
            current += additive;

            sum += current;
        }

        additive += 2;
    }

    return sum;
}

int GetGalvaBart(int n)
{
    n = (n-1) / 2;
    return 1 + 2 * n * (13 + 15 * n + 8 * n * n) / 3;
}

int main()
{
    cout << GetGalvaBart(1001) << endl;
    //cout << GetSumOfDiagonals(1001) << endl;

    return 0;
}

