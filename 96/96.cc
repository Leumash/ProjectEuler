/*
Su Doku (Japanese meaning number place) is the name given to a popular puzzle concept. Its origin is unclear, but credit must be attributed to Leonhard Euler who invented a similar, and much more difficult, puzzle idea called Latin Squares. The objective of Su Doku puzzles, however, is to replace the blanks (or zeros) in a 9 by 9 grid in such that each row, column, and 3 by 3 box contains each of the digits 1 to 9. Below is an example of a typical starting puzzle grid and its solution grid.

        0 0 3  0 2 0  6 0 0     4 8 3  9 2 1  6 5 7
        9 0 0  3 0 5  0 0 1     9 6 7  3 4 5  8 2 1
        0 0 1  8 0 6  4 0 0     2 5 1  8 7 6  4 9 3

        0 0 8  1 0 2  9 0 0     5 4 8  1 3 2  9 7 6
        7 0 0  0 0 0  0 0 8     7 2 9  5 6 4  1 3 8
        0 0 6  7 0 8  2 0 0     1 3 6  7 9 8  2 4 5

        0 0 2  6 0 9  5 0 0     3 7 2  6 8 9  5 1 4
        8 0 0  2 0 3  0 0 9     8 1 4  2 5 3  7 6 9
        0 0 5  0 1 0  3 0 0     6 9 5  4 1 7  3 8 2

A well constructed Su Doku puzzle has a unique solution and can be solved by logic, although it may be necessary to employ "guess and test" methods in order to eliminate options (there is much contested opinion over this). The complexity of the search determines the difficulty of the puzzle; the example above is considered easy because it can be solved by straight forward direct deduction.

The 6K text file, sudoku.txt (right click and 'Save Link/Target As...'), contains fifty different Su Doku puzzles ranging in difficulty, but all with unique solutions (the first puzzle in the file is the example above).

By solving all fifty puzzles find the sum of the 3-digit numbers found in the top left corner of each solution grid; for example, 483 is the 3-digit number found in the top left corner of the solution grid above.
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <unordered_set>
#include <limits>
#include <algorithm>

#define SIZE_OF_ROW 3
#define SIZE_OF_COLUMN 3

using namespace std;

typedef vector<vector<int>> boardType;
typedef vector<vector<vector<int>>> possibilityType;

vector<vector<vector<int>>> GetSudokuGrids()
{
    int gridNumber;
    string gridText;
    ifstream fin("sudoku.txt");
    vector<vector<vector<int>>> sudokuGrids;

    while (fin >> gridText >> gridNumber)
    {
        vector<vector<int>> sudokuGrid(SIZE_OF_ROW * SIZE_OF_COLUMN, vector<int>(SIZE_OF_ROW * SIZE_OF_COLUMN));

        for (int i=0; i<SIZE_OF_ROW * SIZE_OF_COLUMN; ++i)
        {
            for (int j=0; j<SIZE_OF_ROW * SIZE_OF_COLUMN; ++j)
            {
                char temp;

                fin >> temp;

                sudokuGrid[i][j] = temp - '0';
            }
        }

        sudokuGrids.push_back(sudokuGrid);
    }

    return sudokuGrids;
}

int GetTopLeftCornerValue(const vector<vector<int>> &sudokuGrid)
{
    int value;
    stringstream ss;

    ss << sudokuGrid[0][0] << sudokuGrid[0][1] << sudokuGrid[0][2];

    ss >> value;

    return value;
}

bool GetUnFilledCell(const boardType &sudokuGrid, int &rowPos, int &colPos)
{
    for (int row = 0; row<SIZE_OF_ROW * SIZE_OF_COLUMN; ++row)
    {
        for (int col=0; col<SIZE_OF_ROW * SIZE_OF_COLUMN; ++col)
        {
            if (sudokuGrid[row][col] == 0)
            {
                rowPos = row;
                colPos = col;

                return true;
            }
        }
    }

    return false;
}

possibilityType MakeInitialPossibilites()
{
    possibilityType toReturn(SIZE_OF_ROW * SIZE_OF_COLUMN, vector<vector<int>>(SIZE_OF_ROW * SIZE_OF_COLUMN));

    for (int row=0; row<SIZE_OF_ROW * SIZE_OF_COLUMN; ++row)
    {
        for (int col=0; col<SIZE_OF_ROW * SIZE_OF_COLUMN; ++col)
        {
            for (int i=1; i<=SIZE_OF_ROW * SIZE_OF_COLUMN; ++i)
            {
                toReturn[row][col].push_back(i);
            }
        }
    }

    return toReturn;
}

possibilityType GetPossibilites(const boardType &sudokuGrid)
{
    possibilityType possibilities = MakeInitialPossibilites();

    for (int row=0; row<SIZE_OF_ROW * SIZE_OF_COLUMN; ++row)
    {
        for (int col=0; col<SIZE_OF_ROW * SIZE_OF_COLUMN; ++col)
        {
            int notAPossbility = sudokuGrid[row][col];

            // Erase from Rows
            for (int rowPrime=0; rowPrime<SIZE_OF_ROW * SIZE_OF_COLUMN; ++rowPrime)
            {
                possibilities[rowPrime][col].erase(remove(possibilities[rowPrime][col].begin(), possibilities[rowPrime][col].end(), notAPossbility), possibilities[rowPrime][col].end());
            }

            // Erase from Cols
            for (int colPrime=0; colPrime<SIZE_OF_ROW * SIZE_OF_COLUMN; ++colPrime)
            {
                possibilities[row][colPrime].erase(remove(possibilities[row][colPrime].begin(), possibilities[row][colPrime].end(), notAPossbility), possibilities[row][colPrime].end());
            }

            // Erase from Square
            for (int rowPrime = row - (row % SIZE_OF_ROW); rowPrime<SIZE_OF_ROW + row - (row % SIZE_OF_ROW) ; ++rowPrime)
            {
                for (int colPrime = col - (col % SIZE_OF_COLUMN); colPrime<SIZE_OF_COLUMN + col - (col % SIZE_OF_COLUMN); ++colPrime)
                {
                    possibilities[rowPrime][colPrime].erase(remove(possibilities[rowPrime][colPrime].begin(), possibilities[rowPrime][colPrime].end(), notAPossbility), possibilities[rowPrime][colPrime].end());
                }
            }
        }
    }

    return possibilities;
}

void RemovePossibilites(const possibilityType &oldPossib, possibilityType &newPossib, int changedTo, int row, int col)
{
    newPossib = oldPossib;

    // Remove from Row
    for (int rowPos=0; rowPos<SIZE_OF_ROW * SIZE_OF_COLUMN; ++rowPos)
    {
        newPossib[rowPos][col].erase(remove(newPossib[rowPos][col].begin(), newPossib[rowPos][col].end(), changedTo), newPossib[rowPos][col].end());
    }

    // Remove from Col
    for (int colPos=0; colPos<SIZE_OF_ROW * SIZE_OF_COLUMN; ++colPos)
    {
        newPossib[row][colPos].erase(remove(newPossib[row][colPos].begin(), newPossib[row][colPos].end(), changedTo), newPossib[row][colPos].end());
    }

    // Erase from Square
    for (int rowPrime = row - (row % SIZE_OF_ROW); rowPrime<SIZE_OF_ROW + row - (row % SIZE_OF_ROW) ; ++rowPrime)
    {
        for (int colPrime = col - (col % SIZE_OF_COLUMN); colPrime<SIZE_OF_COLUMN + col - (col % SIZE_OF_COLUMN); ++colPrime)
        {
            newPossib[rowPrime][colPrime].erase(remove(newPossib[rowPrime][colPrime].begin(), newPossib[rowPrime][colPrime].end(), changedTo), newPossib[rowPrime][colPrime].end());
        }
    }
}

bool SolveRecursive(boardType sudokuGrid, possibilityType possibilities, boardType &solution)
{
    int row, col;

    unsigned int numberOfPossbilities = numeric_limits<int>::max();

    for (int rowPos=0; rowPos<SIZE_OF_ROW * SIZE_OF_COLUMN; ++rowPos)
    {
        for (int colPos=0; colPos<SIZE_OF_ROW * SIZE_OF_COLUMN; ++colPos)
        {
            if (sudokuGrid[rowPos][colPos] == 0
                && possibilities[rowPos][colPos].size() < numberOfPossbilities)
            {
                numberOfPossbilities = possibilities[rowPos][colPos].size();

                row = rowPos;
                col = colPos;
            }
        }
    }

    if (numberOfPossbilities == 0)
    {
        return false;
    }

    if (numberOfPossbilities == numeric_limits<int>::max())
    {
        solution = sudokuGrid;

        return true;
    }

    for (int possibility : possibilities[row][col])
    {
        sudokuGrid[row][col] = possibility;

        possibilityType newPossibilities;

        RemovePossibilites(possibilities, newPossibilities, possibility, row, col);

        if (SolveRecursive(sudokuGrid, newPossibilities, solution))
        {
            return true;
        }
    }

    return false;
}

vector<vector<int>> SolveWithBruteForce(vector<vector<int>> sudokuGrid)
{
    possibilityType possbilities = GetPossibilites(sudokuGrid);

    if (!SolveRecursive(sudokuGrid, possbilities, sudokuGrid))
    {
        cout << "No solution?" << endl;
        exit (1);
    }

    return sudokuGrid;
}

vector<vector<int>> SolveSudokuGrid(vector<vector<int>> &sudokuGrid)
{
    sudokuGrid = SolveWithBruteForce(sudokuGrid);

    return sudokuGrid;
}

int GetSumOfTopLeftCorners()
{
    vector<vector<vector<int>>> sudokuGrids = GetSudokuGrids();
    
    for (auto &sudokuGrid : sudokuGrids)
    {
        sudokuGrid = SolveSudokuGrid(sudokuGrid);
    }

    int sum = 0;

    for (const auto &sudokuGrid : sudokuGrids)
    {
        sum += GetTopLeftCornerValue(sudokuGrid);
    }

    return sum;
}

int main()
{
    cout << GetSumOfTopLeftCorners() << endl;

    return 0;
}

