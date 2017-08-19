#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

vector<string> readKeys() {
    string key;
    vector<string> keys;
    while (cin >> key) {
        keys.push_back(key);
    }
    return keys;
}

bool isSubCode(string passcode, string key) {
    int pos;
    pos = passcode.find(key[0]);
    if (pos == string::npos) {
        return false;
    }
    pos = passcode.find(key[1], pos + 1);
    if (pos == string::npos) {
        return false;
    }
    pos = passcode.find(key[2], pos + 1);
    return pos != string::npos;
}

bool isCorrectPasscode(string passcode, const vector<string> &keys) {
    for (string key : keys) {
        if (!isSubCode(passcode, key)) {
            return false;
        }
    }
    return true;
}

vector<char> getRequiredDigits(const vector<string> &keys) {
    unordered_set<char> requiredDigits;
    for (string key : keys) {
        for (char k : key) {
            requiredDigits.insert(k);
        }
    }
    vector<char> digits;
    digits.insert(digits.end(), requiredDigits.begin(), requiredDigits.end());
    return digits;
}

string convertToString(vector<char> keys) {
    string toReturn;
    for (int i=0; i<keys.size(); ++i) {
        toReturn += keys[i];
    }
    return toReturn;
}

vector<string> getPermutations(vector<char> requiredKeys) {
    vector<string> permutations;
    sort(requiredKeys.begin(), requiredKeys.end());
    do {
        string permutation = convertToString(requiredKeys);
        permutations.push_back(permutation);
    } while (next_permutation(requiredKeys.begin(), requiredKeys.end()));
    return permutations;
}

int getPasscode(const vector<string> &keys) {
    vector<char> requiredKeys = getRequiredDigits(keys);
    vector<string> permutations = getPermutations(requiredKeys);

    for (string permutation : permutations) {
        if (isCorrectPasscode(permutation, keys)) {
            return stoi(permutation);
        }
    }
}


int main() {
    vector<string> keys = readKeys();
    cout << getPasscode(keys) << endl;
    return 0;
}

