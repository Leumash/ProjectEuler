/*

Euler's Totient function, p(n) [sometimes called the phi function], is used to determine the number of positive numbers less than or equal to n which are relatively prime to n. For example, as 1, 2, 4, 5, 7, and 8, are all less than nine and relatively prime to nine, p(9)=6.
The number 1 is considered to be relatively prime to every positive number, so p(1)=1.

Interestingly, p(87109)=79180, and it can be seen that 87109 is a permutation of 79180.

Find the value of n, 1 < n < 10^7, for which p(n) is a permutation of n and the ratio n/p(n) produces a minimum.

*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

vector<bool> getSieve(int n) {
    vector<bool> sieve(n, true);
    sieve[0] = false;
    sieve[1] = false;
    for (int prime=2; prime<n; ++prime) {
        if (!sieve[prime]) {
            continue;
        }
        for (int multiplier = 2; prime * multiplier < n; ++multiplier) {
            sieve[prime * multiplier] = false;
        }
    }
    return sieve;
}

vector<int> getPrimes(int n) {
    vector<int> primes;
    vector<bool> sieve = getSieve(n);
    for (int i=0; i<sieve.size(); ++i) {
        if (sieve[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

int phi(int a, int b) {
    return a * b - (a - 1) - (b - 1) - 1;
}

bool isPermutation(int n, int m) {
    string a = to_string(n);
    string b = to_string(m);
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return a == b;
}

int getMinimumRatioPermutation(int n) {
    int smallest;
    double minimum = INT_MAX;
    vector<int> primes = getPrimes(n);
    for (int i=0; i<primes.size(); ++i) {
        for (int j=i; j<primes.size(); ++j) {
            long long iPrime = primes[i];
            long long jPrime = primes[j];
            long long num = iPrime * jPrime;
            if (num >= (n * 1l)) {
                break;
            }
            int p = phi(iPrime, jPrime);
            if (isPermutation(num, p)) {
                double ratio = num * 1.0 / p;
                if (ratio < minimum) {
                    minimum = ratio;
                    smallest = num;
                }
            }
        }
    }
    return smallest;
}

int main() {
    cout << getMinimumRatioPermutation(10000000) << endl;
}

