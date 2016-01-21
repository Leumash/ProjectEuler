#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>

#define MATRIX_SIZE 80

using namespace std;

void FillMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE])
{
    ifstream fin("matrix.txt");

    for (int row=0; row<MATRIX_SIZE; ++row)
    {
        for (int col=0; col<MATRIX_SIZE; ++col)
        {
            int temp;
            fin >> temp;
            matrix[col][row] = temp;
        }
    }
}

void ZeroOutMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE])
{
    fill(matrix[0], matrix[0] + MATRIX_SIZE * MATRIX_SIZE, 0);
}

void FillTopRow(int matrix[MATRIX_SIZE][MATRIX_SIZE],
    int shortestPathMatrix[MATRIX_SIZE][MATRIX_SIZE])
{
    shortestPathMatrix[0][0] = matrix[0][0];

    for (int i=1; i<MATRIX_SIZE; ++i)
    {
        shortestPathMatrix[0][i] = shortestPathMatrix[0][i-1] + matrix[0][i];
    }
}

void FillLeftColumn(int matrix[MATRIX_SIZE][MATRIX_SIZE],
    int shortestPathMatrix[MATRIX_SIZE][MATRIX_SIZE])
{
    shortestPathMatrix[0][0] = matrix[0][0];

    for (int i=1; i<MATRIX_SIZE; ++i)
    {
        shortestPathMatrix[i][0] = shortestPathMatrix[i-1][0] + matrix[i][0];
    }
}

int GetShortestPath(int matrix[MATRIX_SIZE][MATRIX_SIZE])
{
    int shortestPathMatrix[MATRIX_SIZE][MATRIX_SIZE];

    ZeroOutMatrix(shortestPathMatrix);

    FillTopRow(matrix, shortestPathMatrix);

    FillLeftColumn(matrix, shortestPathMatrix);

    for (int row=1; row<MATRIX_SIZE; ++row)
    {
        for (int col=1; col<MATRIX_SIZE; ++col)
        {
            int minimum = min(  shortestPathMatrix[col-1][row],
                                shortestPathMatrix[col][row-1]);
            shortestPathMatrix[col][row] = minimum + matrix[col][row];
        }
    }

    return shortestPathMatrix[MATRIX_SIZE-1][MATRIX_SIZE-1];
}

int main()
{
    int matrix[MATRIX_SIZE][MATRIX_SIZE];

    FillMatrix(matrix);

    cout << GetShortestPath(matrix) << endl;
}

