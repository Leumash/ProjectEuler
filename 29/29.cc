/*
Consider all integer combinations of a ^ b for 2 ≤ a ≤ 5 and 2 ≤ b ≤ 5:

2²=4,  2³=8,   2^4=16,  2^5=32
3²=9,  3³=27,  3^4=81,  3^5=243
4²=16, 4³=64,  4^4=256, 4^5=1024
5²=25, 5³=125, 5^4=625, 5^5=3125
If they are then placed in numerical order, with any repeats removed, we get the following sequence of 15 distinct terms:

4, 8, 9, 16, 25, 27, 32, 64, 81, 125, 243, 256, 625, 1024, 3125

How many distinct terms are in the sequence generated by a ^ b for 2 ≤ a ≤ 100 and 2 ≤ b ≤ 100?
*/

#include <iostream>
#include <set>
#include <utility>
#include <map>
#include <unordered_map>

using namespace std;

int GetAPrime(int a, unordered_map<int, pair<int,int> > &conversion)
{
    if (conversion.count(a) > 0)
    {
        return conversion[a].first;
    }

    return a;
}

int GetBPrime(int a, int b, unordered_map<int, pair<int,int> > &conversion)
{
    if (conversion.count(a) > 0)
    {
        return b * conversion[a].second;
    }

    return b;
}

unordered_map<int, pair<int,int> > GetConversions()
{
    unordered_map<int, pair<int,int> > toReturn;

    toReturn[4] = make_pair(2, 2);
    toReturn[8] = make_pair(2, 3);
    toReturn[16] = make_pair(2, 4);
    toReturn[32] = make_pair(2, 5);
    toReturn[64] = make_pair(2, 6);

    toReturn[9] = make_pair(3, 2);
    toReturn[27] = make_pair(3, 3);
    toReturn[81] = make_pair(3, 4);

    toReturn[25] = make_pair(5, 2);
    toReturn[36] = make_pair(6, 2);
    toReturn[49] = make_pair(7, 2);
    toReturn[100] = make_pair(10, 2);

    return toReturn;
}

int GetNumberOfDistinctTerms(int n)
{
    // 2 ≤ a ≤ 100
    // 2 ≤ b ≤ 100

    int aPrime;
    int bPrime;
    set< pair<int,int> > terms;
    unordered_map<int, pair<int,int> > conversion = GetConversions();

    for (int a=2; a<=n; ++a)
    {
        for (int b=2; b<=n; ++b)
        {
            aPrime = GetAPrime(a, conversion);
            bPrime = GetBPrime(a, b, conversion);

            terms.insert(make_pair(aPrime, bPrime));
        }
    }

    return terms.size();
}

int main()
{
    cout << GetNumberOfDistinctTerms(100) << endl;

    return 0;
}

