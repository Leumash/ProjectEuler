/*
In the following equation x, y, and n are positive integers.

    1   1   1
    - + - = -
    x   y   n

For n = 4 there are exactly three distinct solutions:

    1    1   1
    - + -- = -
    5   20   4

    1    1   1
    - + -- = -
    6   12   4

    1   1   1
    - + - = -
    8   8   4

What is the least value of n for which the number of distinct solutions exceeds one-thousand?

NOTE: This problem is an easier version of Problem 110; it is strongly advised that you solve this one first.
*/

/*

f(n) = # of factors of n

*/

/*

x > n
x = 2n

n checks for brute force


Brute force:

Finding distinct solutions has a runtime of O(n)
Finding a specific distinct solution has a runtime of O(n^2)

Optimal Solution:
Total has to be O(n)
Find a distinct solution for a given n, O(1)

*/

/*

x = y = n * 2 is always a solution

*/

/*

1      1
- = -------
n    a * b

*/

/*
     x * y
n = -------
     x + y

n    x * y
- = -------
1    x + y


*/

/*

    1   1   1
    - + - = -
    x   y   n

    1   1     1
    - - - = - -
    x   n     y

y = n (1 + y/x)

x > n
y > n
x <= y
x | y   -> y = a * x

*/

/*

Prime numbers have 2 solutions
Square of a prime has 3 soltuions
Composite of 2 distinct primes has 5 soltuions

12 = 2 ^ 2 * 3
18 = 2 * 3 ^ 2
both have 8 solutions

prime cubed has 4 solutions

prime ^ 4 5 solutions

prime ^ n has n + 1 solutions

composite * p, where p is already in composite has + 3 solutions
composite * p, where p is NOT in composite has + 5 solutions


Primes and Composites

Starting with Prime:
Prime                   2 solutions
Prime * Prime           5 solutions
Prime * Prime * Prime   14 solutions
Prime ^ n               n + 1 soltions

*/

#include <iostream>
#include <cmath>
#include <unordered_map>

#define EPSILON 0.00000000000000001

using namespace std;

unordered_map<int,int> GetPrimeFactors(int n)
{
    unordered_map<int,int> primeFactors;

    for (int i=2; n > 1; ++i)
    {
        while (n % i == 0)
        {
            if (primeFactors.count(i) == 0)
            {
                primeFactors[i] = 0;
            }

            ++primeFactors[i];
            n /= i;
        }
    }

    return primeFactors;
}

int GetNumberOfDivisorsOfNSquared(int n)
{
    // The number of divisors is how many different ways there are to combine the prime factors

    unordered_map<int,int> primeFactors = GetPrimeFactors(n);

    for (auto &primeFactor : primeFactors)
    {
        primeFactor.second *= 2;
    }

    int numberOfDivisors = 1;

    for (const auto &primeFactor : primeFactors)
    {
        numberOfDivisors *= primeFactor.second + 1;
    }

    return numberOfDivisors;
}

int GetNumberOfDistinctSolutions(int n)
{
    int numberOfDivisors = GetNumberOfDivisorsOfNSquared(n);

    return (numberOfDivisors + 1) / 2;
}

int GetLeastValueWhereDistinctSolutionsExceeds(int numberOfDistinctSolutions)
{
    int maximumN = 2 * 3 * 5 * 7 * 11 * 13 * 17;
    int minimumN = maximumN;

    for (int two=0; ; ++two)
    {
        int a = pow(2, two);

        if (a >= maximumN)
        {
            break;
        }

        for (int three=0; three <= two; ++three)
        {
            int b = pow(3, three) * a;

            if (b >= maximumN)
            {
                break;
            }

            for (int five=0; five <= three; ++five)
            {
                int c = pow(5, five) * b;

                if (c >= maximumN)
                {
                    break;
                }


                for (int seven=0; seven <= five; ++seven)
                {
                    int d = pow(7, seven) * c;

                    if (d >= maximumN)
                    {
                        break;
                    }


                    for (int eleven=0; eleven <= seven; ++eleven)
                    {
                        int e = pow(11, eleven) * d;

                        if (e >= maximumN)
                        {
                            break;
                        }


                        for (int thirteen=0; thirteen <= eleven; ++thirteen)
                        {
                            int f = pow(13, thirteen) * e;

                            if (f >= maximumN)
                            {
                                break;
                            }

                            for (int seventeen=0; seventeen <= thirteen; ++seventeen)
                            {
                                int n = pow(17, seventeen) * f;

                                if (n >= maximumN)
                                {
                                    break;
                                }

                                int solutions = GetNumberOfDistinctSolutions(n);

                                if (solutions > numberOfDistinctSolutions)
                                {
                                    minimumN = min(minimumN, n);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return minimumN;
}

int main()
{
    cout << GetLeastValueWhereDistinctSolutionsExceeds(1000) << endl;

    return 0;
}

