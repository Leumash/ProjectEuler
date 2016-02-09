/*
The nth term of the sequence of triangle numbers is given by, tn = ½n(n+1); so the first ten triangle numbers are:

1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

By converting each letter in a word to a number corresponding to its alphabetical position and adding these values we form a word value. For example, the word value for SKY is 19 + 11 + 25 = 55 = t10. If the word value is a triangle number then we shall call the word a triangle word.

Using words.txt (right click and 'Save Link/Target As...'), a 16K text file containing nearly two-thousand common English words, how many are triangle words?
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <string>

using namespace std;

vector<string> GetWords(const char* inputFile)
{
    vector<string> toReturn;
    ifstream fin(inputFile);
    string temp;

    while (fin >> temp)
    {
        toReturn.push_back(temp);
    }

    return toReturn;
}

int GetLetterValue(const char &letter)
{
    return toupper(letter) - 'A' + 1;
}

int GetWordValue(const string &word)
{
    int wordValue = 0;

    for (auto letter : word)
    {
        wordValue += GetLetterValue(letter);
    }

    return wordValue;
}

vector<int> GetWordValues(const vector<string> &words)
{
    vector<int> toReturn;

    for (auto &word : words)
    {
        toReturn.push_back(GetWordValue(word));
    }

    return toReturn;
}

unordered_set<int> GetTriangleNumbers(int limitInclusive)
{
    // tn = ½ n(n+1);
    // 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

    unordered_set<int> triangleNumbers;

    int triangleNumber = 1;

    for (int n=2; triangleNumber <= limitInclusive; ++n)
    {
        triangleNumbers.insert(triangleNumber);

        triangleNumber = (n * (n + 1)) / 2;
    }

    return triangleNumbers;
}

int GetCountOfTriangleWords(const vector<int> &wordValues,
    const unordered_set<int> &triangleNumbers)
{
    int count = 0;

    for (int wordValue : wordValues)
    {
        if (triangleNumbers.count(wordValue) > 0)
        {
            ++count;
        }
    }

    return count;
}

int GetCountOfTriangleWords(const char* inputFile)
{
    vector<string> words = GetWords(inputFile);

    vector<int> wordValues = GetWordValues(words);

    int maxWordValue = *max_element(wordValues.begin(), wordValues.end());

    unordered_set<int> triangleNumbers = GetTriangleNumbers(maxWordValue);

    return GetCountOfTriangleWords(wordValues, triangleNumbers);
}

int main()
{
    cout << GetCountOfTriangleWords("words.txt") << endl;

    return 0;
}

