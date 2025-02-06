#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;
const ll INF = 1e18;
const int MAXN = 405;

ll dp[MAXN][MAXN];
vector<ll> prefix; // Prefix sum array for range sum computation

// Function to compute minimum cost of merging subarrays
ll solve(int l, int r, vector<ll> &arr) {    
    if (l >= r) return 0;
    if (dp[l][r] != INF) return dp[l][r];

    ll sum = prefix[r+1] - prefix[l]; // Compute range sum in O(1)
    ll res = INF;

    for (int i = l; i < r; i++) {
        res = min(res, solve(l, i, arr) + solve(i + 1, r, arr) + sum);
    }

    dp[l][r] = res;
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    ll n;
    cin >> n;
    vector<ll> arr(n);
    
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Initialize DP table with INF
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = INF;
        }
    }

    // Compute prefix sum for fast range sum queries
    prefix.resize(n+1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i+1] = prefix[i] + arr[i];
    }

    cout << solve(0, n - 1, arr) << endl;
    return 0;
}
