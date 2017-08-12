#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

string hashValues(int a, int b) {
    return to_string(a) + ' ' + to_string(b);
}

bool isPerfectSquare(int n) {
    int squareRoot = sqrt(n);
    return squareRoot * squareRoot == n;
}

int getRepeats(string val, const vector<string> &seen) {
    for (int i=0; i<seen.size(); ++i) {
        if (val == seen[i]) {
            return seen.size() - i;
        }
    }
    return -1;
}

int getNumberOfRepeatedContinuedFractions(int n, int numerator, int denominatorSubtraction, vector<string> &seen) {
    string hashedValue = hashValues(numerator, denominatorSubtraction);
    int loopLength = getRepeats(hashedValue, seen);
    if (loopLength > 0) {
        return loopLength;
    } else {
        seen.push_back(hashedValue);
    }

    // First transformation
    int numeratorAddition = denominatorSubtraction;
    int denominator = (n - denominatorSubtraction * denominatorSubtraction) / numerator;

    // Second transformation
    int numeratorSubtraction = 0;
    while (numeratorAddition % denominator > 0) {
        ++numeratorAddition;
        ++numeratorSubtraction;
    }

    while (1) {
        if ((denominator + numeratorSubtraction) * (denominator + numeratorSubtraction) > n) {
            break;
        }
        numeratorSubtraction += denominator;
    }

    return getNumberOfRepeatedContinuedFractions(n, denominator, numeratorSubtraction, seen);
}

int getNumberOfRepeatedContinuedFractions(int n, int perfectSquareBelowN) {
    int numerator = n;
    int denominatorSubtraction = 0;
    vector<string> seen;
    return getNumberOfRepeatedContinuedFractions(n, numerator, denominatorSubtraction, seen);
}

int getNumberOfRepeatedContinuedFractionsWithOddPeriod(int n) {
    int numberOfRepeatedContinuedFractionsWithOddPeriod = 0;
    int currentLowestPerfectSquare = 0;

    for (int i = 1; i<=n; ++i) {
        if (isPerfectSquare(i)) {
            currentLowestPerfectSquare = i;
        } else {
            int numRepeated = getNumberOfRepeatedContinuedFractions(i, currentLowestPerfectSquare);
            if (numRepeated % 2 == 1) {
                ++numberOfRepeatedContinuedFractionsWithOddPeriod;
            }
        }
    }
    return numberOfRepeatedContinuedFractionsWithOddPeriod;
}

int main() {
    //cout << getNumberOfRepeatedContinuedFractionsWithOddPeriod(13) << endl;
    cout << getNumberOfRepeatedContinuedFractionsWithOddPeriod(10000) << endl;
    return 0;
}

