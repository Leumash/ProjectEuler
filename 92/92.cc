/*
A number chain is created by continuously adding the square of the digits in a number to form a new number until it has been seen before.

For example,

44 → 32 → 13 → 10 → 1 → 1
85 → 89 → 145 → 42 → 20 → 4 → 16 → 37 → 58 → 89

Therefore any chain that arrives at 1 or 89 will become stuck in an endless loop. What is most amazing is that EVERY starting number will eventually arrive at 1 or 89.

How many starting numbers below ten million will arrive at 89?
*/

#include <iostream>
#include <unordered_map>

using namespace std;

int GetSquareOfDigits(int n)
{
    int sum = 0;

    while (n)
    {
        sum += (n % 10) * (n % 10);
        n /= 10;
    }

    return sum;
}

bool DoesNumberArriveAt89(int n, unordered_map<int,int> &numberAndArrival)
{
    if (numberAndArrival.count(n) > 0)
    {
        return numberAndArrival[n] == 89;
    }

    int squareOfDigits = GetSquareOfDigits(n);

    if (DoesNumberArriveAt89(squareOfDigits, numberAndArrival))
    {
        numberAndArrival[n] = 89;
    }
    else
    {
        numberAndArrival[n] = 1;
    }

    return numberAndArrival[n] == 89;
}

int GetNumbersThatArriveAt89(int limit)
{
    int count = 0;
    unordered_map<int,int> numberAndArrival;

    numberAndArrival[1] = 1;
    numberAndArrival[89] = 89;

    for (int i=1; i<limit; ++i)
    {
        if (DoesNumberArriveAt89(i, numberAndArrival))
        {
            ++count;
        }
    }

    return count;
}

int main()
{
    //cout << GetNumbersThatArriveAt89(10000000) << endl;
    cout << GetNumbersThatArriveAt89(100) << endl;
    return 0;
}

