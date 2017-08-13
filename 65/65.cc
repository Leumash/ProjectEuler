#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

vector<int> getPartialDenominatorsOfE(int n) {
    vector<int> partialDenominators;
    partialDenominators.push_back(2);
    for (int i=2; i<=n; ++i) {
        if (i % 3) {
            partialDenominators.push_back(1);
        } else {
            partialDenominators.push_back(i/3 * 2);
        }
    }
    return partialDenominators;
}

int getNumerator(const vector<int> &partialDenominators) {
    long long numerator = partialDenominators[partialDenominators.size() - 1];
    long long denominator = 1;
    for (int i=partialDenominators.size() - 2; i>=0; --i) {
        long long previous = partialDenominators[i];
        swap(numerator, denominator);
        numerator = denominator * previous + numerator;
        long long GCD = gcd(numerator, denominator);
        numerator /= GCD;
        denominator /= GCD;
    }
    return numerator;
}

int sumOfDigits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n %10;
        n /= 10;
    }
    return sum;
}

int getSumOfDigitsInNumerator(const vector<int> &partialDenominators) {
    int numerator = getNumerator(partialDenominators);
    return sumOfDigits(numerator);
}

int getSumOfDigitsInNumerator(int n) {
    vector<int> partialDenominators = getPartialDenominatorsOfE(n);
    return getSumOfDigitsInNumerator(partialDenominators);
}

int main() {
    cout << getSumOfDigitsInNumerator(10) << endl;
    //cout << getSumOfDigitsInNumerator(100) << endl;
    return 0;
}

