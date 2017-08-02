#include <iostream>
#include <cmath>

#define EPSILON 0.000000001

using namespace std;

bool increasing(int num, int n) {
    while (n > 0) {
        int next = n % 10;
        n = n / 10;

        if (next < num) {
            return true;
        }
        if (next > num) {
            num = next;
        }
    }
    return false;
}

bool decreasing(int num, int n) {
    while (n > 0) {
        int next = n % 10;
        n = n / 10;

        if (next > num) {
            return true;
        }
        if (next < num) {
            num = next;
        }
    }
    return false;
}

bool isBouncy(int n) {
    int num = n % 10;
    n = n / 10;

    while (n > 0) {
        int next = n % 10;
        n = n / 10;
        if (next > num) {
            return increasing(next, n);
        }
        if (next < num) {
            return decreasing(next, n);
        }
    }

    return false;
}

bool isPercentage(int bouncyCount, int notBouncyCount, int percentageBouncy) {
    double a = percentageBouncy / 100.0;
    double b = bouncyCount * 1.0 / (bouncyCount + notBouncyCount);

    return std::abs(a - b) < EPSILON;
}

int getSmallestProportion(int percentageBouncy) {
    int i = 100;
    int bouncyCount = 0;
    int notBouncyCount = 99;
    while (true) {
        if (isBouncy(i)) {
            ++bouncyCount;
        } else {
            ++notBouncyCount;
        }
        if (isPercentage(bouncyCount, notBouncyCount, percentageBouncy)) {
            return i;
        }
        ++i;
    }
}

int main() {
    cout << getSmallestProportion(50) << endl;
    cout << getSmallestProportion(90) << endl;
    cout << getSmallestProportion(99) << endl;
    return 0;
}

