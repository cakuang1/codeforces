#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
const ll NEG_INF = -1e18;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int N, M, K;
    cin >> N >> M >> K;
    // Read the grid: N rows and M columns.
    // We will store column by column.
    vector<vector<int>> col(M+1, vector<int>(N));
    for (int i = 0; i < N; i++){
        for (int j = 1; j <= M; j++){
            cin >> col[j][i];
        }
    }
 
    // For each column, sort the values in descending order and compute prefix sums.
    // Let pref[i][c] = sum of top c elements in column i (pref[i][0] = 0).
    vector<vector<ll>> pref(M+1);
    for (int j = 1; j <= M; j++){
        vector<int> tmp = col[j]; // copy the column
        sort(tmp.begin(), tmp.end(), greater<int>());
        // Determine maximum number of picks from column j:
        int available = (j < K ? j : K);  // sliding-window constraint; also cannot exceed K.
        int cmax = min(N, available);
        pref[j].resize(cmax+1, 0);
        for (int c = 1; c <= cmax; c++){
            pref[j][c] = pref[j][c-1] + tmp[c-1];
        }
    }
 
    // DP: dp[i] will store the best total money after processing i columns,
    // for each valid number of picks j.
    // For column i, valid j are in [offset, i], where offset = (i < K ? 0 : i - K + 1).
    vector<vector<ll>> dp(M+1);
    // For i=0, no columns processed: only state is 0 picks.
    dp[0].resize(1, 0);
 
    // Process columns 1..M
    for (int i = 1; i <= M; i++){
        int offset = (i < K ? 0 : i - K + 1);
        int states = i - offset + 1; // number of valid operation counts for column i.
        dp[i].assign(s  ates, NEG_INF);
 
        // For the previous column i-1, the allowed states:
        int prevOffset = ( (i-1) < K ? 0 : (i-1) - K + 1 );
        int prevStates = (i-1) - prevOffset + 1;
 
        // Maximum picks possible in column i:
        int available = (i < K ? i : K);
        int cmax = min(N, available);
 
        // Transition: for each valid state from previous column, try picking c elements from column i.
        for (int j_old = prevOffset; j_old <= (i-1); j_old++){
            int idx_old = j_old - prevOffset;
            if(dp[i-1][idx_old] == NEG_INF) continue;
            // Try all possible c picks (0 <= c <= cmax)
            for (int c = 0; c <= cmax; c++){
                int j_new = j_old + c;
                // j_new must be in allowed range for column i:
                if(j_new < offset || j_new > i) continue;
                int idx_new = j_new - offset;
                dp[i][idx_new] = max(dp[i][idx_new], dp[i-1][idx_old] + pref[i][c]);
            }
        }
    }
 
    // The final answer: after M columns, we must have performed exactly M-K+1 operations.
    int finalOps = M - K + 1;
    int finalOffset = (M < K ? 0 : M - K + 1);
    if(finalOps < finalOffset || finalOps > M){
        cout << -1 << "\n"; // Should not happen.
    } else {
        cout << dp[M][finalOps - finalOffset] << "\n";
    }
 
    return 0;
}
