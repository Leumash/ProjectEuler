#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

bool isValid(int numer, int denom) {
    double third = 1.0 / 3;
    double half = 1.0 / 2;
    double value = numer * 1.0 / denom;
    return value > third && value < half;
}

int getNumberOfReducedProperFractions(int n) {
    unordered_map<int, unordered_set<int>> numeratorsToDenominators;
    for (int denominator=1; denominator<=n; ++denominator) {
        for (int numerator=1; numerator<denominator; ++numerator) {
            if (isValid(numerator, denominator)) {
                int hcf = gcd(numerator, denominator);
                int numer = numerator / hcf;
                int denom = denominator / hcf;
                numeratorsToDenominators[numer].insert(denom);
            }
        }
    }

    int count = 0;
    for (auto numerToDenoms : numeratorsToDenominators) {
        count += numerToDenoms.second.size();
    }
    return count;
}

int main() {
    cout << getNumberOfReducedProperFractions(12000) << endl;
    return 0;
}

