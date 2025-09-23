#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();


    // determine dp 

    //   hwo woudly ousove evnsove htiw er wer

    vector<int> dp(n, 0);
    int maxLen = 0, count = 0;

    for (int i = 1; i < n; i++) {
        if (s[i] == ')') {
            if (s[i - 1] == '(') {
                dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
            } else if (s[i - 1] == ')' && i - dp[i - 1] - 1 >= 0 && s[i - dp[i - 1] - 1] == '(') {
                dp[i] = dp[i - 1] + 2;
                if (i - dp[i - 1] - 2 >= 0) {
                    dp[i] += dp[i - dp[i - 1] - 2];
                }
            }
            if (dp[i] > maxLen) {
                maxLen = dp[i];
                count = 1;
            } else if (dp[i] == maxLen && maxLen > 0) {
                count++;
            }
        }
    }

    if (maxLen == 0) {
        cout << "0 1\n";
    } else {
        cout << maxLen << " " << count << "\n";
    }
    return 0;
}


 