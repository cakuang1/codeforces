#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Given a list of bucket‐counts x[0..K-1] in a path,
// returns the minimum total deletions so that no two
// kept buckets are adjacent.
ll solve_path(const vector<int>& x) {
    int K = x.size();
    if (K <= 1) return 0;  // zero or one bucket → no deletions needed
    // We'll do the same DP as the Python version:
    // pad to 1‐based: x2[1]=x[0], …, x2[K]=x[K-1], x2[0]=0.
    vector<ll> x2(K+1, 0), dp(K+2, 0);
    for (int i = 1; i <= K; ++i) {
        x2[i] = x[i-1];
    }
    // dp[0]=dp[1]=0
    for (int i = 1; i <= K; ++i) {
        // option1: delete bucket i    → pay x2[i], come from dp[i]
        // option2: delete bucket i-1  → pay x2[i-1], come from dp[i-1]
        dp[i+1] = min(dp[i] + x2[i], dp[i-1] + x2[i-1]);
    }
    return dp[K+1];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ll D;
    cin >> N >> D;
    vector<int> A(N);
    int maxA = 0;
    for (int i = 0; i < N; i++){
        cin >> A[i];
        maxA = max(maxA, A[i]);
    }

    // Build frequency array up to maxA (we only need as large as the largest A[i])
    int M = maxA + 1;
    vector<int> cnt(M, 0);
    for (int x : A) {
        ++cnt[x];
    }

    ll ans = 0;
    if (D == 0) {
        // Must delete all but one in each bucket
        for (int c : cnt) {
            if (c > 1) ans += (c - 1);
        }
    } else {
        // Process each residue class mod D
        // Values run from 0..maxA, residues from 0..D-1
        for (int r = 0; r < D && r < M; ++r) {
            // collect counts at r, r+D, r+2D, ...
            vector<int> bucket;
            for (int v = r; v < M; v += D) {
                if (cnt[v] > 0) {
                    bucket.push_back(cnt[v]);
                }
            }
            // solve the no‐adjacent‐keeps DP on this path
            ans += solve_path(bucket);
        }
    }

    cout << ans << "\n";
    return 0;
}
