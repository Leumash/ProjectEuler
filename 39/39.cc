/*
If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, there are exactly three solutions for p = 120.

{20,48,52}, {24,45,51}, {30,40,50}

For which value of p ≤ 1000, is the number of solutions maximised?
*/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>

using namespace std;

set<int> GetSquares(int max)
{
    set<int> toReturn;

    for (int i=1; i<=max; ++i)
    {
        toReturn.insert(i * i);
    }

    return toReturn;
}

vector<int> GetNumberOfSolutionsForPerimeter(set<int> &squares, int maxPerimeter)
{
    vector<int> toReturn(maxPerimeter + 1, 0);

    for (auto i = squares.begin(); i != squares.end(); ++i)
    {
        int aSquared = *i;

        for (auto j = next(i, 1); j != squares.end(); ++j)
        {
            int bSquared = *j;
            int cSquared = aSquared + bSquared;

            if (squares.count(cSquared) > 0)
            {
                int perimeter = sqrt(aSquared) + sqrt(bSquared) + sqrt(cSquared);

                if (perimeter <= maxPerimeter)
                {
                    ++toReturn[perimeter];
                }
            }
        }
    }

    return toReturn;
}

int GetValueForMaxNumberOfSolutions(int perimeter)
{
    set<int> squares = GetSquares(perimeter / 2);

    vector<int> numberOfSolutionsForPerimeter =
        GetNumberOfSolutionsForPerimeter(squares, perimeter);

    int maxIndex = 0;
    int maxSolutions = 0;

    for (int i=0; i<numberOfSolutionsForPerimeter.size(); ++i)
    {
        if (numberOfSolutionsForPerimeter[i] > maxSolutions)
        {
            maxSolutions = numberOfSolutionsForPerimeter[i];
            maxIndex = i;
        }
    }

    return maxIndex;
}

int main()
{
    cout << GetValueForMaxNumberOfSolutions(1000) << endl;

    return 0;
}

