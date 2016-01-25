/*
If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?
*/

#include <iostream>
#include <map>

using namespace std;

map<int,int> FillMap()
{
    map<int,int> numberToNumberOfLetters;

    numberToNumberOfLetters[1] = 3;
    numberToNumberOfLetters[2] = 3;
    numberToNumberOfLetters[3] = 5;
    numberToNumberOfLetters[4] = 4;
    numberToNumberOfLetters[5] = 4;
    numberToNumberOfLetters[6] = 3;
    numberToNumberOfLetters[7] = 5;
    numberToNumberOfLetters[8] = 5;
    numberToNumberOfLetters[9] = 4;

    numberToNumberOfLetters[11] = 6;
    numberToNumberOfLetters[12] = 6;
    numberToNumberOfLetters[13] = 8;
    numberToNumberOfLetters[14] = 8;
    numberToNumberOfLetters[15] = 7;
    numberToNumberOfLetters[16] = 7;
    numberToNumberOfLetters[17] = 9;
    numberToNumberOfLetters[18] = 8;
    numberToNumberOfLetters[19] = 8;

    numberToNumberOfLetters[10] = 3;
    numberToNumberOfLetters[20] = 6;
    numberToNumberOfLetters[30] = 6;
    numberToNumberOfLetters[40] = 5;
    numberToNumberOfLetters[50] = 5;
    numberToNumberOfLetters[60] = 5;
    numberToNumberOfLetters[70] = 7;
    numberToNumberOfLetters[80] = 6;
    numberToNumberOfLetters[90] = 6;

    numberToNumberOfLetters[100] = 10;
    numberToNumberOfLetters[200] = 10;
    numberToNumberOfLetters[300] = 12;
    numberToNumberOfLetters[400] = 11;
    numberToNumberOfLetters[500] = 11;
    numberToNumberOfLetters[600] = 10;
    numberToNumberOfLetters[700] = 12;
    numberToNumberOfLetters[800] = 12;
    numberToNumberOfLetters[900] = 11;

    numberToNumberOfLetters[1000] = 11;

    return numberToNumberOfLetters;
}

bool IsSpecialNumberPresent(int n)
{
    return (n%100 > 10) && (n%100 < 20);
}

int GetNumberOfLetters(int n)
{
    int numberOfLetters = 0;
    map<int,int> numberToNumberOfLetters = FillMap();

    // And
    if (n >= 100 && n % 100 > 0)
    {
        numberOfLetters += 3;
    }

    // Check for specialty numbers - 11-19 and remove them
    if (IsSpecialNumberPresent(n))
    {
        numberOfLetters += numberToNumberOfLetters[n%100];
        n -= n%100;
    }

    // Check ones place
    if (n%10)
    {
        numberOfLetters += numberToNumberOfLetters[n%10];
    }

    // Check tens place
    int tens = n % 100 - n % 10;
    if (tens)
    {
        numberOfLetters += numberToNumberOfLetters[tens];
    }

    // Check hundreds
    int hundreds = n % 1000 - n % 100;
    if (hundreds)
    {
        numberOfLetters += numberToNumberOfLetters[hundreds];
    }

    // Check thousands
    int thousands = n % 10000 - n % 1000;
    if (thousands)
    {
        numberOfLetters += numberToNumberOfLetters[thousands];
    }

    return numberOfLetters;
}

int CountLetters(int n)
{
    int sum = 0;

    for (int i=1; i<=1000; ++i)
    {
        sum += GetNumberOfLetters(i);
    }

    return sum;
}

int main()
{
    cout << CountLetters(1000) << endl;
    return 0;
}

