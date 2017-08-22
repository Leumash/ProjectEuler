#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> getValidSquares(int n) {
    int upper = sqrt(n);
    vector<int> validSquares;
    for (int i=1; i<=upper; ++i) {
        validSquares.push_back(i * i);
    }
    return validSquares;
}

vector<int> getPrefixSum(vector<int> nums) {
    for (int i=1; i<nums.size(); ++i) {
        nums[i] += nums[i-1];
    }
    return nums;
}

bool isPalindrome(int n) {
    string num = to_string(n);
    string rev = num;
    reverse(rev.begin(), rev.end());
    return num == rev;
}

int getSumOfNumbersThatAreBothPalindromicAndSumOfConsecutiveSquares(int n) {
    vector<int> squares = getValidSquares(n);
    vector<int> prefixSum = getPrefixSum(squares);
    prefixSum.insert(prefixSum.begin(), 0);
    int sum = 0;
    for (int b=1; b<prefixSum.size(); ++b) {
        for (int a=0; a<b; ++a) {
            int sumOfConsecutiveSquares = prefixSum[b] - prefixSum[a];
            if (sumOfConsecutiveSquares < n && b - a > 1&& isPalindrome(sumOfConsecutiveSquares)) {
                sum += sumOfConsecutiveSquares;
            }
        }
    }
    return sum;
}

int main() {
    cout << getSumOfNumbersThatAreBothPalindromicAndSumOfConsecutiveSquares(1000) << endl;
    return 0;
}

