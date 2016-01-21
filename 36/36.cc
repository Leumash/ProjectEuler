#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <sstream>

/*
The decimal number, 585 = 10010010012 (binary), is palindromic in both bases.

Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.

(Please note that the palindromic number, in either base, may not include leading zeros.)
*/

using namespace std;

vector<bool> GetBitSet(int n)
{
    vector<bool> toReturn;

    while (n)
    {
        toReturn.push_back(n & 1);
        n >>= 1;
    }

    return toReturn;
}

string GetDecSet(int n)
{
    stringstream ss;

    ss << n;

    return ss.str();
}

bool IsPalindrome(vector<bool> bits)
{
    for (int i=0; i<bits.size() / 2; ++i)
    {
        if (bits[i] != bits[bits.size() - 1 - i])
        {
            return false;
        }
    }

    return true;
}

bool IsPalindrome(string dec)
{
    for (int i=0; i<dec.size() / 2; ++i)
    {
        if (dec[i] != dec[dec.size() - 1 - i])
        {
            return false;
        }
    }

    return true;
}

bool IsDoubleBasePalindrome(int n)
{
    vector<bool> bits = GetBitSet(n);
    string dec = GetDecSet(n);

    return (IsPalindrome(bits) && IsPalindrome(dec));
}

int GetSum(int n)
{
    int sum = 0;

    for (int i=1; i<n; ++i)
    {
        if (IsDoubleBasePalindrome(i))
        {
            sum += i;
        }
    }

    return sum;
}

int main()
{
    cout << GetSum(1000000) << endl;
}

