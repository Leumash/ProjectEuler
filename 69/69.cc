#include <iostream>

using namespace std;

bool isPrime(int n) {
    for (int i=2; i<n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int getNextPrime(int n) {
    int current = n + 1;
    while (!isPrime(current)) {
        ++current;
    }
    return current;
}

int getMax(int n) {
    int prime = 2;
    int total = prime;
    while (true) {
        int nextPrime = getNextPrime(prime);
        if (total * nextPrime > n) {
            break;
        }
        total *= nextPrime;
        prime = nextPrime;
    }
    return total;
}

int main() {
    cout << getMax(1000000) << endl;
    return 0;
}

