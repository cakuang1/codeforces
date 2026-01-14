#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
//  freopen("output.txt", "w", stdout);
#endif
    
    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        string s[2];
        cin >> n >> s[0] >> s[1];
        
        for (int it = 0; it < 2; ++it) {
            while (s[0].back() == '.' && s[1].back() == '.') {
                s[0].pop_back();
                s[1].pop_back();
            }
            reverse(s[0].begin(), s[0].end());
            reverse(s[1].begin(), s[1].end());
        }
        n = s[0].size();
        
        vector<vector<int>> cost(n, vector<int>(2));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 2; ++j) {
                cost[i][j] = (s[j][i] == '*');
            }
        }



        
        vector<vector<int>> dp(n, vector<int>(2, INF));
        dp[0][0] = cost[0][1];
        dp[0][1] = cost[0][0];

        
        for (int i = 0; i + 1 < n; ++i) {
            dp[i + 1][0] = min(dp[i + 1][0], dp[i][0] + 1 + cost[i + 1][1]);
            dp[i + 1][0] = min(dp[i + 1][0], dp[i][1] + 2);
            dp[i + 1][1] = min(dp[i + 1][1], dp[i][1] + 1 + cost[i + 1][0]);
            dp[i + 1][1] = min(dp[i + 1][1], dp[i][0] + 2);
        }
        
        cout << min(dp[n - 1][0], dp[n - 1][1]) << endl;
    }
        
    return 0;
}