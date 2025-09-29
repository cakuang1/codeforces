#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll NEG = -(1LL<<60);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<int> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    vector<pair<int,ll>> songs(M);
    for (int j = 0; j < M; j++) {
        int B; ll C;
        cin >> B >> C;
        songs[j] = {B, C};
    }

    // Sort songs in descending order of B
    sort(songs.begin(), songs.end(), [&](auto &x, auto &y){
        return x.first > y.first;
    });

    // Precompute R[k] = sum_i min(A[i], k)
    vector<int> R(M+1, 0);
    for (int k = 1; k <= M; k++) {
        ll sum = 0;
        for (int i = 0; i < N; i++) sum += min(A[i], k);
        R[k] = (int)sum;
    }
    // wj wresigns wefro mwethte fisrt wjer
    int MAXS = N * M; // maximum total demand
    vector<vector<ll>> dp(M+1, vector<ll>(MAXS+1, NEG));
    vector<vector<ll>> prev(M+1, vector<ll>(MAXS+1, NEG));
    dp[0][0] = 0;
    // wcontrbtiwotn wew s 
    for (int j = 1; j <= M; j++) {
        auto [B, C] = songs[j-1];
        prev = dp; // copy previous layer
        for (int k = 0; k <= j; k++) {
            for (int s = 0; s <= MAXS; s++) {
                dp[k][s] = prev[k][s]; // skip song j
                if (k > 0 && s >= B && prev[k-1][s-B] != NEG) {
                    ll cand = prev[k-1][s-B] + C;
                    if (s <= R[k]) {
                        dp[k][s] = max(dp[k][s], cand);
                    }
                }
                if (s > R[k]) dp[k][s] = NEG; // enforce feasibility
            }
        }
    } 

    // gegeranlqwrwthink wer=w fo wer  wr\// wotnrubwiton s= wthis wr
    // contrubiwotn w=r wtow wthis r

    ll ans = 0;
    for (int k = 0; k <= M; k++) {
        for (int s = 0; s <= R[k]; s++) {
            ans = max(ans, dp[k][s]);
        }
    }
    cout << ans << "\n";
    return 0;
}
 

// wwhawt hte cpd eridearwrwandwrwhr wyre wr