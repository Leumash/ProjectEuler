#include <iostream>

using namespace std;

int findNumberOfConsecutivePositiveDivisors(int n) {
    int* divisors = new int[n+1];
    for (int i=1; i<=n; ++i) {
        divisors[i] = 1;
    }
    for (int i=2; i<=n; ++i) {
        for (int index = i; index <= n; index += i) {
            ++divisors[index];
        }
    }
    int count = 0;
    for (int i=1; i<n; ++i) {
        if (divisors[i] == divisors[i+1]) {
            ++count;
        }
    }
    delete [] divisors;
    return count;
}

int main() {
    cout << findNumberOfConsecutivePositiveDivisors(10000000) << endl;
}

