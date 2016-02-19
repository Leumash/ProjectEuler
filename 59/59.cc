/*
Each character on a computer is assigned a unique code and the preferred standard is ASCII (American Standard Code for Information Interchange). For example, uppercase A = 65, asterisk (*) = 42, and lowercase k = 107.

A modern encryption method is to take a text file, convert the bytes to ASCII, then XOR each byte with a given value, taken from a secret key. The advantage with the XOR function is that using the same encryption key on the cipher text, restores the plain text; for example, 65 XOR 42 = 107, then 107 XOR 42 = 65.

For unbreakable encryption, the key is the same length as the plain text message, and the key is made up of random bytes. The user would keep the encrypted message and the encryption key in different locations, and without both "halves", it is impossible to decrypt the message.

Unfortunately, this method is impractical for most users, so the modified method is to use a password as a key. If the password is shorter than the message, which is likely, the key is repeated cyclically throughout the message. The balance for this method is using a sufficiently long password key for security, but short enough to be memorable.

Your task has been made easy, as the encryption key consists of three lower case characters. Using cipher.txt (right click and 'Save Link/Target As...'), a file containing the encrypted ASCII codes, and the knowledge that the plain text must contain common English words, decrypt the message and find the sum of the ASCII values in the original text.
*/

/*
Source: wikipedia.com
20 most common words in English:

the
be
to
of
and
a
in
that
have
I
it
for
not
on
with
he
as
you
do
at
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_set>
#include <sstream>
#include <cctype>

using namespace std;

vector<char> GetText(const char* inputFile)
{
    vector<char> toReturn;
    ifstream fin(inputFile);

    int temp;

    while (fin >> temp)
    {
        toReturn.push_back(temp);
    }

    return toReturn;
}

vector< vector<char> > GetPotentialKeys()
{
    // Keys are 3 lowercase letters

    vector< vector<char> > toReturn;

    for (char i='a'; i<='z'; ++i)
    {
        for (char j='a'; j<='z'; ++j)
        {
            for (char k='a'; k<='z'; ++k)
            {
                vector<char> toPushBack;

                toPushBack.push_back(i);
                toPushBack.push_back(j);
                toPushBack.push_back(k);

                toReturn.push_back(toPushBack);
            }
        }
    }

    return toReturn;
}

vector<char> DecryptText(const vector<char> &cipherText, const vector<char> &key)
{
    vector<char> decryptedText;

    for (int i=0; i<cipherText.size(); ++i)
    {
        char decryptedChar = cipherText[i] ^ key[i % key.size()];

        decryptedText.push_back(decryptedChar);
    }

    return decryptedText;
}

vector<string> GetCommonEnglishWords()
{
    vector<string> commonEnglishWords;

    commonEnglishWords.push_back("the");
    commonEnglishWords.push_back("be");
    commonEnglishWords.push_back("to");
    commonEnglishWords.push_back("of");
    commonEnglishWords.push_back("and");
    commonEnglishWords.push_back("a");
    commonEnglishWords.push_back("in");
    commonEnglishWords.push_back("that");
    commonEnglishWords.push_back("have");
    commonEnglishWords.push_back("I");
    commonEnglishWords.push_back("it");
    commonEnglishWords.push_back("for");
    commonEnglishWords.push_back("not");
    commonEnglishWords.push_back("on");
    commonEnglishWords.push_back("with");
    commonEnglishWords.push_back("he");
    commonEnglishWords.push_back("as");
    commonEnglishWords.push_back("you");
    commonEnglishWords.push_back("do");
    commonEnglishWords.push_back("at");

    return commonEnglishWords;
}

unordered_set<string> GetWords(const vector<char> &text)
{
    unordered_set<string> toReturn;
    stringstream ss;
    string temp;

    for (char letter : text)
    {
        ss << (char) tolower(letter);
    }


    while (ss >> temp)
    {
        toReturn.insert(temp);
    }

    return toReturn;
}

bool DoesContainCommonEnglishWords(const vector<char> &text)
{
    static vector<string> commonEnglishWords = GetCommonEnglishWords();
    int totalCommonEnglishWords = commonEnglishWords.size();
    int count = 0;

    unordered_set<string> textWords = GetWords(text);

    for (string commonWord : commonEnglishWords)
    {
        if (textWords.count(commonWord) > 0)
        {
            ++count;
        }
    }

    if (count * 1.0 / totalCommonEnglishWords > 0.50)
    {
        return true;
    }

    return false;
}

int GetSumOfAsciiValues(const vector<char> &text)
{
    int sum = 0;

    for (char letter : text)
    {
        sum += letter;
    }

    return sum;
}

int GetSumOfAsciiValuesInOriginalText(const char* inputFile)
{
    vector<char> cipherText = GetText(inputFile);

    vector< vector<char> > potentialKeys = GetPotentialKeys();

    for (vector<char> potentialKey : potentialKeys)
    {
        vector<char> decryptedText = DecryptText(cipherText, potentialKey);

        if (DoesContainCommonEnglishWords(decryptedText))
        {
            return GetSumOfAsciiValues(decryptedText);
        }
    }

    return -1;
}

int main()
{
    cout << GetSumOfAsciiValuesInOriginalText("cipher.txt") << endl;

    return 0;
}

