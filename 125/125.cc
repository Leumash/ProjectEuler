#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

vector<long long> getValidSquares(long long n) {
    long long upper = sqrt(n);
    vector<long long> validSquares;
    for (long long i=1; i<=upper; ++i) {
        validSquares.push_back(i * i);
    }
    return validSquares;
}

vector<long long> getPrefixSum(vector<long long> nums) {
    for (long long i=1; i<nums.size(); ++i) {
        nums[i] += nums[i-1];
    }
    return nums;
}

bool isPalindrome(long long n) {
    string num = to_string(n);
    string rev = num;
    reverse(rev.begin(), rev.end());
    return num == rev;
}

long long getSumOfNumbersThatAreBothPalindromicAndSumOfConsecutiveSquares(long long n) {
    unordered_set<long long> nums;
    vector<long long> squares = getValidSquares(n);
    vector<long long> prefixSum = getPrefixSum(squares);
    prefixSum.insert(prefixSum.begin(), 0);
    for (long long b=1; b<prefixSum.size(); ++b) {
        for (long long a=0; a<b; ++a) {
            long long sumOfConsecutiveSquares = prefixSum[b] - prefixSum[a];
            if (sumOfConsecutiveSquares < n && b - a > 1 && isPalindrome(sumOfConsecutiveSquares)) {
                nums.insert(sumOfConsecutiveSquares);
            }
        }
    }
    long long sum = 0;
    for (long long num : nums) {
        sum += num;
    }
    return sum;
}

int main() {
    cout << getSumOfNumbersThatAreBothPalindromicAndSumOfConsecutiveSquares(100000000) << endl;
}

