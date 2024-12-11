#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAX = 200005; // Sufficient for factorial computations

vector<long long> fact(MAX), invFact(MAX);

// Fast modular exponentiation
long long modExp(long long x, long long y, long long mod) {
    long long res = 1;
    while (y > 0) {
        if (y & 1) res = (res * x) % mod;
        x = (x * x) % mod;
        y >>= 1;
    }
    return res;
}

// Precompute factorials and modular inverses
void precomputeFactorials(int maxVal) {
    fact[0] = 1;
    for (int i = 1; i <= maxVal; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    invFact[maxVal] = modExp(fact[maxVal], MOD - 2, MOD);
    for (int i = maxVal - 1; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }
}

// Compute nCr % MOD
long long nCr(int n, int r) {
    if (r > n || r < 0) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int h, w, n;
    cin >> h >> w >> n;

    vector<pair<int, int>> blackCells(n);
    for (int i = 0; i < n; i++) {
        cin >> blackCells[i].first >> blackCells[i].second;
    }

    blackCells.push_back({h, w}); // Add the bottom-right corner
    sort(blackCells.begin(), blackCells.end());

    precomputeFactorials(h + w - 2);

    vector<long long> dp(n + 1, 0);
    for (int i = 0; i <= n; i++) {
        int r_i = blackCells[i].first, c_i = blackCells[i].second;
        dp[i] = nCr(r_i + c_i - 2, r_i - 1);
        for (int j = 0; j < i; j++) {
            int r_j = blackCells[j].first, c_j = blackCells[j].second;
            if (r_j <= r_i && c_j <= c_i) {
                dp[i] = (dp[i] - dp[j] * nCr((r_i - r_j) + (c_i - c_j), r_i - r_j) % MOD + MOD) % MOD;
            }
        }
    }

    cout << dp[n] << endl;
    return 0;
}
 

 // enumerate all theblack tcells wforom the path we  
 // then what w