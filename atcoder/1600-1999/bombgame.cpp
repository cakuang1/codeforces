#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll mod2 = 998244353;

// Modular Arithmetic Utilities
ll power(ll a, ll b, ll m = mod2) {
    ll result = 1;
    a %= m;
    while (b > 0) {
        if (b & 1) {
            result = (result * a) % m;
        }
        a = (a * a) % m;
        b >>= 1;
    }
    return result;
}

ll mod_inverse(ll n, ll m = mod2) {
    return power(n, m - 2, m);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    const int K = 2; // Denominator for probability
    ll p = mod_inverse(K, mod2); // Probability (1/2 mod mod2)
    ll q = (1 - p + mod2) % mod2; // Complement probability (1 - p mod mod2)

    // Precompute powers of q
    vector<ll> qt(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        qt[i] = (qt[i - 1] * q) % mod2;
    }

    // DP table
    vector<vector<ll>> dp(n + 1, vector<ll>(n, 0));
    dp[1][0] = 1; // Base case

    ll mul = 1; // Multiplicative factor
    for (int i = 2; i <= n; i++) {
        mul = (mul * p % mod2) * mod_inverse((1 - power(q, i, mod2) + mod2) % mod2, mod2) % mod2;

        // Calculate the initial sum for dp[i][0]
        ll add = 0;
        for (int k = 0; k < i; k++) {
            add = (add + dp[i - 1][i - 1 - k] * qt[k] % mod2) % mod2;
        }

        // Compute dp[i][j]
        for (int j = 0; j < i; j++) {
            dp[i][j] = (dp[i][j] + add) % mod2;

            if (j < i - 1) {
                add = (add - dp[i - 1][j] * qt[i - 1] % mod2 + mod2) % mod2;
                add = (add * q % mod2 + dp[i - 1][j]) % mod2;
            }
        }
    }

    // Scale final results by mul
    for (int i = 0; i < n; i++) {
        dp[n][i] = dp[n][i] * mul % mod2;
    }

    // Output the result
    for (int i = 0; i < n; i++) {
        cout << dp[n][i] << " ";
    }
    cout << endl;

    return 0;
}
