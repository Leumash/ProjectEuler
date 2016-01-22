/*
The first known prime found to exceed one million digits was discovered in 1999, and is a Mersenne prime of the form 26972593−1; it contains exactly 2,098,960 digits. Subsequently other Mersenne primes, of the form 2p−1, have been found which contain more digits.

However, in 2004 there was found a massive non-Mersenne prime which contains 2,357,207 digits: 28433×27830457+1.

Find the last ten digits of this prime number.
*/

#include <iostream>

#define DIGITS 10000000000l

using namespace std;

long long GetLastTenDigitsOfPowerOfTwo(int n)
{
    long long answer = 1;

    for (int i=0; i<n; ++i)
    {
        answer = (answer << 1) % DIGITS;
    }

    return answer;
}


long long LastTenDigitsOfNonMersennePrime()
{
    long long answer = 0;
    // Get Last ten digits of 2 ^ 7830457
    answer = GetLastTenDigitsOfPowerOfTwo(7830457);

    // Multiply result by 28433
    answer *= 28433;

    // Add 1
    answer += 1;

    // Return Last ten digits
    return answer % DIGITS;
}

int main()
{
    cout << LastTenDigitsOfNonMersennePrime() << endl;
}

