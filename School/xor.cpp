#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
const size_t MAX_MEMO_SIZE = 1e5; // Limit the size of memoization cache

// LRU Cache for memoized transformations
unordered_map<string, string> memo_xor;
deque<string> memo_keys; // To track LRU

// Memoized XOR transformation function with LRU eviction
string xor_str(const string &trans) {
    if (memo_xor.count(trans)) return memo_xor[trans];

    string result = "";
    int len = trans.length();
    for (int i = 0; i < len - 1; i++) {
        result += trans[i];
        result += ((trans[i] - '0') ^ (trans[i + 1] - '0')) + '0';
    }
    result += trans[len - 1];

    // Add to memoization cache with LRU eviction
    if (memo_xor.size() >= MAX_MEMO_SIZE) {
        string old_key = memo_keys.front();
        memo_keys.pop_front();
        memo_xor.erase(old_key);
    }
    memo_xor[trans] = result;
    memo_keys.push_back(trans);

    return result;
}

// Function to calculate the "beauty" of a string
int calc_beauty(const string &str) {
    int beauty = 0;
    for (int i = 0; i < str.length() - 1; i++) {
        if (str[i] == str[i + 1]) {
            beauty++;
        }
    }
    return beauty;
}

int main() {
    int n;
    long long k;
    cin >> n >> k;
    string s;
    cin >> s;

    long long total_beauty = 0;

    // Iterate through all substrings directly
    for (int i = 0; i < n; ++i) {
        string current_substring = "";
        for (int j = i; j < n; ++j) {
            current_substring += s[j];

            // Compute the transformation up to k times
            string trans = current_substring;
            unordered_map<string, int> seen; // To detect cycles
            long long steps = 0;

            while (steps < k) {
                if (seen.count(trans)) {
                    // Cycle detected, skip redundant transformations
                    long long cycle_length = steps - seen[trans];
                    long long remaining = (k - steps) % cycle_length;
                    while (remaining--) {
                        trans = xor_str(trans);
                    }
                    break;
                }
                seen[trans] = steps;
                trans = xor_str(trans);
                steps++;
            }

            // Add the beauty of the final transformed substring
            total_beauty = (total_beauty + calc_beauty(trans)) % MOD;
        }
    }

    cout << total_beauty << endl;
    return 0;
}
