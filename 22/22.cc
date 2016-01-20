#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void GetNames(vector<string> &names)
{
    string temp;
    ifstream fin;

    fin.open("names.txt");

    while(fin >> temp)
    {
        names.push_back(temp);
    }

    fin.close();
}

int ComputeScoreForName(string name)
{
    int score = 0;

    for (int i=0; i<name.size(); ++i)
    {
        score += (name[i] - 'A' + 1);
    }

    return score;
}

void ComputeScoreForIndividualWord(vector<string> name, vector<int> &score)
{
    for (int i=0; i<name.size(); ++i)
    {
        int scoreForWord = ComputeScoreForName(name[i]);
        score.push_back(scoreForWord);
    }
}

void ComputeScoreWithPosition(vector<int> &score)
{
    for (int i=0; i<score.size(); ++i)
    {
        score[i] = score[i] * (i+1);
    }
}

int GetTotal(vector<int> score)
{
    int total = 0;

    for (int i=0; i<score.size(); ++i)
    {
        total += score[i];
    }

    return total;
}

int main()
{
    vector<string> name;
    vector<int> score;

    GetNames(name);
    sort(name.begin(), name.end());

    ComputeScoreForIndividualWord(name, score);
    ComputeScoreWithPosition(score);

    int total = GetTotal(score);

    cout << total << endl;
}

