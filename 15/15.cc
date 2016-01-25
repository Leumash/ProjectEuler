/*
Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.

How many such routes are there through a 20×20 grid?
*/

#include <iostream>
#include <cstring>

using namespace std;

void ZeroOutMatrix(long long matrix[21][21])
{
    memset(matrix, 0, sizeof(matrix[0][0]) * 21 * 21);
}

void FillTopRow(long long matrix[21][21])
{
    for (int i=0; i<21; ++i)
    {
        matrix[0][i] = 1;
    }
}

void FillLeftColumn(long long matrix[21][21])
{
    for (int i=0; i<21; ++i)
    {
        matrix[i][0] = 1;
    }
}

void CalculateMatrix(long long matrix[21][21])
{
    for (int row=1; row<21; ++row)
    {
        for (int col=1; col<21; ++col)
        {
            matrix[row][col] = matrix[row-1][col] + matrix[row][col-1];
        }
    }
}

long long GetNumberOfRoutes()
{
    long long matrix[21][21];

    ZeroOutMatrix(matrix);

    FillTopRow(matrix);

    FillLeftColumn(matrix);

    CalculateMatrix(matrix);

    return matrix[20][20];
}

int main()
{
    cout << GetNumberOfRoutes() << endl;
}

