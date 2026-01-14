#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> Q;
    string queries;
    cin >> queries;

    string S;
    vector<vector<bool>> dp(Q+1, vector<bool>(Q+1, false));
    vector<int> palEnd(Q+1, 0); // palindromes ending at each index
    vector<long long> answers;
    long long total = 0;

    for (char q : queries) {
        if (q == '-') {
            int j = S.size() - 1;
            total -= palEnd[j];
            S.pop_back();
        } else {
            S.push_back(q);
            int j = S.size() - 1;
            int newCount = 0;
            for (int i = 0; i <= j; i++) {
                if (i == j) dp[i][j] = true;
                else if (j == i+1) dp[i][j] = (S[i] == S[j]);
                else dp[i][j] = (S[i] == S[j] && dp[i+1][j-1]);

                if (dp[i][j]) newCount++;
            }
            palEnd[j] = newCount;
            total += newCount;
        }
        answers.push_back(total);
    }

    for (int i = 0; i < Q; i++) {
        cout << answers[i] << (i+1 == Q ? '\n' : ' ');
    }
}
 
// wd oesthis rally wrwork we