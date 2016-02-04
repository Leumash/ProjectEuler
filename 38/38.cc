/*
Take the number 192 and multiply it by each of 1, 2, and 3:

192 × 1 = 192
192 × 2 = 384
192 × 3 = 576
By concatenating each product we get the 1 to 9 pandigital, 192384576. We will call 192384576 the concatenated product of 192 and (1,2,3)

The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4, and 5, giving the pandigital, 918273645, which is the concatenated product of 9 and (1,2,3,4,5).

What is the largest 1 to 9 pandigital 9-digit number that can be formed as the concatenated product of an integer with (1,2, ... , n) where n > 1?
*/

/*
987654321

987654312

Generate smaller and smaller pandigital numbers and test if it is a concatenated product.

There are 9! possible combinations: 362880

2 Problems then, how to generate decreasing pandigital numbers, how to test if concatenated product.
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

vector<int> GetDecreasingPandigitalNumbers()
{
    vector<int> toReturn;
    vector<int> permutations;

    permutations.push_back(9);
    permutations.push_back(8);
    permutations.push_back(7);
    permutations.push_back(6);
    permutations.push_back(5);
    permutations.push_back(4);
    permutations.push_back(3);
    permutations.push_back(2);
    permutations.push_back(1);

    do
    {
        stringstream ss;

        for (int num : permutations)
        {
            ss << num;
        }

        int toInsert;

        ss >> toInsert;

        toReturn.push_back(toInsert);

    } while (prev_permutation(permutations.begin(), permutations.end()));

    return toReturn;
}

bool IsConcatenatedProduct(int n)
{
    //int frontNumber = n / 100000000;
    //int frontNumber = n / (int) pow(10,8);
}

int GetLargestNineDigitalPandigitalNumber()
{
    vector<int> decreasingPandigitalNumbers = GetDecreasingPandigitalNumbers();

    for (int pandigitalNumber : decreasingPandigitalNumbers)
    {
        if (IsConcatenatedProduct(pandigitalNumber))
        {
            return pandigitalNumber;
        }
    }

    return -1;
}

int main()
{
    cout << GetLargestNineDigitalPandigitalNumber() << endl;

    return 0;
}

