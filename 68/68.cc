/*
Consider the following "magic" 3-gon ring, filled with the numbers 1 to 6, and each line adding to nine.

// Picture here

Working clockwise, and starting from the group of three with the numerically lowest external node (4,3,2 in this example), each solution can be described uniquely. For example, the above solution can be described by the set: 4,3,2; 6,2,1; 5,1,3.

It is possible to complete the ring with four different totals: 9, 10, 11, and 12. There are eight solutions in total.

Total   Solution Set

9   4,2,3; 5,3,1; 6,1,2
9   4,3,2; 6,2,1; 5,1,3
10  2,3,5; 4,5,1; 6,1,3
10  2,5,3; 6,3,1; 4,1,5
11  1,4,6; 3,6,2; 5,2,4
11  1,6,4; 5,4,2; 3,2,6
12  1,5,6; 2,6,4; 3,4,5
12  1,6,5; 3,5,4; 2,4,6

By concatenating each group it is possible to form 9-digit strings; the maximum string for a 3-gon ring is 432621513.

Using the numbers 1 to 10, and depending on arrangements, it is possible to form 16- and 17-digit strings. What is the maximum 16-digit string for a "magic" 5-gon ring?

// Picture here

*/

/*

Picture used for implementation

        9
         \
          6   1
         / \ /
        5   7
       / \ /
      4  0-8-2
         \
          3

*/

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;


bool IsMagicGonRing(const vector<int> numbers)
{
    int arr[] =
    {
        numbers[9] + numbers[6] + numbers[7],
        numbers[1] + numbers[7] + numbers[8],
        numbers[2] + numbers[8] + numbers[0],
        numbers[3] + numbers[0] + numbers[5],
        numbers[4] + numbers[5] + numbers[6]
    };

    for (int i=1; i<5; ++i)
    {
        if (arr[0] != arr[i])
        {
            return false;
        }
    }

    return true;
}

void Rotate(vector<int> &gonRing)
{
    int temp = gonRing[0];

    gonRing.erase(gonRing.begin());

    gonRing.push_back(temp);
}

vector<int> GetNumbersInGonRing(const vector<int> &numbers)
{
    vector<int> toReturn;

    toReturn.push_back(stoi(to_string(numbers[9]) + to_string(numbers[6]) + to_string(numbers[7])));
    toReturn.push_back(stoi(to_string(numbers[1]) + to_string(numbers[7]) + to_string(numbers[8])));
    toReturn.push_back(stoi(to_string(numbers[2]) + to_string(numbers[8]) + to_string(numbers[0])));
    toReturn.push_back(stoi(to_string(numbers[3]) + to_string(numbers[0]) + to_string(numbers[5])));
    toReturn.push_back(stoi(to_string(numbers[4]) + to_string(numbers[5]) + to_string(numbers[6])));

    return toReturn;
}

long long GetMagicGonRingString(const vector<int> &numbers)
{
    vector<int> gonRing = GetNumbersInGonRing(numbers);

    int minimum = *min_element(gonRing.begin(), gonRing.end());

    while (gonRing[0] != minimum)
    {
        Rotate(gonRing);
    }

    string toReturn;

    for (int number : gonRing)
    {
        toReturn += to_string(number);
    }

    return stoll(toReturn);
}

long long GetMaximumSixteenDigitStringForMagicFiveGonRing()
{
    vector<int> numbers(10);
    vector<long long> magicGonRingStrings;

    for (int i=0; i<10; ++i)
    {
        numbers[i] = i + 1;
    }

    do
    {
        if (IsMagicGonRing(numbers))
        {
            magicGonRingStrings.push_back(GetMagicGonRingString(numbers));
        }

    } while (next_permutation(numbers.begin(), numbers.end() - 1));

    return *max_element(magicGonRingStrings.begin(), magicGonRingStrings.end());
}

int main()
{
    cout << GetMaximumSixteenDigitStringForMagicFiveGonRing() << endl;

    return 0;
}

