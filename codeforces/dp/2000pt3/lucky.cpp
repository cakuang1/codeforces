#include <bits/stdc++.h>
using namespace std;
 
// We'll use -1e9 as "minus infinity" for our DP.
const int NEG_INF = -1000000000;
 
// Precompute the KMP-style next state transitions for virus.
// nextState[k][c] = length of longest prefix of virus that is suffix of (virus[0..k-1] + c).
vector<vector<int>> computeNext(const string &virus) {
    int L = virus.size();
    vector<vector<int>> nextState(L+1, vector<int>(26, 0));
    // For each state k and letter c, try to extend virus[0..k-1] by c.
    for (int k = 0; k <= L; k++){
        for (int c = 0; c < 26; c++){
            // Build string = virus[0..k-1] + (char)(c+'A').
            string cur = virus.substr(0, k) + char('A' + c);
            // We want the maximum t (0<=t<=L) such that virus[0..t-1] is a suffix of cur.
            int t = min(L, k+1);
            while(t > 0) {
                if(cur.substr(cur.size()-t) == virus.substr(0, t))
                    break;
                t--;
            }
            nextState[k][c] = t;
        }
    }
    return nextState;
}
 
// We'll reconstruct the answer using parent pointers.
struct Parent {
    int i, j, k; // previous indices
    char ch;     // if we took a letter here, otherwise 0.
};
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s1, s2, virus;
    cin >> s1 >> s2 >> virus;
    int n = s1.size(), m = s2.size(), L = virus.size();
    
    // Precompute next state transitions for virus.
    auto nextState = computeNext(virus);
    
    // dp[i][j][k]: max length of valid common subsequence for s1[i...] and s2[j...]
    // with current virus state = k.
    // We'll use 3D DP with dimensions (n+1) x (m+1) x (L)
    vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(m+1, vector<int>(L, NEG_INF)));
    // Parent pointers for reconstruction.
    vector<vector<vector<Parent>>> par(n+1, vector<vector<Parent>>(m+1, vector<Parent>(L, {-1,-1,-1,0})));
    
    dp[0][0][0] = 0;
    // Fill DP.
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= m; j++){
            for (int k = 0; k < L; k++){
                if(dp[i][j][k] == NEG_INF) continue;
                // Option 1: skip s1[i] if possible.
                if(i < n) {
                    if(dp[i+1][j][k] < dp[i][j][k]) {
                        dp[i+1][j][k] = dp[i][j][k];
                        par[i+1][j][k] = {i, j, k, 0}; // 0 means skip s1.
                    }
                }
                // Option 2: skip s2[j] if possible.
                if(j < m) {
                    if(dp[i][j+1][k] < dp[i][j][k]) {
                        dp[i][j+1][k] = dp[i][j][k];
                        par[i][j+1][k] = {i, j, k, 0}; // 0 means skip s2.
                    }
                }
                // Option 3: if characters match, try to add that letter.
                if(i < n && j < m && s1[i] == s2[j]) {
                    char c = s1[i];
                    int letter = c - 'A';
                    int newK = nextState[k][letter];
                    if(newK < L) { // only valid if virus is not formed.
                        if(dp[i+1][j+1][newK] < dp[i][j][k] + 1) {
                            dp[i+1][j+1][newK] = dp[i][j][k] + 1;
                            par[i+1][j+1][newK] = {i, j, k, c}; // we took letter c.
                        }
                    }
                }
            }
        }
    }
    
    // Find the best answer among dp[n][m][k] for k in [0,L-1].
    int best = NEG_INF, bestK = 0;
    for (int k = 0; k < L; k++){
        if(dp[n][m][k] > best) {
            best = dp[n][m][k];
            bestK = k;
        }
    }


    
    if(best <= 0) {
        cout << 0 << "\n";
        return 0;
    }
    
    // Reconstruct the sequence.
    string ans = "";
    int i = n, j = m, k = bestK;
    while(i != 0 || j != 0 || k != 0) {
        Parent p = par[i][j][k];
        if(p.i == -1) break; // safety check
        if(p.ch != 0) { // we took a letter here.
            ans.push_back(p.ch);
        }
        int ni = p.i, nj = p.j, nk = p.k;
        i = ni; j = nj; k = nk;
    }
    reverse(ans.begin(), ans.end());
    cout << ans << "\n";
    return 0;
}
