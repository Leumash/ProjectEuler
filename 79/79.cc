#include <iostream>
#include <vector>

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

int getPasscode(const vector<string> &keys) {
    int passcode = stoi(keys[0]);
    while (true) {
        if (isCorrectPasscode(to_string(passcode), keys)) {
            return passcode;
        }
        ++passcode;
    }
}

int main() {
    vector<string> keys = readKeys();
    cout << getPasscode(keys) << endl;
    return 0;
}

