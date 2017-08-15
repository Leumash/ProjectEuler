#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

#define SIZE 80

using namespace std;

vector<vector<int>> readMatrix() {
    int num;
    vector<vector<int>> matrix = vector<vector<int>>(SIZE, vector<int>(SIZE));
    for (int row=0; row<SIZE; ++row) {
        for (int col=0; col<SIZE; ++col) {
            cin >> num;
            matrix[row][col] = num;
        }
    }
    return matrix;
}

int getMinimalPathSum(const vector<vector<int>> &matrix) {
    vector<vector<int>> minimalPathSum = vector<vector<int>>(SIZE, vector<int>(SIZE));

    // Last column's cost is the current value
    for (int i=0; i<SIZE; ++i) {
        minimalPathSum[i][SIZE-1] = matrix[i][SIZE-1];
    }

    for (int col=SIZE-2; col >= 0; --col) {
        for (int row=0; row<SIZE; ++row) {
            // Check going up
            int currentSumGoingUp = matrix[row][col];
            int minimumGoingUp = matrix[row][col] + minimalPathSum[row][col + 1];
            for (int i=row-1; i >= 0; --i) {
                currentSumGoingUp += matrix[i][col];
                minimumGoingUp = min(minimumGoingUp, currentSumGoingUp + minimalPathSum[i][col + 1]);
            }

            // Check going down
            int currentSumGoingDown = matrix[row][col];
            int minimumGoingDown = matrix[row][col] + minimalPathSum[row][col + 1];
            for (int i=row+1; i<SIZE; ++i) {
                currentSumGoingDown += matrix[i][col];
                minimumGoingDown = min(minimumGoingDown, currentSumGoingDown + minimalPathSum[i][col + 1]);
            }

            minimalPathSum[row][col] = min(minimumGoingUp, minimumGoingDown);
        }
    }

    int minimum = INT_MAX;
    for (int i=0; i<SIZE; ++i) {
        minimum = min(minimum, minimalPathSum[i][0]);
    }
    return minimum;
}

int main() {
    vector<vector<int>> matrix = readMatrix();
    cout << getMinimalPathSum(matrix) << endl;
    return 0;
}

