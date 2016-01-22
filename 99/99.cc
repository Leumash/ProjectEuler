#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

vector<double> GetIntermediateValues()
{
    fstream fin("base_exp.txt");
    vector<double> toReturn;
    int base, exp;

    for (int i=0; i<1000; ++i)
    {
        fin >> base >> exp;

        toReturn.push_back(log10(base) * exp);
    }

    return toReturn;
}

int GetLargest()
{
    vector<double> intermediateValues = GetIntermediateValues();

    double max = 0;
    int pos = 0;

    for (int i=0; i<intermediateValues.size(); ++i)
    {
        if (max < intermediateValues[i])
        {
            max = intermediateValues[i];
            pos = i;
        }
    }

    return pos + 1;
}

int main()
{
    cout << "The largest line is: " << GetLargest() << endl;
}

