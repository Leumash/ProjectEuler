/*
The cube, 41063625 (345 ^ 3), can be permuted to produce two other cubes: 56623104 (384 ^ 3) and 66430125 (405 ^ 3). In fact, 41063625 is the smallest cube which has exactly three permutations of its digits which are also cube.

Find the smallest cube for which exactly five permutations of its digits are cube.
*/

#include <iostream>
#include <unordered_map>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

multiset<int> GetDigits(long long cubed)
{
    multiset<int> toReturn;

    while (cubed)
    {
        toReturn.insert(cubed %10);
        cubed /= 10;
    }

    return toReturn;
}

vector<int> GetAnswers(map< multiset<int>, vector<int> > &permutationToCube, int permutations)
{
    vector<int> toReturn;

    for (auto &mit : permutationToCube)
    {
        if (mit.second.size() == permutations)
        {
            toReturn.push_back(*min_element(mit.second.begin(), mit.second.end()));
        }
    }

    return toReturn;
}

void AddNumberToMap(map< multiset<int>, vector<int> > &permutationToCube, int n)
{
    long long cubed = pow(n, 3);
    multiset<int> toAdd = GetDigits(cubed);

    if (permutationToCube.count(toAdd) == 0)
    {
        permutationToCube[toAdd] = vector<int>(1, n);
    }
    else
    {
        permutationToCube[toAdd].push_back(n);
    }
}

long long GetSmallestCube(int permutations)
{

    map< multiset<int>, vector<int> > permutationToCube;

    int i = 1;
    long long cubed = 1;
    int previousCubedDigits = 1;

    while (true)
    {
        int cubedDigits = floor(log10(cubed)) + 1;

        if (cubedDigits > previousCubedDigits)
        {
            vector<int> answers = GetAnswers(permutationToCube, permutations);

            if (answers.size() > 0)
            {
                return pow(*min_element(answers.begin(), answers.end()), 3);
            }

            permutationToCube.empty();

            previousCubedDigits = cubedDigits;
        }

        AddNumberToMap(permutationToCube, i);

        ++i;
        cubed = pow(i, 3);
    }
}

int main()
{
    cout << GetSmallestCube(5) << endl;

    return 0;
}

