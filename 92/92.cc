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

int GetSquareOfDigits(int n, int digitToSquare[])
{
    int sum = 0;

    while (n)
    {
        sum += digitToSquare[n % 10];
        n /= 10;
    }

    return sum;
}

bool DoesNumberArriveAt89(int n, unordered_map<int,int> &numberAndArrival, int digitToSquare[])
{
    if (numberAndArrival.count(n) > 0)
    {
        return numberAndArrival[n] == 89;
    }

    int squareOfDigits = GetSquareOfDigits(n, digitToSquare);

    if (DoesNumberArriveAt89(squareOfDigits, numberAndArrival, digitToSquare))
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
    int digitToSquare[] = { 0, 1, 4, 9, 16, 25, 36, 49, 64, 81 };
    unordered_map<int,int> numberAndArrival;

    numberAndArrival[1] = 1;
    numberAndArrival[89] = 89;

    for (int i=1; i<limit; ++i)
    {
        if (DoesNumberArriveAt89(i, numberAndArrival, digitToSquare))
        {
            ++count;
        }
    }

    return count;
}

bool DoesNumberArriveAt89(int n)
{
    if (n <= 0)
    {
        return false;
    }

    int digitToSquare[] = { 0, 1, 4, 9, 16, 25, 36, 49, 64, 81 };
    static unordered_map<int,int> numberAndArrival;

    numberAndArrival[1] = 1;
    numberAndArrival[89] = 89;

    return DoesNumberArriveAt89(n, numberAndArrival, digitToSquare);
}

int Factorial(int n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }

    return n * Factorial(n-1);
}

int GetMultinomialCoefficient(string n)
{
    int digitCount[10] = {0};

    for (char c : n)
    {
        ++digitCount[c - '0'];
    }

    return Factorial(n.size())
        / (
            Factorial(digitCount[0])
            * Factorial(digitCount[1])
            * Factorial(digitCount[2])
            * Factorial(digitCount[3])
            * Factorial(digitCount[4])
            * Factorial(digitCount[5])
            * Factorial(digitCount[6])
            * Factorial(digitCount[7])
            * Factorial(digitCount[8])
            * Factorial(digitCount[9])
          );
}

string IncrementNonDecreasing(string n)
{
    int nonNineIndex;

    for (nonNineIndex=n.size() - 1; nonNineIndex >= 0; --nonNineIndex)
    {
        if (n[nonNineIndex] != '9')
        {
            break;
        }
    }

    if (nonNineIndex < 0)
    {
        return n + '9';
    }

    char nextNumber = n[nonNineIndex] + 1;

    for (int i=nonNineIndex; i<n.size(); ++i)
    {
        n[i] = nextNumber;
    }

    return n;
}

int GetNumbers(int digits)
{
    int sum = 0;
    string start;
    string end;

    for (int i=0; i<digits; ++i)
    {
        start += "0";
        end += "9";
    }

    for (string i = start; i <= end; i = IncrementNonDecreasing(i))
    {
        if (DoesNumberArriveAt89(stoi(i)))
        {
            sum += GetMultinomialCoefficient(i);
        }
    }

    return sum;
}

int main()
{
    //cout << GetNumbersThatArriveAt89(10000000) << endl;
    cout << GetNumbers(7) << endl;

    return 0;
}

