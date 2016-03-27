/*
The smallest number expressible as the sum of a prime square, prime cube, and prime fourth power is 28. In fact, there are exactly four numbers below fifty that can be expressed in such a way:

28 = 2^2 + 2^3 + 2^4
33 = 3^2 + 2^3 + 2^4
49 = 5^2 + 2^3 + 2^4
47 = 2^2 + 3^3 + 2^4

How many numbers below fifty million can be expressed as the sum of a prime square, prime cube, and prime fourth power?
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool IsPrime(int n)
{
    if (n <= 1)
    {
        return false;
    }

    if (n == 2)
    {
        return true;
    }

    if (n % 2 == 0)
    {
        return false;
    }

    for (int i=3; i <= sqrt(n); i += 2)
    {
        if (n % i == 0)
        {
            return false;
        }
    }

    return true;
}

vector<int> GetPrimeToPowerLessThan(int power, int limit)
{
    vector<int> primesToPower;

    primesToPower.push_back(pow(2,power));

    for (int i=3; ; i += 2)
    {
        if (IsPrime(i))
        {
            int primeToPower = pow(i, power);

            if (primeToPower < limit)
            {
                primesToPower.push_back(primeToPower);
            }
            else
            {
                break;
            }
        }
    }

    return primesToPower;
}

int GetNumbersThatCanBeExpressedAsSumOfPrimeSquarePrimeCubeAndPrimeFourthPower(int limit)
{
    vector<int> primeSquares = GetPrimeToPowerLessThan(2, limit);
    vector<int> primeCubes = GetPrimeToPowerLessThan(3, limit);
    vector<int> primeFourths = GetPrimeToPowerLessThan(4, limit);

    int count = 0;
    vector<bool> numbersThatCanBeExpressedAsSum(limit, false);

    for (int primeFourth : primeFourths)
    {
        for (int primeCube : primeCubes)
        {
            if (primeFourth + primeCube >= limit)
            {
                break;
            }

            for (int primeSquare : primeSquares)
            {
                int sum = primeFourth + primeCube + primeSquare;
                if (sum >= limit)
                {
                    break;
                }

                if (numbersThatCanBeExpressedAsSum[sum] == false)
                {
                    ++count;
                    numbersThatCanBeExpressedAsSum[sum] = true;
                }
            }
        }
    }

    return count;
}

int main()
{
    cout << GetNumbersThatCanBeExpressedAsSumOfPrimeSquarePrimeCubeAndPrimeFourthPower(50000000) << endl;

    return 0;
}

