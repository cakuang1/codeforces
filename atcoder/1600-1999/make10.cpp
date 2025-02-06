#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll mod = 1e9 + 7; // Default modulo
const ll mod2 = 998244353;
const int MAX_SUM = 10; // Maximum sum we care about

// Precompute modular inverses
ll power(ll a, ll b, ll m) {
    ll result = 1;
    while (b > 0) {
        if (b & 1) result = (result * a) % m;
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
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<ll> die(n); 
    for (int i = 0; i < n; i++) {
        cin >> die[i];
    }

    // DP table: dp[i][S]
    vector<vector<ll>> dp(n + 1, vector<ll>(1 << (MAX_SUM + 1), 0));
    dp[0][0] = 1; // Base case: no dice rolled, only empty set achievable

    for (int i = 0; i < n; i++) {
        ll dice = die[i];
        ll inv = mod_inverse(dice, mod2); // Modular inverse for normalization
        for (int curr = 0; curr < (1 << (MAX_SUM + 1)); curr++) {
            if (dp[i][curr] != 0) {
                // Transition for dice values
                for (int d = 1; d <= dice; d++) {
                    if (d > MAX_SUM) {
                        // If dice value exceeds MAX_SUM, it doesn't contribute
                        dp[i + 1][curr] = (dp[i + 1][curr] + dp[i][curr] * (dice - MAX_SUM) % mod2 * inv % mod2) % mod2;
                        break;
                    }
                    // Add dice value `d` to all achievable sums in `curr`
                    dp[i + 1][curr | (1 << d)] = (dp[i + 1][curr | (1 << d)] + dp[i][curr] * inv % mod2) % mod2;
                }
            }
        }
    }
    ll result = 0;
    for (int curr = 0; curr < (1 << (MAX_SUM + 1)); curr++) {
        if (dp[n][curr] != 0) {
            for (int s = 0; s <= MAX_SUM; s++) {
                if (curr & (1 << s)) {
                    result = (result + dp[n][curr]) % mod2;
                    break;
                }
            }
        }
    }

    cout << result << "\n";
    return 0;
}
