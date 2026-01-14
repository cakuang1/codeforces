#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (ll)1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read the two strings
    string s1, s2;
    cin >> s1 >> s2;

    int l1 = s1.size(); 
    int l2 = s2.size(); 
    
    if (l1 != l2) {
        cout << -1 << endl;
        return 0 ;
    }
    
    int L = l1;
    int n;
    cin >> n;
    
    //
    vector<vector<ll>> dp(26, vector<ll>(26, INF));
    for (int c = 0; c < 26; c++) 
        dp[c][c] = 0;

    // Input the direct edges
    for (int i = 0; i < n; i++) {
        char x, y;
        ll w;
        cin >> x >> y >> w;
        int u = x - 'a';
        int v = y - 'a';
        dp[u][v] = min(dp[u][v], w);
    }

    // Floyd–Warshall over the 26 letters
    for (int k = 0; k < 26; k++) {
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; j++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
    }

    ll totalCost = 0;
    string result;
    result.reserve(L);

    // Build the answer character by character
    for (int i = 0; i < L; i++) {
        int c1 = s1[i] - 'a';
        int c2 = s2[i] - 'a';

        // If already equal, keep that letter
        if (c1 == c2) {
            result.push_back(char('a' + c1));
            continue;
        }
        
        if (dp[c1][c2] == INF && dp[c2][c1] == INF) {
            cout << -1 << endl;
            return 0;
        }

        if (dp[c1][c2] <= dp[c2][c1]) {
            result.push_back(char(c2 + 'a')); 
            totalCost += dp[c1][c2];
        } else{
            result.push_back(char(c1 + 'a')); 
            totalCost += dp[c2][c1];
        }
    }

    // Output
    cout << totalCost << "\n"
         << result << "\n";

    return 0;
}
