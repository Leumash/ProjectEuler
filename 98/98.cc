/*
By replacing each of the letters in the word CARE with 1, 2, 9, and 6 respectively, we form a square number: 1296 = 36^2. What is remarkable is that, by using the same digital substitutions, the anagram, RACE, also forms a square number: 9216 = 96^2. We shall call CARE (and RACE) a square anagram word pair and specify further that leading zeroes are not permitted, neither may a different letter have the same digital value as another letter.

Using words.txt, a 16K text file containing nearly two-thousand common English words, find all the square anagram word pairs (a palindromic word is NOT considered to be an anagram of itself).

What is the largest square number formed by any member of such a pair?

NOTE: All anagrams formed must be contained in the given text file.
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <algorithm>

using namespace std;

vector<string> GetWords()
{
    string word;
    vector<string> words;

    ifstream fin("words.txt");

    while (fin >> word)
    {
        words.push_back(word);
    }

    return words;
}

bool MyComp(pair<string,string> a, pair<string,string> b)
{
    return a.first == b.first ? a.second < b.second : a.first < b.first;
}

vector<pair<string,string>> MakeSortedWordAndWord(const vector<string> &words)
{
    vector<string> sortedWords = words;

    for (string &word : sortedWords)
    {
        sort(word.begin(), word.end());
    }

    vector<pair<string,string>> toReturn;

    for (int i=0; i<words.size(); ++i)
    {
        toReturn.push_back(make_pair(sortedWords[i], words.at(i)));
    }

    return toReturn;
}

vector<vector<pair<string,string>>> GetAnagrams(vector<pair<string,string>> &sortedWordAndWord)
{
    sort(sortedWordAndWord.begin(), sortedWordAndWord.end(), MyComp);

    vector<vector<pair<string,string>>> toReturn;

    for (int i=0; i<sortedWordAndWord.size(); ++i)
    {
        vector<pair<string,string>> anagrams;

        string sortedWord = sortedWordAndWord[i].first;

        int j;

        for (j=i+1; j<sortedWordAndWord.size(); ++j)
        {
            if (sortedWordAndWord[j].first != sortedWord)
            {
                break;
            }
        }

        if (j - i >= 2)
        {
            for (int k = i; k<j; ++k)
            {
                anagrams.push_back(sortedWordAndWord[k]);
            }

            toReturn.push_back(anagrams);

            i = j - 1;
        }
    }

    return toReturn;
}

string Decode(const unordered_map<char,char> &letterToNumber, string wordToDecode)
{
    for (char &c : wordToDecode)
    {
        c = letterToNumber.at(c);
    }

    return wordToDecode;
}

unordered_map<char,char> GetLetterToNumber(int n, const string &word)
{
    string number = to_string(n);

    unordered_map<char,char> toReturn;

    for (int i=0; i<word.size(); ++i)
    {
        toReturn[word[i]] = number[i];
    }

    return toReturn;
}

bool IsPerfectSquare(int n)
{
    int squareRoot = sqrt(n);

    return squareRoot * squareRoot == n;
}

bool IsValidNumberMap(string number, const string &word1, const string &word2)
{
    unordered_set<char> usedNumbers;
    unordered_map<char,char> letterToNumber;

    for (int i=0; i<word1.size(); ++i)
    {
        if (letterToNumber.count(word1[i]) == 0)
        {
            if (usedNumbers.count(number[i]) > 0)
            {
                return false;
            }
            else
            {
                letterToNumber[word1[i]] = number[i];
                usedNumbers.insert(number[i]);
            }
        }
        else
        {
            if (letterToNumber[word1[i]] != number[i])
            {
                return false;
            }
        }
    }

    if (letterToNumber[word2[0]] == '0')
    {
        return false;
    }

    return true;
}

int GetNumberOfDigits(int n)
{
    return log10(n) + 1;
}

vector<int> GetPerfectSquares(int numberOfDigits)
{
    vector<int> perfectSquares;

    for (int i=1; GetNumberOfDigits(i*i) <= numberOfDigits; ++i)
    {
        if (GetNumberOfDigits(i*i) == numberOfDigits)
        {
            perfectSquares.push_back(i*i);
        }
    }

    return perfectSquares;
}

int GetLargestSquareNumber(string word1, string word2)
{
    static vector<vector<int>> allPerfectSquares;
    int largest = 0;

    while (allPerfectSquares.size() <= word1.size())
    {
        vector<int> perfectSquares = GetPerfectSquares(allPerfectSquares.size());

        allPerfectSquares.push_back(perfectSquares);
    }

    for (int perfectSquare : allPerfectSquares[word1.size()])
    {
        if (IsValidNumberMap(to_string(perfectSquare), word1, word2))
        {
            unordered_map<char,char> letterToNumber = GetLetterToNumber(perfectSquare, word1);

            string number2 = Decode(letterToNumber, word2);

            int num2 = stoi(number2);

            if (IsPerfectSquare(num2))
            {
                largest = max({perfectSquare, num2, largest});
            }
        }
    }

    return largest;
}

int GetLargestSquareNumberFormedByASquareAnagramWordPair()
{
    int largestSquareNumber = 0;

    vector<string> words = GetWords();

    vector<pair<string,string>> sortedWordAndWord = MakeSortedWordAndWord(words);

    vector<vector<pair<string,string>>> allAnagrams = GetAnagrams(sortedWordAndWord);

    for (const auto &anagrams : allAnagrams)
    {
        for (int i=0; i<anagrams.size(); ++i)
        {
            for (int j=i+1; j<anagrams.size(); ++j)
            {
                int largeSquareNumber = GetLargestSquareNumber(anagrams[i].second, anagrams[j].second);
                largestSquareNumber = max(largestSquareNumber, largeSquareNumber);
            }
        }
    }

    return largestSquareNumber;
}

int main()
{
    cout << GetLargestSquareNumberFormedByASquareAnagramWordPair() << endl;

    return 0;
}

