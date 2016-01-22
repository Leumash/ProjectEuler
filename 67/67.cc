#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#define LEVELS_OF_TRIANGLE_FILE 100

using namespace std;

void FillTriangle(vector< vector<int> > &triangle)
{
    fstream fin("triangle.txt");

    for (int row=0; row<LEVELS_OF_TRIANGLE_FILE; ++row)
    {
        triangle.push_back(vector<int>());

        for (int col=0; col<row+1; ++col)
        {
            int temp;
            fin >> temp;
            triangle[row].push_back(temp);
        }
    }
}

int MakeDecisionToAdd(vector< vector<int> > triangle, int row, int col)
{
    int topLeft = 0;
    int topRight = 0;

    if (col > 0)
    {
        topLeft = triangle[row-1][col-1];
    }

    if (col < triangle[row-1].size())
    {
        topRight = triangle[row-1][col];
    }

    return max(topLeft, topRight);
}

void FillMaximumPathSumTriangle(vector< vector<int> > triangle,
                                vector< vector<int> > &maximumPathSumTriangle)
{
    // First element. This path must be traversed
    maximumPathSumTriangle.push_back(vector<int>());
    maximumPathSumTriangle[0].push_back(triangle[0][0]);

    for (int row=1; row<LEVELS_OF_TRIANGLE_FILE; ++row)
    {
        maximumPathSumTriangle.push_back(vector<int>());

        for (int col=0; col<row+1; ++col)
        {
            int toAdd = MakeDecisionToAdd(maximumPathSumTriangle, row, col);
            maximumPathSumTriangle[row].push_back(triangle[row][col] + toAdd);
        }
    }
}

int GetMaximumPathSum(vector< vector<int> > triangle)
{
    return max_element(triangle[LEVELS_OF_TRIANGLE_FILE - 1].begin(),
                        triangle[LEVELS_OF_TRIANGLE_FILE - 1].end())[0];
}

int MaximumPathSumII()
{
    vector< vector<int> > triangle;
    vector< vector<int> > maximumPathSumTriangle;

    FillTriangle(triangle);

    FillMaximumPathSumTriangle(triangle, maximumPathSumTriangle);

    return GetMaximumPathSum(maximumPathSumTriangle);
}

int main()
{
    cout << MaximumPathSumII() << endl;
}

